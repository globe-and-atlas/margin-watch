"""Capture and pixel-check a fixture build on a known, already-running QEMU."""
from pathlib import Path
import argparse
import json
import socket
import subprocess
import time

from PIL import Image, ImageDraw, ImageFont
try:
    from execution.generate_digits import glyph_mask
except ModuleNotFoundError:
    from generate_digits import glyph_mask

ROOT = Path(__file__).resolve().parents[1]
UUID = json.loads((ROOT / 'watchface/package.json').read_text())['pebble']['uuid']
PALETTES=[((255,255,255),(0,0,0),(170,0,0)),((255,255,170),(0,0,0),(170,0,0)),((0,0,0),(255,255,255),(255,85,0)),((0,0,85),(255,255,255),(85,255,255)),((170,255,170),(0,0,0),(0,85,0)),((85,0,85),(255,255,255),(255,85,170)),((0,0,85),(255,255,255),(85,255,255))]


def command(args: list[str]) -> None:
    result = subprocess.run(['pebble'] + args, cwd=ROOT / 'watchface',
                            capture_output=True, text=True, timeout=45)
    if result.returncode:
        raise RuntimeError(result.stderr[-1500:])


def screenshot(port: int) -> Image.Image:
    path = ROOT / '.tmp/native-frame.ppm'
    path.unlink(missing_ok=True)
    with socket.create_connection(('localhost', port), timeout=5) as connection:
        connection.recv(65536)
        connection.sendall(f'screendump "{path.resolve()}"\n'.encode())
        deadline = time.monotonic() + 5
        while time.monotonic() < deadline:
            connection.recv(65536)
            try:
                image = Image.open(path).convert('RGB')
                break
            except (FileNotFoundError, OSError):
                continue
        else:
            raise TimeoutError('QEMU screendump did not complete')
    pixels = image.get_flattened_data() if hasattr(image,'get_flattened_data') else image.getdata()
    peak = max(max(pixel) for pixel in pixels)
    # QEMU applies backlight dimming; restore the native 2-bit RGB palette.
    image = image.point(lambda channel: round(channel / max(peak, 1) * 3) * 85)
    path.unlink(missing_ok=True)
    assert image.size == (200, 228)
    return image


def expected_pair(value: int, fg: tuple[int,int,int], bg: tuple[int,int,int]) -> Image.Image:
    image=Image.new('RGB',(145,94),bg)
    first=glyph_mask(value//10);second=glyph_mask(value%10)
    left=first.getbbox()[0];right=68+second.getbbox()[2]-1
    offset=(143-left-right)//2
    image.paste(fg,(offset,0),first);image.paste(fg,(offset+68,0),second)
    return image


def check(image, hour, minute, palette):
    bg,fg,accent=PALETTES[palette]
    assert image.crop((0,14,145,108)).tobytes()==expected_pair(hour,fg,bg).tobytes(),'Hour pixels differ'
    assert image.crop((0,116,145,210)).tobytes()==expected_pair(minute,fg,bg).tobytes(),'Minute pixels differ'
    assert image.getpixel((145,100))==accent,'Divider color differs'


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--monitor',required=True,type=int);options=parser.parse_args()
    keys=json.loads((ROOT/'watchface/build/js/message_keys.json').read_text())
    cases=[('default',10,8,2,1,0,82)]
    cases += [(f'palette-{p}',10,8,2,1,p,82) for p in range(6)]
    cases += [('midnight-24h',0,0,2,1,0,0),('midnight-12h',0,0,1,1,0,100),('noon',12,0,1,1,0,50),('late-24h',23,59,2,1,0,5),('late-12h',23,59,1,1,0,82),('eleven',11,11,2,1,0,82)]
    cases += [(f'date-{d}',10,8,1,d,0,82) for d in range(5)]
    cases += [('custom',10,8,2,1,6,82)]
    evidence=[]
    for name,h,m,fmt,date,palette,battery in cases:
        values={keys['Palette']:palette,keys['TimeFormat']:fmt,keys['DateFormat']:date,keys['Background']:0x000055,keys['Foreground']:0xFFFFFF,keys['Accent']:0x55FFFF,11000:h,11001:m,11004:battery}
        command(['send-app-message','--emulator','emery','--app-uuid',UUID,'--int']+[f'{k}={v}' for k,v in values.items()])
        display=h if fmt==2 else h%12 or 12
        for attempt in range(30):
            image=screenshot(options.monitor)
            try:check(image,display,m,palette);break
            except AssertionError:time.sleep(.1)
        else:check(image,display,m,palette)
        image.save(ROOT/f'media/margin-{name}.png');evidence.append({'case':name,'native_digit_pixels':True});print('PASS:',name,flush=True)
    (ROOT/'.tmp/native-checks.json').write_text(json.dumps(evidence,indent=2))
    # Restore reproducible default for review.
    command(['send-app-message','--emulator','emery','--app-uuid',UUID,'--int']+[f'{keys[k]}={v}' for k,v in {'Palette':0,'TimeFormat':0,'DateFormat':1}.items()]+['11000=10','11001=8','11004=82'])


if __name__=='__main__':main()

"""Generate original layout masks from bundled OFL Archivo Black."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
ROOT=Path(__file__).resolve().parents[1]
WIDTH,HEIGHT=64,94

def glyph_mask(number: int) -> Image.Image:
    font=ImageFont.truetype(str(ROOT/'assets/fonts/ArchivoBlack-Regular.ttf'),160)
    boxes=[font.getbbox(str(i)) for i in range(10)]
    top=min(b[1] for b in boxes);bottom=max(b[3] for b in boxes)
    b=boxes[number];max_width=max(v[2]-v[0] for v in boxes)
    canvas=Image.new('L',(b[2]-b[0],bottom-top))
    ImageDraw.Draw(canvas).text((-b[0],-top),str(number),font=font,fill=255)
    canvas=canvas.resize((round(canvas.width*62/max_width),HEIGHT),Image.Resampling.LANCZOS)
    image=Image.new('L',(WIDTH,HEIGHT));image.paste(canvas,((WIDTH-canvas.width)//2,0))
    return image.point(lambda p:255 if p>=128 else 0).convert('1')

def main() -> None:
    lines=['/* Generated; Archivo Black OFL: licenses/ArchivoBlack-OFL.txt. */','#pragma once','#include <stdint.h>','#define DIGIT_WIDTH 64','#define DIGIT_HEIGHT 94','static const uint8_t DIGITS[10][752]={']
    for n in range(10):lines.append('{'+','.join(map(str,glyph_mask(n).tobytes()))+'},')
    lines.append('};');bounds=[glyph_mask(i).getbbox() for i in range(10)]
    lines.append('static const int DIGIT_LEFT[10]={'+','.join(str(b[0]) for b in bounds)+'};')
    lines.append('static const int DIGIT_RIGHT[10]={'+','.join(str(b[2]-1) for b in bounds)+'};')
    (ROOT/'watchface/src/c/digits.h').write_text('\n'.join(lines)+'\n')
if __name__=='__main__':main()

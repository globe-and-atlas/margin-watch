from pathlib import Path
import subprocess
import importlib.util
ROOT=Path(__file__).resolve().parents[1]

def test_time_policy():
    folder=ROOT/'.tmp';folder.mkdir(exist_ok=True)
    source=folder/'policy.c';binary=folder/'policy'
    source.write_text('''#include <assert.h>
#include "policy.h"
int main(void){
for(int h=0;h<24;h++){
assert(display_hour(h,2,false)==h);
assert(display_hour(h,1,true)==(h%12?h%12:12));
assert(display_hour(h,0,true)==h);
assert(display_hour(h,0,false)==(h%12?h%12:12));}
assert(battery_bars(0)==0);assert(battery_bars(100)==4);
for(int b=1;b<=100;b++)assert(battery_bars(b)>=1 && battery_bars(b)<=4);
assert(minute_progress(0)==0);assert(minute_progress(59)==36);
return 0;}
''')
    subprocess.run(['cc','-Wall','-Werror','-I',str(ROOT/'watchface/src/c'),str(source),'-o',str(binary)],check=True)
    subprocess.run([str(binary)],check=True)

def test_mask_geometry():
    spec=importlib.util.spec_from_file_location('digits',ROOT/'execution/generate_digits.py');mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod)
    for n in range(10):
        image=mod.glyph_mask(n);b=image.getbbox();assert b and b[0]>=0 and b[2]<=64 and b[3]<=94
        assert 10 < sum(image.convert('L').get_flattened_data())/255
    for value in range(60):
        left=mod.glyph_mask(value//10).getbbox()[0];right=68+mod.glyph_mask(value%10).getbbox()[2]-1
        offset=(143-left-right)//2
        assert 0<=offset+left and offset+right<145
        assert abs((offset+left+offset+right)/2-71.5)<=.5

#include <pebble.h>
#include "config.h"
#include "policy.h"
#include "digits.h"
enum{P_PALETTE=1,P_BG,P_FG,P_ACCENT,P_TIME,P_DATE};
typedef struct{int palette,bg,fg,accent,time,date;}Settings;
static Settings s={0,0xFFFFFF,0x000000,0xAA0000,0,1};
static const uint32_t PALETTES[6][3]={{0xFFFFFF,0x000000,0xAA0000},{0xFFFFAA,0x000000,0xAA0000},{0x000000,0xFFFFFF,0xFF5500},{0x000055,0xFFFFFF,0x55FFFF},{0xAAFFAA,0x000000,0x005500},{0x550055,0xFFFFFF,0xFF55AA}};
static Window *window;static Layer *layer;static struct tm current;static int battery;
#if MARGIN_FIXTURE
static int fh=MARGIN_HOUR,fm=MARGIN_MINUTE,fb=MARGIN_BATTERY;
#endif
static const char *DAYS[]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
static const char *MONTHS[]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
static uint32_t color(int i){if(s.palette<6)return PALETTES[s.palette][i];return i==0?(uint32_t)s.bg:i==1?(uint32_t)s.fg:(uint32_t)s.accent;}
static void text(GContext *ctx,const char *value,int y,bool big){graphics_draw_text(ctx,value,fonts_get_system_font(big?FONT_KEY_GOTHIC_24_BOLD:FONT_KEY_GOTHIC_18_BOLD),GRect(150,y,45,29),GTextOverflowModeFill,GTextAlignmentCenter,NULL);}
static void digit(GContext *ctx,int n,int x,int y){
  for(int row=0;row<94;row++){int start=-1;for(int col=0;col<=64;col++){
    bool on=col<64 && (DIGITS[n][row*8+col/8]&(0x80>>(col%8)));
    if(on && start<0)start=col;
    if(!on && start>=0){graphics_fill_rect(ctx,GRect(x+start,y+row,col-start,1),0,GCornerNone);start=-1;}
  }}
}
static void pair(GContext *ctx,int value,int y){
  int left=DIGIT_LEFT[value/10],right=68+DIGIT_RIGHT[value%10];
  int x=(143-left-right)/2;
  digit(ctx,value/10,x,y);digit(ctx,value%10,x+68,y);
}
#if defined(PBL_ROUND)
#include "round_digital.h"
static void round_numeral(GContext *ctx,int value,int x,int y,int w,int h){rmask(ctx,DIGITS[value],64,94,8,x,y,w,h);}
static void round_current(GContext *ctx){uint32_t bg=color(0),fg=color(1),accent=color(2);RoundData d={0};d.now=current;d.bg=bg;d.fg=fg;d.accent=accent;d.battery=battery;d.time_mode=s.time;d.date_mode=s.date;int hour=rhour(&d);d.hour_shift=rpair_shift(DIGITS[hour/10],DIGITS[hour%10],64,94,8,24,67,39,53,65);d.minute_shift=rpair_shift(DIGITS[d.now.tm_min/10],DIGITS[d.now.tm_min%10],64,94,8,24,67,39,53,65);round_digital(ctx,&d,5,round_numeral);}
#endif
static void draw(Layer *own,GContext *ctx){
#if defined(PBL_ROUND)
 (void)own;round_current(ctx);rproof_marker(ctx);return;
#endif

  graphics_context_set_antialiased(ctx,false);
  graphics_context_set_fill_color(ctx,GColorFromHEX(color(0)));graphics_fill_rect(ctx,layer_get_bounds(own),0,GCornerNone);
  graphics_context_set_fill_color(ctx,GColorFromHEX(color(1)));pair(ctx,display_hour(current.tm_hour,s.time,clock_is_24h_style()),14);pair(ctx,current.tm_min,116);
  graphics_context_set_fill_color(ctx,GColorFromHEX(color(2)));graphics_fill_rect(ctx,GRect(145,14,2,196),0,GCornerNone);
  graphics_context_set_text_color(ctx,GColorFromHEX(color(1)));
  char a[24],b[24],c[24];
  if(s.date){
    text(ctx,DAYS[current.tm_wday],23,true);
    if(s.date==1){text(ctx,MONTHS[current.tm_mon],49,true);snprintf(a,sizeof(a),"%02d",current.tm_mday);text(ctx,a,75,true);}
    else{
      if(s.date==2){snprintf(a,sizeof(a),"%04d",current.tm_year+1900);snprintf(b,sizeof(b),"%02d",current.tm_mon+1);snprintf(c,sizeof(c),"%02d",current.tm_mday);}
      else if(s.date==3){snprintf(a,sizeof(a),"%02d",current.tm_mon+1);snprintf(b,sizeof(b),"%02d",current.tm_mday);snprintf(c,sizeof(c),"%04d",current.tm_year+1900);}
      else{snprintf(a,sizeof(a),"%02d",current.tm_mday);snprintf(b,sizeof(b),"%02d",current.tm_mon+1);snprintf(c,sizeof(c),"%04d",current.tm_year+1900);}
      text(ctx,a,51,false);text(ctx,b,73,false);text(ctx,c,95,false);
    }
  }
  if(!uses_24(s.time,clock_is_24h_style()))text(ctx,current.tm_hour>=12?"PM":"AM",132,false);
  graphics_context_set_fill_color(ctx,GColorFromHEX(color(1)));graphics_context_set_stroke_color(ctx,GColorFromHEX(color(1)));
  graphics_draw_rect(ctx,GRect(155,169,29,14));graphics_fill_rect(ctx,GRect(184,173,3,6),0,GCornerNone);
  for(int i=0;i<battery_bars(battery);i++)graphics_fill_rect(ctx,GRect(158+i*6,172,4,8),0,GCornerNone);
  snprintf(a,sizeof(a),"%d%%",battery);text(ctx,a,187,false);
  graphics_context_set_fill_color(ctx,GColorFromHEX(color(1)));graphics_fill_rect(ctx,GRect(154,216,36,3),0,GCornerNone);
  graphics_context_set_fill_color(ctx,GColorFromHEX(color(2)));graphics_fill_rect(ctx,GRect(154,216,minute_progress(current.tm_min),3),0,GCornerNone);
}
static void tick(struct tm *now,TimeUnits changed){(void)changed;current=*now;
#if MARGIN_FIXTURE
current.tm_hour=fh;current.tm_min=fm;current.tm_year=126;current.tm_mon=10;current.tm_mday=5;current.tm_wday=4;
#endif
layer_mark_dirty(layer);}
static void battery_changed(BatteryChargeState state){battery=state.charge_percent;
#if MARGIN_FIXTURE
battery=fb;
#endif
layer_mark_dirty(layer);}
static void set(DictionaryIterator *iter,uint32_t key,int persist,int maximum,int *target){Tuple *t=dict_find(iter,key);if(t && (t->type==TUPLE_INT || t->type==TUPLE_UINT)){int v=t->value->int32;if(v>=0 && v<=maximum){*target=v;persist_write_int(persist,v);}}}
#if MARGIN_FIXTURE
static void fixture(DictionaryIterator *iter,int key,int maximum,int *target){Tuple *t=dict_find(iter,key);if(t && t->type==TUPLE_INT && t->value->int32>=0 && t->value->int32<=maximum)*target=t->value->int32;}
#endif
static void inbox(DictionaryIterator *iter,void *context){
#if defined(PBL_ROUND) && (MARGIN_FIXTURE)
 Tuple *round_proof=dict_find(iter,11022);if(round_proof && round_proof->type==TUPLE_INT){r_proof=round_proof->value->int32==1;layer_mark_dirty(layer);}
#endif
(void)context;
set(iter,MESSAGE_KEY_Palette,P_PALETTE,6,&s.palette);set(iter,MESSAGE_KEY_Background,P_BG,0xFFFFFF,&s.bg);set(iter,MESSAGE_KEY_Foreground,P_FG,0xFFFFFF,&s.fg);set(iter,MESSAGE_KEY_Accent,P_ACCENT,0xFFFFFF,&s.accent);set(iter,MESSAGE_KEY_TimeFormat,P_TIME,2,&s.time);set(iter,MESSAGE_KEY_DateFormat,P_DATE,4,&s.date);
#if MARGIN_FIXTURE
fixture(iter,11000,23,&fh);fixture(iter,11001,59,&fm);fixture(iter,11004,100,&fb);battery=fb;
#endif
time_t now=time(NULL);tick(localtime(&now),MINUTE_UNIT);}
static void restore(int key,int maximum,int *target){if(persist_exists(key)){int v=persist_read_int(key);if(v>=0 && v<=maximum)*target=v;}}
static void init(void){restore(P_PALETTE,6,&s.palette);restore(P_BG,0xFFFFFF,&s.bg);restore(P_FG,0xFFFFFF,&s.fg);restore(P_ACCENT,0xFFFFFF,&s.accent);restore(P_TIME,2,&s.time);restore(P_DATE,4,&s.date);
window=window_create();layer=layer_create(PBL_IF_ROUND_ELSE(GRect(0,0,PBL_DISPLAY_WIDTH,PBL_DISPLAY_HEIGHT),GRect(0,0,200,228)));layer_set_update_proc(layer,draw);layer_add_child(window_get_root_layer(window),layer);window_stack_push(window,true);time_t now=time(NULL);tick(localtime(&now),MINUTE_UNIT);battery_changed(battery_state_service_peek());tick_timer_service_subscribe(MINUTE_UNIT,tick);battery_state_service_subscribe(battery_changed);app_message_register_inbox_received(inbox);app_message_open(256,64);}
static void deinit(void){tick_timer_service_unsubscribe();battery_state_service_unsubscribe();app_message_deregister_callbacks();layer_destroy(layer);window_destroy(window);}
int main(void){init();app_event_loop();deinit();}

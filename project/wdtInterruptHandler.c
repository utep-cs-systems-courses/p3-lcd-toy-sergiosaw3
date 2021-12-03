#include <msp430.h>
#include "libTimer.h"
#include "draw_shapes.h"
#include "lcdutils.h"
#include "lcddraw.h"

// function that handles interrupts
// from the periodic timer
// The timer fires an event 250 times/sec
//u_int backgroundColor = COLOR_BLUE;
void
__interrupt_vec(WDT_VECTOR) WDT()
{
  const  u_int second_limit = 250;
  static u_int second_count = 0;
  static int seconds = 0;

  const u_char text_row = 20;
  const u_char text_col = 40;
  const u_char char_width = 12;
  static u_char blue = 31, green = 16, red = 31;
  u_int on_color  =                (green << 5) | red;
  u_int off_color = (blue << 11)                | red;
  
  second_count++;

  if (second_count >= second_limit) {
    draw_moving_shapes();
    second_count = 0;
    seconds++;
    //drawChar5x7(text_col+char_width*2, text_row, tmp2,on_color, background_color);
  }
  char tmp1=seconds+'0';
  static int itmp2=0;
  //char tmp2='0';
  if(seconds%10 ==0)
    {
      char tmp2= itmp2+'0';
      drawChar5x7(text_col+char_width, text_row, tmp2,on_color, background_color);
      itmp2++;
  }
  if(seconds%10 < 10){
  drawChar5x7(text_col+char_width*2, text_row, tmp1,on_color, background_color);
  }
  if(seconds==100){
    char redraw_screen =1;
  }
} 


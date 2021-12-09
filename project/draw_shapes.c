#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "switches.h"
#include "buzzer.h"

//#include <libTimer.h>
//#include "led.h"

// global vars for the rectangle
rectangle rect1;

rectangle rect2;
circle cir1;

circle cir2;

triangle tri1;

u_int background_color = COLOR_BLUE;

void
init_shapes(void)
{
  // vars for the rectangle
  rect1.rect_row = 40;
  rect1.rect_col = screenWidth / 2;
  rect1.old_rect_row = 40;
  rect1.old_rect_col = screenWidth / 2;
  rect1.height = 10;
  rect1.width = 10;
  rect1.xvel =-10;
  rect1.yvel =5;
  rect1.hit =0;
  //rect1.height = 10;
  //rect1.width  = 60;

  
  rect2.rect_row = 20;
  rect2.rect_col = screenWidth / 2;
  rect2.old_rect_row = 20;
  rect2.old_rect_col = screenWidth / 2;
  rect2.height = 10;
  rect2.width = 10;
  rect2.xvel =-10;
  rect2.yvel =5;
  rect2.hit =0;
  
  // vars for the circle
  cir1.cir_y = 60;
  cir1.cir_x = screenWidth / 2;
  cir1.old_cir_y = 60;
  cir1.old_cir_x = screenWidth / 2;
  //cir1.r = 20;
  cir1.r = 5;
  cir1.xvel =5;
  cir1.yvel =10;
  

  cir2.cir_y = 100;
  cir2.cir_x = screenWidth / 2;
  cir2.old_cir_y = 100;
  cir2.old_cir_x = screenWidth / 2;
  cir2.r = 20;
  cir2.xvel =10;
  cir2.yvel=8;
  //if(switch1_state == down){
    
  //}
}

void
draw_moving_shapes(void)
{
  int left_col1 = rect1.old_rect_col - (rect1.width / 2);
  int top_row1  = rect1.old_rect_row - (rect1.height / 2);
int left_col2 = rect2.old_rect_col - (rect2.width / 2);
  int top_row2  = rect2.old_rect_row - (rect2.height / 2);
  
  // blank out the old rectangle
  fillRectangle(left_col1, top_row1, rect1.width, rect1.height, background_color);

  fillRectangle(left_col2, top_row2, rect2.width, rect2.height, background_color);
  //fillTriangle(left_col, top_row, tri1.width, tri1.height, background_color);


  
  // blank out the old circle
  //draw_circle(cir1.old_cir_x, cir1.old_cir_y, cir1.r, background_color);
  
  draw_circle(cir2.old_cir_x, cir2.old_cir_y, cir2.r, background_color);

  // draw and update the rectangle
  moving_rectangle(&rect1);
  moving_rectangle(&rect2);
  
  // draw and update the circle
  //moving_circle(&cir1);

  moving_circle(&cir2);

  // draw the triangle
  //draw_triangle();

  //draw_circle(cir2.old_cir_x, cir2.old_cir_y, cir2.r, WHITE);
  //moving_triangle(&tri1);
}


void change_vel1(void)
{
  //int tmp;
  //tmp=cir2.xvel;
  cir2.xvel = 8;
  cir2.yvel = 10;
}

void change_vel2(void)
{
  //int tmp;
  //tmp=cir2.xvel;
  cir2.xvel = 8;
  cir2.yvel = -10;
}

void change_vel3(void)
{
  //int tmp;
  //tmp=cir2.xvel;
  cir2.xvel = -8;
  cir2.yvel = 10;
}

void change_vel4(void)
{
  //int tmp;
  //tmp=cir2.xvel;
  cir2.xvel = -8;
  cir2.yvel = -10;
}

void
draw_rectangle(void)
{
  int left_col = rect1.rect_col - (rect1.width / 2);
  int top_row  = rect1.rect_row - (rect1.height / 2);

  unsigned int blue = 16, green = 0, red = 31;
  unsigned int color = (blue << 11) | (green << 5) | red;

  fillRectangle(left_col, top_row, rect1.width, rect1.height, color);
}


void
moving_rectangle(rectangle *to_draw)
{
  int x_vel = to_draw->xvel;
  int y_vel = to_draw->yvel;

  int left_col = to_draw->rect_col - (to_draw->width / 2);
  int top_row  = to_draw->rect_row - (to_draw->height / 2);

  unsigned int blue = 16, green = 0, red = 31;
  unsigned int color = (blue << 11) | (green << 5) | red;

  // draw rectangle at current position
  if(to_draw->hit==0){
  fillRectangle(left_col, top_row, to_draw->width, to_draw->height, color);
  }
  else{
  fillRectangle(left_col, top_row, to_draw->width, to_draw->height, background_color);  
  }

  // save current position
  to_draw->old_rect_row = to_draw->rect_row;
  to_draw->old_rect_col = to_draw->rect_col;

  // update position
  to_draw->rect_row += y_vel;
  to_draw->rect_col += x_vel;

  // check boundaries, see if rectangle has hit the edges
  if ( ( to_draw->rect_col - (to_draw->width / 2) ) <= 0 ||            // left boundary
       ( to_draw->rect_col + (to_draw->width / 2) ) >= screenWidth ) { // right boundary
    // right or left hit, reverse x velocity
    //x_vel = x_vel * -1;
    to_draw->xvel = x_vel*-1;
  }
  if ( (to_draw->rect_row + to_draw->height / 2) >= screenHeight ||   // bottom
       (to_draw->rect_row - to_draw->height / 2) <= 0) {              // top
    // top or bottom hit, reverse y velocity
    //y_vel = y_vel * -1;
    to_draw->yvel = y_vel*-1;
  }
  
  /* left of rect <= right of cir AND top of rect >= top of cir *this works because it generates screen top dow* AND bottom of rect <= top of cir??
*/
  if ( ( to_draw->rect_col - (to_draw->width / 2) ) <= cir2.cir_x+cir2.r && (to_draw->rect_row - to_draw->height / 2) >= cir2.cir_y-cir2.r && (to_draw->rect_row + to_draw->height / 2) <= cir2.cir_y+cir2.r && to_draw->rect_col + (to_draw->width / 2)  >= cir2.cir_x-cir2.r && to_draw->hit ==0)
    {
      buzzer_set_period(1000);
      to_draw->xvel=0;
      to_draw->yvel=0;
      for(int i=0;i<10000;i++){
	buzzer_set_period(1000);
      to_draw->xvel=0;
      to_draw->yvel=0;
      }
      //color = background_color;
      buzzer_set_period(0);
      to_draw->hit =1;
    }
  
  
}


void
draw_triangle(void)
{
  u_char height = 40;
  u_char row = 80, col = screenWidth / 2;

  u_char step = 0;

  unsigned int blue = 31, green = 0, red = 31;

  unsigned int color = (blue << 11) | (green << 5) | red;

  // draw a n equilateral triangle
  // starts at the top and works down
  // at the first row the width is 1, second 2 and so on
  for (step = 0; step < height; step++) {
    // left side of triangle
    u_char start_col = col - (step / 2);
    // right side of triangle
    u_char end_col   = col + (step / 2);
    u_char width     = end_col - start_col;
    fillRectangle(col - (step / 2), row+step, width, 1, color);
  }
}


void
moving_triangle(triangle *to_draw) //change rectangle to triangle
{
  static int x_vel = 10;
  static int y_vel = 5;

  int left_col = to_draw->tri_col - (to_draw->width / 2);
  int top_row  = to_draw->tri_row - (to_draw->height / 2);

  unsigned int blue = 16, green = 0, red = 31;
  unsigned int color = (blue << 11) | (green << 5) | red;

  // draw rectangle at current position
  fillTriangle(left_col, top_row, to_draw->width, to_draw->height, color);

  // save current position
  to_draw->old_tri_row = to_draw->tri_row;
  to_draw->old_tri_col = to_draw->tri_col;

  // update position
  to_draw->tri_row += y_vel;
  to_draw->tri_col += x_vel;

  // check boundaries, see if rectangle has hit the edges
  if ( ( to_draw->tri_col - (to_draw->width / 2) ) <= 0 ||            // left boundary
       ( to_draw->tri_col + (to_draw->width / 2) ) >= screenWidth ) { // right boundary
    // right or left hit, reverse x velocity
    x_vel = x_vel * -1;
  }
  if ( (to_draw->tri_row + to_draw->height / 2) >= screenHeight ||   // bottom
       (to_draw->tri_row - to_draw->height / 2) <= 0) {              // top
    // top or bottom hit, reverse y velocity
    y_vel = y_vel * -1;
  }

}



void
drawHorizontalLine(u_int x_start, u_int x_end, u_int y, u_int colorBGR)
{
  u_int length = x_end - x_start;
  // set the draw area from the start of the line to the end
  // height is 1 since its a line
  lcd_setArea(x_start, y, x_end, y);
  for (u_int i = 0; i < length; i++) {
    lcd_writeColor(colorBGR);
  }
  
}

void
drawLines(u_int x_coord, u_int y_coord, u_int x_point, u_int y_point, u_int color)
{
  // bottom
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord + y_point, color);
  // top
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord - y_point, color);
  // and the middle two
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord + x_point, color);
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord - x_point, color);
					  
}

void
draw_circle(int x, int y, int r, u_int color)
{
  int x_coord = x;
  int y_coord = y;
  // first point will be the very top;
  int x_point = 0;
  int y_point = r;
  int decision = 3 - (2 * r);

  drawLines(x_coord, y_coord, x_point, y_point, color);

  while (y_point >= x_point) {
    // move x over one
    x_point++;

    // check decision point
    if (decision > 0) {
      // move y down one
      y_point--;
      decision = decision + 4 * (x_point - y_point) + 10;
    } else {
      decision = decision + 4 * x_point + 6;
    }
    drawLines(x_coord, y_coord, x_point, y_point, color);
  }
}

void
moving_circle(circle *cir)
{
  int x_vel=cir->xvel;
  int y_vel=cir->yvel;
  
  u_int color = COLOR_SIENNA;


  // draw at the new position
  draw_circle(cir->cir_x, cir->cir_y, cir->r, color);

  // save current position
  cir->old_cir_x = cir->cir_x;
  cir->old_cir_y = cir->cir_y;

  // update position
  cir->cir_x += x_vel;
  cir->cir_y += y_vel;
  
  // check boundaries, see if rectangle has hit the edges
  if ( (cir->cir_x + cir->r) >= screenWidth || (cir->cir_x - cir->r) <= 0) {
    // top or bottom hit, reverse x velocity
    cir->xvel= x_vel*-1;
  }
  if ( ( cir->cir_y - cir->r ) <= 0 ||            // left boundary
       ( cir->cir_y + cir->r ) >= screenHeight ) { // right boundary
    // right or left hit, reverse y velocity
    cir->yvel= y_vel*-1;
  }

  if(rect1.hit==1 && rect2.hit==1)
    {
      cir->xvel=0;
      cir->yvel=0;
    }
}

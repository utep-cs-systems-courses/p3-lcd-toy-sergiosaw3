#ifndef _DRAW_SHAPES_H_
#define _DRAW_SHAPES_H_

#include <lcdutils.h>

typedef struct rect_st {
  int rect_row;
  int rect_col;
  int old_rect_row;
  int old_rect_col;
  u_char height;
  u_char width;
  int xvel;
  int yvel;
  int hit;
} rectangle;

typedef struct cir_st {
  int cir_x;
  int cir_y;
  int old_cir_x;
  int old_cir_y;
  int r;
  int xvel;
  int yvel;
} circle;

typedef struct tri_st {
  int tri_row;
  int tri_col;
  int old_tri_row;
  int old_tri_col;
  u_char height;
  u_char width;
} triangle;

extern u_int background_color;

void change_vel1(void);
void change_vel2(void);
void change_vel3(void);
void change_vel4(void);

/* initializes shape positions */
void init_shapes(void);

/* handles erasing and updating all the shapes */
void draw_moving_shapes(void);

/* handles a single rectangle, updates its 
   position and draws it at its new location */
void moving_rectangle(rectangle* to_draw);

/* handles a single circle, updates its 
   position and draws it at its new location */
//void moving_circle(void);
void moving_circle(circle* to_draw);

/* draws a rectangle */
void draw_rectangle(void);

/* draws a triangle */
void draw_triangle(void);

void moving_triangle(triangle* to_draw);

/* draws a circle with the given parameters */
void draw_circle(int x, int y, int r, u_int color);

#endif // _DRAW_SHAPES_H_

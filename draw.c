#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z
Returns:
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
	// printf("%d\n", points -> lastcol);
	// printf("%d\n", points -> cols);
	if (points->lastcol == points->cols) {
		grow_matrix(points, (points->cols * 3) / 2 + 1);
	}
	points -> m[0][points -> lastcol] = x;
	points -> m[1][points -> lastcol] = y;
	points -> m[2][points -> lastcol] = z;
	points -> m[3][points -> lastcol] = 1;
	points -> lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns:
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge(struct matrix * points, double x0, double y0, double z0, double x1, double y1, double z1) {
	add_point(points, x0, y0, z0);
	add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c
Returns:
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
	int col;
	for (col = 0; col < points -> lastcol; col += 2) {
		draw_line(points -> m[0][col], points -> m[1][col], points -> m[0][col + 1], points -> m[1][col + 1], s, c);
	}
}



int get_octant(int x0, int y0, int x1, int y1) {
  int delta_x = x1 - x0;
  int delta_y = y1 - y0;

  if (delta_x >= delta_y && delta_y >= 0) {
    return 1;
  }
  if (delta_x <= delta_y && delta_y >= 0) {
    return 2;
  }
  if (delta_x >= -1 * delta_y && delta_y < 0) {
    return 8;
  }
  if (delta_x <= -1 * delta_y && delta_y < 0) {
    return 7;
  }


  printf("not right\n");
  return -1;
}

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  // f (x, y) = Ax + By + C
  if (x1 - x0 < 0) {
    draw_line(x1, y1, x0, y0, s, c);
  }
  else {
    int A,B,C,d,x,y;
    int octant = get_octant(x0, y0, x1, y1);
    if (octant < 0) {
      printf("something went wrong\n");
      exit(0);
    }
    x = x0;
    y = y0;
    A = y1 - y0;
    B = x0 - x1;
    C = 0;
    //octant 1
    if (octant == 1) {
      // printf("octant 1/5\n");
      d = 2 * A + B;
      while (x < x1) {
        plot (s, c, x, y);
        if (d > 0) {
          y++;
          d += 2 * B;
        }
        x++;
        d += 2 * A;
      }
    }

    else if (octant == 2) {
      // printf("octant 2/6\n");
      d = A + 2 * B;
      while (y < y1) {
        plot (s, c, x, y);
        if (d < 0) {
          x++;
          d += 2 * A;
        }
        y++;
        d += 2 * B;
      }
    }

    else if (octant == 7) {
      // printf("octant 3/7\n");
      d = A - 2 * B;
      while (y > y1) {
        plot (s, c, x, y);
        if (d > 0) {
          x++;
          d += 2 * A;
        }
        y--;
        d -= 2 * B;
      }
    }

    else {
      // printf("octant 4/8\n");
      d = 2 * A - B;
      while (x < x1) {
        plot (s, c, x, y);
        if (d < 0) {
          y--;
          d -= 2 * B;
        }
        x++;
        d += 2 * A;
      }
    }
  }
  // printf("finish\n");
}

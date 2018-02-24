#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  clear_screen(s);
  c.red = 240;
  c.green = 248;
  c.blue = 255;

  struct matrix * tester = new_matrix(2, 2);
  tester -> m[0][0] = 15;
  tester -> m[0][1] = 11;
  tester -> m[1][0] = 21;
  tester -> m[1][1] = 14;
  printf("Here's my test matrix:\n");
  print_matrix(tester);


  struct matrix * tester2 = new_matrix(2, 3);
  tester2 -> m[0][0] = 5;
  tester2 -> m[0][1] = 6;
  tester2 -> m[0][2] = 7;
  tester2 -> m[1][0] = 8;
  tester2 -> m[1][1] = 9;
  tester2 -> m[1][2] = 3;
  printf("Multiplying with the following matrix:\n");
  print_matrix(tester2);
  matrix_mult(tester, tester2);

  printf("The result:\n");
  print_matrix(tester2);

  printf("Let's multiply the following identity matrix with the result:\n");
  ident(tester);
  print_matrix(tester);

  printf("And we get...\n");
  matrix_mult(tester, tester2);
  print_matrix(tester2);
  free_matrix(tester);
  free_matrix(tester2);

  printf("Time to generate an image...!\n");
  struct matrix *edges;

  edges = new_matrix(4, 1);

  //top view
  c.red = 139;
  c.green = 69;
  c.blue = 19;
  add_edge(edges, 100, 175, 0, 100, 375, 0);
  add_edge(edges, 400, 175, 0, 400, 375, 0);
  add_edge(edges, 100, 175, 0, 250, 100, 0);
  add_edge(edges, 400, 175, 0, 250, 100, 0);
  add_edge(edges, 250, 100, 0, 250, 300, 0);

  draw_lines(edges, s, c);
  free(edges);

  edges = new_matrix(4, 1);

  c.red = 34;
  c.green = 139;
  c.blue = 34;

  add_edge(edges, 100, 375, 0, 250, 300, 0);
  add_edge(edges, 400, 375, 0, 250, 300, 0);
  add_edge(edges, 100, 375, 0, 250, 450, 0);
  add_edge(edges, 400, 375, 0, 250, 450, 0);

  draw_lines(edges, s, c);
  display(s);
  save_extension(s, "result.png");
  free_matrix( edges );
}

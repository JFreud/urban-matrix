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
  struct matrix *edges;

  edges = new_matrix(4, 4);
  ident(edges);
  struct matrix *mult_test = new_matrix(4,4);
  ident(mult_test);
  print_matrix(edges);

  mult_test -> m[0][0] = 30;

  print_matrix(mult_test);

  matrix_mult(edges, mult_test);
  print_matrix(mult_test);


  // draw_lines(edges, s, c);
  // display(s);
  free_matrix( edges );
}

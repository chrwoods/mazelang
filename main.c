#include "pair.h"
#include "io.c"
#include "solve.c"

int main(int argc, char* argv[]) {
  pair size;
  short* maze = load_maze("maze2.txt", &size);
  printf("Rows: %d, Cols: %d\n", size.row, size.col);
  print_maze(maze, size);
  free(maze);
  int num_de;
  pair* dead_ends = find_dead_ends(maze, size, &num_de);
  reduce_dead_ends(maze, size, dead_ends, num_de);
  print_maze(maze, size);
  set_islands(maze, size);
  print_maze(maze, size);
  int bisector = find_bisector(maze, size);
  printf("Found bisector at index %d.\n", bisector);
  pair start = find_start_pos(maze, size, bisector);
  printf("Found starting pos at %d, %d.\n", start.row, start.col);
  return 0;
}

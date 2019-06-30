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
  for(int i = 0; i < num_de; i++) {
    printf("Found dead end at %d, %d.\n", dead_ends[i].row, dead_ends[i].col);
  }
  return 0;
}

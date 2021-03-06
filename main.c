#include "pair.h"
#include "io.c"
#include "solve.c"

int main(int argc, char* argv[]) {
  char* to_load = "maze2.txt";
  if(argc > 1) {
    to_load = argv[1];
  }
  pair size;
  short* maze = load_maze(to_load, &size);
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
  pair path_start = find_path(maze, size, start);
  print_maze(maze, size);
  printf("Found path start at %d, %d.\n", path_start.row, path_start.col);
  int num_instructions;
  short* instructions = get_instructions(maze, size, path_start, &num_instructions);
  printf("Found %d instructions:\n", num_instructions);
  for(int i = 0; i < num_instructions; i++) {
    printf("%d ", instructions[i]);
  }
  printf("\n");
  return 0;
}

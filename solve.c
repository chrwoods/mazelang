//#include "pair.h"

pair* find_dead_ends(short* maze, pair size, int* num_de) {
  *num_de = 0;
  pair* dead_ends = NULL;
  for(int i = 1; i < size.row - 1; i++) {
    for(int j = 1; j < size.col - 1; j++) {
      if(maze[i * size.col + j]) continue;
      short num_walls = 0;
      for(short k = 0; k < 4; k++) {
	//check all direct edges of current cell
	num_walls += maze[(i + (((k % 2) ? -1 : 1) * (k / 2))) * size.col + j + ((k % 2) ? -1 : 1) * !(k / 2)];
      }
      if(num_walls == 3) {
	dead_ends = realloc(dead_ends, sizeof(pair) * ++(*num_de));
	pair dead_end;
	dead_end.row = i;
	dead_end.col = j;
	dead_ends[(*num_de) - 1] = dead_end;
      }
    }
  }
  return dead_ends;
}

short* reduce_dead_ends(short* maze, pair size, pair* dead_ends, int num_de) {
  
}

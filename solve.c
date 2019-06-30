//#include "pair.h"

pair get_dir(int num) {
  if(num < 0 || num >= 4) num = num % 4;
  if(num == 0) return (pair){-1, 0};
  else if(num == 1) return (pair){0, 1};
  else if(num == 2) return (pair){1, 0};
  else return (pair){0, -1};
}

int get_next_cell(short* maze, pair size, pair pos, pair dir) {
  if(pos.row + dir.row < 0 || pos.row + dir.row >= size.row) return -1;
  if(pos.col + dir.col < 0 || pos.col + dir.col >= size.col) return -1;
  return maze[(pos.row + dir.row) * size.col + pos.col + dir.col];
}

short find_num_walls(short* maze, pair size, pair pos) {
  short num_walls = 0;
  for(short d = 0; d < 4; d++) {
    //check all direct edges of current cell
    /*num_walls += maze[(pos.row + (((k % 2) ? -1 : 1) * (k / 2))) * size.col + pos.col + ((k % 2) ? -1 : 1) * !(k / 2)];*/
    //we count edges as walls
    num_walls += get_next_cell(maze, size, pos, get_dir(d)) ? 1 : 0;
  }
  return num_walls;
}

pair* find_dead_ends(short* maze, pair size, int* num_de) {
  *num_de = 0;
  pair* dead_ends = NULL;
  for(int i = 1; i < size.row - 1; i++) {
    for(int j = 1; j < size.col - 1; j++) {
      if(maze[i * size.col + j]) continue;
      pair pos = {i, j};
      if(find_num_walls(maze, size, pos) >= 3) {
	dead_ends = realloc(dead_ends, sizeof(pair) * ++(*num_de));
	dead_ends[(*num_de) - 1] = pos;
      }
    }
  }
  return dead_ends;
}

pair find_next_dir(short* maze, pair size, pair pos) {
  //we assume that we are in a dead end
  for(int d = 0; d < 4; d++) {
    pair dir = get_dir(d);
    if(!get_next_cell(maze, size, pos, dir)) return dir;
  }
  //this will only happen if the person is in a box
  return (pair){0, 0};
}

int reduce_dead_ends(short* maze, pair size, pair* dead_ends, int num_de) {
  for(int n = 0; n < num_de; n++) {
    pair pos = dead_ends[n];
    pair dir = {0, 0};
    while(find_num_walls(maze, size, pos) >= 3) {
      maze[pos.row * size.col + pos.col] = 1;
      short next_cell = get_next_cell(maze, size, pos, dir);
      if(next_cell == -1) {
	//maze is unsolvable, or we have gone horribly wrong somewhere
	//(assume unsolvable)
	return -1;
      } else if (next_cell == 1) {
	//find new direction
	dir = find_next_dir(maze, size, pos);
      }
      if(dir.row == 0 && dir.col == 0) break;
      pos.row += dir.row;
      pos.col += dir.col;
    }
  }
  return 0;
}

//#include "pair.h"

short get_cell(short* maze, pair size, pair pos) {
  return maze[pos.row * size.col + pos.col];
}

void set_cell(short* maze, pair size, pair pos, short val) {
  maze[pos.row * size.col + pos.col] = val;
}

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

void reduce_dead_ends(short* maze, pair size, pair* dead_ends, int num_de) {
  for(int n = 0; n < num_de; n++) {
    pair pos = dead_ends[n];
    pair dir = {0, 0};
    while(find_num_walls(maze, size, pos) >= 3) {
      maze[pos.row * size.col + pos.col] = 1;
      short next_cell = get_next_cell(maze, size, pos, dir);
      if(next_cell) {
	//find new direction
	dir = find_next_dir(maze, size, pos);
      }
      if(dir.row == 0 && dir.col == 0) break;
      pos.row += dir.row;
      pos.col += dir.col;
    }
  }
  free(dead_ends);
}

//currently deprecated
int find_endpoints(short* maze, pair size, pair* start, pair* end) {
  *start = (pair){0, 0};
  *end = (pair){0, 0};
  pair start_pos = {0, size.col - 1};
  while(!get_cell(maze, size, start_pos)) {
    start_pos.row++;
  }
  pair pos = start_pos;
  int dir_num = 1;
  //traverse the perimiter of the maze, clockwise
  do {
    //TODO
  } while(!(pos.row == start_pos.row && pos.col == start_pos.col));
  if(start->row == 0 && start->col == 0) return -3;
  if(end->row == 0 && end->col == 0) return -4;
  return 0;
}

int expand_island(short* maze, pair size, pair pos, short marker) {
  if(get_cell(maze, size, pos) != 1) return 0;

  set_cell(maze, size, pos, marker);
  int land = 1;

  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      if(i == 0 && j == 0) continue;
      if(pos.row + i < 0 || pos.row + i >= size.row) continue;
      if(pos.col + j < 0 || pos.col + j >= size.col) continue;
      pair new_pos = (pair){pos.row + i, pos.col + j};
      land += expand_island(maze, size, new_pos, marker);
    }
  }

  return land;
}

int set_islands(short* maze, pair size) {
  int total_land = 0;
  for(int i = 0; i < size.row; i++) {
    for(int j = 0; j < size.col; j++) {
      total_land += maze[i * size.col + j];
    }
  }

  for(int i = 0; i < size.row; i++) {
    for(int j = 0; j < size.col; j++) {
      if(maze[i * size.col + j]) {
	total_land -= expand_island(maze, size, (pair){i, j}, 2);
	i = size.row;
	break;
      }
    }
  }

  if(total_land <= 0) return -1;

  for(int i = size.row - 1; i >= 0; i--) {
    for(int j = size.col - 1; j >= 0; j--) {
      if(maze[i * size.col + j] == 1) {
	total_land -= expand_island(maze, size, (pair){i, j}, 3);
	i = size.row;
	break;
      }
    }
  }

  if(total_land > 0) return -2;
  return 0;
}

short check_bisector(short* maze, pair size, int index) {
  if(index < 0) {
    //check for a horizontal bisector
    index *= -1;
    if(index >= size.row) return -1;
    short check = 0;
    pair pos = {index, 0};
    for(pos.col = 0; pos.col < size.col; pos.col++) {
      switch(get_cell(maze, size, pos)) {
      case 0:
	continue;
	break;
      case 2:
	check |= 1;
	break;
      case 3:
	check |= 2;
	break;
      }
      if(check == 3) return 1;
    }
    return 0;
  } else {
    //check for a vertical bisector
    if(index >= size.col) return -1;
    short check = 0;
    pair pos = {0, index};
    for(pos.row = 0; pos.row < size.row; pos.row++) {
      switch(get_cell(maze, size, pos)) {
      case 0:
	continue;
	break;
      case 2:
	check |= 1;
	break;
      case 3:
	check |= 2;
	break;
      }
      if(check == 3) return 1;
    }
    return 0;
  }
}

int find_bisector(short* maze, pair size) {
  int index = size.col / 2;
  if(check_bisector(maze, size, index) == 1) return index;
  index = size.row / -2;
  if(check_bisector(maze, size, index) == 1) return index;
  index = (3 * size.col) / 4;
  if(check_bisector(maze, size, index) == 1) return index;
  index = size.col / 4;
  if(check_bisector(maze, size, index) == 1) return index;
  for(index = 1; index < size.col; index++) {
    if(check_bisector(maze, size, index) == 1) return index;
  }
  //we should never, ever get here
  return 0;
}

pair find_start_pos(short* maze, pair size, int bisector) {
  //note: currently we only support a one-wide maze
  if(bisector < 0) {
    pair cur;
    cur.row = bisector * -1;
    for(cur.col = 1; cur.col < size.col - 1; cur.col++) {
      if(get_cell(maze, size, cur) == 0) {
	if(get_next_cell(maze, size, cur, get_dir(1)) + get_next_cell(maze, size, cur, get_dir(3)) == 5) {
	  return cur;
	}
      }
    }
  } else {
    pair cur;
    cur.col = bisector;
    for(cur.row = 1; cur.row < size.row - 1; cur.row++) {
      if(get_cell(maze, size, cur) == 0) {
	if(get_next_cell(maze, size, cur, get_dir(0)) + get_next_cell(maze, size, cur, get_dir(2)) == 5) {
	  return cur;
	}
      }
    }
  }
  //this will only happen if the path is too wide
  return (pair){0, 0};
}

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "pair.h"

#define MAX_MAZE_WIDTH 50000

short* load_maze(char* filepath, pair* size) {
	FILE* fp;
	fp = fopen(filepath, "r");
	if (fp == NULL) {
		printf("File was not found at %s\n", filepath);
		return NULL;
	}
	//get size of maze
	size->row = 0;
	size->col = 0;
	char* line = malloc(sizeof(char) * MAX_MAZE_WIDTH);
	while (!feof(fp)) {
		int row_length;
		if(fgets(line, MAX_MAZE_WIDTH, fp) == NULL) break;
		row_length = strlen(line);
		if (line[row_length - 1] == '\n') row_length--;
		if (size->col < row_length) size->col = row_length;
		(size->row)++;
	}
	rewind(fp);
	//fill maze array
	short* maze = malloc(sizeof(short) * size->row * size->col);
	for (int i = 0; i < size->row; i++) {
		for (int j = 0; j < size->col; j++) {
			char c = fgetc(fp);
			printf("%c", c);
			if (c == '\n') {
				if (j == 0) {
					j--;
					continue;
				}
				// fill in the rest of the maze row
				while (j < size->col) {
					maze[i * size->col + j++] = 0;
				}
				break;
			}
			else if (c == ' ') {
				maze[i * size->col + j] = 0;
			}
			else {
				maze[i * size->col + j] = 1;
			}
		}
	}
	free(line);
	fclose(fp);
	return maze;
}

void print_maze(short* maze, pair size) {
  for (int i = 0; i < size.row; i++) {
    for (int j = 0; j < size.col; j++) {
      printf(maze[i * size.col + j] ? "#" : " ");
    }
    printf("\n");
  }
}

int main(int argc, char* argv[]) {
  pair size;
  short* maze = load_maze("maze1.txt", &size);
  printf("Rows: %d, Cols: %d\n", size.row, size.col);
  print_maze(maze, size);
  free(maze);
  return 0;
}

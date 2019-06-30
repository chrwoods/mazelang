#include <string.h>
#include <stdio.h>

#define MAX_MAZE_WIDTH 50000

short** load_maze(char* filepath, int* rows, int* cols) {
	FILE* fp;
	fp = fopen(filepath, "r");
	if (fp == NULL) {
		printf("File was not found at %s\n", filepath);
		return NULL;
	}
	//get size of maze
	*rows = 0;
	*cols = 0;
	char* line = malloc(sizeof(char) * MAX_MAZE_WIDTH);
	while (!feof(fp)) {
		int row_length;
		if(fgets(line, MAX_MAZE_WIDTH, fp) == NULL) break;
		row_length = strlen(line);
		if (line[row_length - 1] == '\n') row_length--;
		if (*cols < row_length) *cols = row_length;
		(*rows)++;
	}
	rewind(fp);
	//fill maze array
	short* maze = malloc(sizeof(short) * *rows * *cols);
	for (int i = 0; i < *rows; i++) {
		for (int j = 0; j < *cols; j++) {
			char c = fgetc(fp);
			printf("%c", c);
			if (c == '\n') {
				if (j == 0) {
					j--;
					continue;
				}
				// fill in the rest of the maze row
				while (j < *cols) {
					maze[i * *cols + j++] = 0;
				}
				break;
			}
			else if (c == ' ') {
				maze[i * *cols + j] = 0;
			}
			else {
				maze[i * *cols + j] = 1;
			}
		}
	}
	free(line);
	fclose(fp);
	return maze;
}

int main(int argc, char* argv[]) {
	int rows, cols;
	short* maze = load_maze("maze1.txt", &rows, &cols);
	printf("Rows: %d, Cols: %d\n", rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d", maze[i * cols + j]);
		}
		printf("\n");
	}
	free(maze);
	return 0;
}
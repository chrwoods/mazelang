#include <stdio.h>
#include <string.h>

**short load_maze(char* filepath, int* rows, int* cols) {
	FILE* fp;
	fp = fopen(filepath, "r");
	if (fp == 0) {
		printf("File was not found at %s\n", filepath);
		return null;
	}
	//get size of maze
	*rows = 0;
	*cols = 0;
	while (!feof(fp)) {
		char* line;
		fscanf(fp, "%[^\n]", line);
		int row_length = strlen(line);
		if (*cols < row_length) *cols = row_length;
		*rows++;
	}
}
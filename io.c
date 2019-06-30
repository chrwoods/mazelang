#include <string.h>
#include <stdio.h>

short** load_maze(char* filepath, int* rows, int* cols) {
	FILE* fp;
	fp = fopen(filepath, "r");
	if (fp == NULL) {
		printf("File was not found at %s\n", filepath);
		return 0;
	}
	//get size of maze
	*rows = 0;
	*cols = 0;
	char* line = malloc(1000);
	while (!feof(fp)) {
		size_t row_length;
		getline(line, &row_length, fp);
		if (*cols < row_length) *cols = row_length;
		*rows++;
		printf("%s\n", line);
	}
	free(line);
	fclose(fp);
	return 0;
}

int main(int argc, char* argv[]) {
	int rows, cols;
	short** maze = load_maze("maze1.txt", &rows, &cols);
	printf("Rows: %d, Cols: %d", rows, cols);
	return 0;
}
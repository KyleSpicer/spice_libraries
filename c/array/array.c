#include "array.h"

#include <stdio.h>
#include <stdlib.h>

char **create_char_matrix(int rows, int cols)
{
	if (!rows || !cols) {
		return NULL;
	}

	char **matrix = calloc(rows, sizeof(char *));

	if (!matrix) {
		printf("Unable to create matrix.\n");
		return NULL;
	}

	for (int i = 0; i < rows; i++) {
		matrix[i] = (char *)calloc(cols, sizeof(char));
		if (!matrix[i]) {
			printf("Unable to create column entry for matrix.\n");
			return NULL;
		}
	}

	return matrix;

}

void print_char_matrix(char **matrix, int rows, int cols)
{
	if (!matrix || !rows || !cols) {
		return;
	}
	printf("\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%c", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

void destroy_matrix(char **matrix, int rows)
{
	if (!*matrix || !rows) {
		return;
	}

	for (int i = 0; i < rows; i++) {
		free(matrix[i]);
	}
	free(matrix);
	matrix = NULL;

}

/* end of file */

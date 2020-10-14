#include <stdio.h>
#include <cstdlib>
#pragma warning (disable:4996)

int main() {
	FILE* inputFile = fopen("input.txt", "r");
	FILE* outputFile = fopen("output.txt", "w");

	int s;
	fscanf(inputFile, "%d", &s);

	int** sizes = new int*[s + 1];
	for (int i = 0; i < (s + 1); i++) {
		sizes[i] = new int[2];
		if (i != s)
			fscanf(inputFile, "%d %d", &sizes[i][0], &sizes[i][1]);
		else {
			sizes[i][0] = sizes[i - 1][1];
			sizes[i][1] = sizes[i - 1][1];
		}
	}

	int** answers = new int*[s + 1];
	for (int i = 0; i < (s + 1); i++) {
		answers[i] = new int[s + 1];
		for (int j = 0; j < (s + 1); j++) {
			answers[i][j] = 0;
		}
	}

	int j;
	for (int l = 2; l < (s + 1); l++) {
		for (int i = 1; i < (s+1 - l + 1); i++) {
			j = i + l - 1;
			answers[i][j] = INT_MAX;
			
			for (int k = i; k < j; k++) {
				if (answers[i][k] + answers[k + 1][j] + sizes[i - 1][0] * sizes[k][0] * sizes[j][0] < answers[i][j]) {
					answers[i][j] = answers[i][k] + answers[k + 1][j] + sizes[i - 1][0] * sizes[k][0] * sizes[j][0];
				}
			}
		}
	}
    /*
	for (int i = 0; i < (s + 1); i++) {
		for (j = 0; j < (s + 1); j++) {
			fprintf(outputFile, "%d ", answers[i][j]);
		}
		fprintf(outputFile, "\n");
	}*/

	fprintf(outputFile, "%d", answers[1][s]);

	return 0;
}

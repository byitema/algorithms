#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int main() {
	FILE* inputFile = fopen("input.txt", "r");
	FILE* outputFile = fopen("output.txt", "w");
	
	int n;
	fscanf(inputFile, "%d", &n);
	int* lilies = (int*)malloc(n*sizeof(int));

	int tmp, i = 0;
	while (fscanf(inputFile, "%d", &tmp) != EOF) {
		lilies[i] = tmp;
		i++;
	}

	if (n == 1) {
		fprintf(outputFile, "%d", lilies[0]);
		return 0;
	}
	else if (n == 2) {
		fprintf(outputFile, "-1");
		return 0;
	}

	int* answers = (int*)malloc(n*sizeof(int));
	answers[0] = lilies[0];
	answers[1] = -1;
	answers[2] = lilies[0] + lilies[2];
	for (int j = 3; j < n; j++) {
		if (answers[j - 2] > answers[j - 3]) {
			answers[j] = answers[j - 2];
		}
		else {
			answers[j] = answers[j - 3];
		}
		answers[j] += lilies[j];
	}

	fprintf(outputFile, "%d", answers[n - 1]);
	return 0;
}

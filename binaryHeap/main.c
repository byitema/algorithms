#include <stdio.h>
#include <cstdlib>
#pragma warning (disable: 4996)

int main() {
	FILE* in = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");

	int n;
	fscanf(in, "%d", &n);

	int* vec = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		fscanf(in, "%d", &vec[i]);
	}

	short isEnd = 0;
	int j = 0;
	for (int i = 1; i < n; i++) {
		i % 2 == 0 ? j = i / 2 - 1 : j = i / 2;
		if (vec[j] > vec[i]) {
			fprintf(out, "No");
			isEnd = 1;
			break;
		}
	}

	if (isEnd == 0) {
		fprintf(out, "Yes");
	}

	return 0;
}

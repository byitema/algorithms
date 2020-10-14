#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#pragma warning (disable:4996)

int main() {
	FILE* inputFile = fopen("input.txt", "r");
	FILE* outputFile = fopen("output.txt", "w");

	const char* str = (const char*)malloc(7001 * sizeof(const char));
	fscanf(inputFile, "%s", str);

	int n = strlen(str);

	if (n == 1) {
		fprintf(outputFile, "1\n%s", str);
		return 0;
	}
	else if (n == 2) {
		if (str[0] == str[1]) {
			fprintf(outputFile, "2\n%s", str);
			return 0;
		}
		else {
			fprintf(outputFile, "1\n%c", str[0]);
			return 0;
		}
	}

	int** answers = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		answers[i] = (int*)malloc(n * sizeof(int));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				answers[i][j] = 1;
			}
			else if (i == (j - 1)) {
				if (str[i] == str[i + 1]) {
					answers[i][j] = 2;
				}
				else {
					answers[i][j] = 1;
				}
			}
			else {
				answers[i][j] = INT_MAX;
			}
		}
	}

	int j;
	for (int k = 2; k < n; k++) {
		for (int i = 0; i < n; i++) {
			if (i + k < n) {
				j = i + k;
				if (str[i] == str[j]) {
					answers[i][j] = answers[i + 1][j - 1] + 2;
				}
				else {
					if (answers[i + 1][j] > answers[i][j - 1]) {
						answers[i][j] = answers[i + 1][j];
					}
					else {
						answers[i][j] = answers[i][j - 1];
					}
				}
			}
		}
	}
	//доделать
	std::vector<char> answer;
	int i = 0;
	j = n - 1;
	while (/*i != j && */i != n && j != 0 && answers[i][j] != INT_MAX) {
		if (str[i] == str[j]) {
			answer.push_back(str[j]);
			i++;
			j--;
		}
		else {
			if (answers[i + 1][j] >= answers[i][j - 1]) {
				i++;
			}
			else {
				j--;
			}
		}
	}
	//
	/*for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fprintf(outputFile, "%d\t\t\t", answers[i][j]);
		}
		fprintf(outputFile, "\n");
	}*/

	fprintf(outputFile, "%d\n", answers[0][n - 1]);

	for (char c : answer) {
		fprintf(outputFile, "%c", c);
	}
	
	if (answers[0][n - 1] % 2 == 0) {
		for (i = 0; i < answer.size(); i++) {
			fprintf(outputFile, "%c", answer[answer.size()-1-i]);
		}
	}
	else {
		for (i = 1; i < answer.size(); i++) {
			fprintf(outputFile, "%c", answer[answer.size() - 1 - i]);
		}
	}

	//fprintf(outputFile, "\n%s %d", str, n);

	return 0;
}

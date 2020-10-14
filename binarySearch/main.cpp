#include <stdio.h>
#include <iostream>
#pragma warning (disable:4996)

int binarySearchLeft(int num, int* vec, int length) {
	int left = 0, right = length;
	int middle;
	while (left < right) {
		middle = (left + right) / 2;
		if (num <= vec[middle]) {
			right = middle;
		}
		else {
			left = middle + 1;
		}
	}
	return left;
}

int binarySearchRight(int num, int* vec, int length) {
	int left = 0, right = length;
	int middle;
	while (left < right) {
		middle = (left + right) / 2;
		if (num < vec[middle]) {
			right = middle;
		}
		else {
			left = middle + 1;
		}
	}
	return left;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	scanf("%d", &n);

	int tmp;
	int* vec = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		vec[i] = tmp;
	}

	int k;
	scanf("%d", &k);

	int leftResult, rightResult;
	for (int i = 0; i < k; i++) {
		scanf("%d", &tmp);
		leftResult = binarySearchLeft(tmp, vec, n);
		rightResult = binarySearchRight(tmp, vec, n);
		if ((rightResult - leftResult) == 0) {
			printf("0 ");
		}
		else {
			printf("1 ");
		}
		printf("%d %d\n", leftResult, rightResult);
	}
}

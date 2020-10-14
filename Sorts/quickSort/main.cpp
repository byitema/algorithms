#include <iostream>
using namespace std;

void my_quick_sort(int array[], int left, int right) {
	int tmp_left = left; int tmp_right = right;
	int tmp;
	int middle = array[(left + right) / 2];

	while (tmp_left <= tmp_right) {
		while (array[tmp_left] < middle)
			tmp_left++;
		while (array[tmp_right] > middle)
			tmp_right--;
		if (tmp_left <= tmp_right) {
			tmp = array[tmp_left];
			array[tmp_left] = array[tmp_right];
			array[tmp_right] = tmp;
			tmp_left++; tmp_right--;
		}
	}

	if (left < tmp_right)
		my_quick_sort(array, left, tmp_right);
	if (tmp_left < right)
		my_quick_sort(array, tmp_left, right);
}

int main() {
	int n; cin >> n;
	int *array = new int[n];
	for (int i = 0; i < n; i++)
		cin >> array[i];
	my_quick_sort(array, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
}

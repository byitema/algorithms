#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	long long n;
	fin >> n;

	std::vector<bool> binaryDigits;
	long long tmp = n;
	while (tmp != 0 && tmp != 1) {
		binaryDigits.push_back(tmp % 2);
		tmp /= 2;
	}
	binaryDigits.push_back(tmp);

	std::vector<long long> answer;
	for (long long i = (binaryDigits.size() - 1); i >= 0; i--) {
		if (binaryDigits[i] == 1) answer.push_back(i);
	}

	for (long long i = (answer.size() - 1); i >= 0; i--) {
		fout << answer[i] << '\n';
	}
	
	return 0;
}

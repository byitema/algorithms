#include <iostream>
#include <vector>

#define MOD 1000000007

long long Cnk(long long n, long long k) {
	if (n == 0 || k == 0) {
		return 1;
	}
	else if (n == k) {
		return 1;
	}
	else if (k == 1) {
		return n % MOD;
	}

	return Cnk(n - 1, k - 1) % MOD + Cnk(n - 1, k) % MOD;
}

int main() {
	long long n, k;
	std::cin >> n >> k;

	std::vector<std::vector<long long>> vec(n + 1, std::vector<long long>(n + 1));

	if (k == 0 || n == 0) {
		std::cout << 1;
		return 0;
	}
	else if (k == 0) {
		std::cout << 1;
		return 0;
	}

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			if (i == j) {
				vec[i][j] = 1;
			}
			else if (j == 0){
				vec[i][j] = 1;
			}
			else {
				vec[i][j] = -1;
			}
		}
	}

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j <		i; j++) {
			if (i == j) {
				vec[i][j] = 1;
			}
			else {
				vec[i][j] = (vec[i - 1][j - 1] % MOD + vec[i - 1][j] % MOD) % MOD;
			}
		}
	}

	std::cout << vec[n][k];
	return 0;
}

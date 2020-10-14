#include <fstream>
#include <stdio.h>
#include <set>
#include <string>
#pragma warning (disable:4996)
using namespace std;

int main() {
	ifstream ifs("input.txt");
	ofstream ofs("output.txt");

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	set<long long> mySet;

	long long s;
	while (true) {
		if (ifs.eof())
			break;
		ifs >> s;
		mySet.insert(s);
	}

	long long sum = 0;
	for (long long i : mySet) {
		sum += i;
	}

	ofs << sum;

	return 0;
}

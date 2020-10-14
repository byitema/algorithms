#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
	ifstream fin("rect.in");
	ofstream fout("rect.out");

	long long xMax, yMax, n;
	fin >> xMax >> yMax >> n;

	int x0, y0, x1, y1;
	vector<tuple<long long, long long, long long, long long>> cords;
	for (long long i = 0; i < n; i++) {
		fin >> x0 >> y0 >> x1 >> y1;
		cords.push_back(make_tuple(x0, y0, x1, y1));
	}
	/*
	int counter = 0;
	int counterMax = 0;
	pair<int, int> crds;
	for (int i = 0; i <= yMax; i++) {
		counter = 0;
		for (int j = 0; j < n; j++) {
			if ((i * get<0>(cords[j]) - xMax * get<3>(cords[j]))* (i * get<2>(cords[j]) - xMax * get<1>(cords[j])) > 0) {
				continue;
			}
			else {
				counter++;
			}
		}
		if (counter > counterMax) {
			counterMax = counter;
			crds = make_pair(xMax, i);
		}
	}
	for (int i = 0; i < xMax; i++) {
		counter = 0;
		for (int j = 0; j < n; j++) {
			if ((yMax * get<0>(cords[j]) - i * get<3>(cords[j]))* (yMax * get<2>(cords[j]) - i * get<1>(cords[j])) > 0) {
				continue;
			}
			else {
				counter++;
			}
		}
		if (counter > counterMax) {
			counterMax = counter;
			crds = make_pair(i, yMax);
		}
	}

	fout << counterMax << " " << crds.first << " " << crds.second;
	*/

	vector<long long> openingCordsVERT;
	vector<long long> closingCordsVERT;
	vector<long long> openingCordsHOR;
	vector<long long> closingCordsHOR;

	long double tmp;
	for (long long i = 0; i < n; i++) {
		tmp = get<1>(cords[i]) * xMax / (double)get<2>(cords[i]);
		if (tmp <= yMax) {
			openingCordsVERT.push_back((long long)(ceil(tmp)));
		}
		else {
			if (get<1>(cords[i]) != 0) {
				openingCordsHOR.push_back((long long)(get<2>(cords[i]) * yMax / (long double)get<1>(cords[i])));
			}
			else {
				openingCordsVERT.push_back(0);
			}
		}
		
		if (get<0>(cords[i]) != 0) {
			tmp = get<3>(cords[i]) * xMax / (long double)get<0>(cords[i]);
			if (tmp <= yMax) {
				closingCordsVERT.push_back((long long)(tmp));
			}
			else {
				closingCordsHOR.push_back((long long)(ceil(get<0>(cords[i]) * yMax / (long double)get<3>(cords[i]))));
			}
		}
		else {
			closingCordsHOR.push_back(0);
		}
	}


	sort(openingCordsHOR.rbegin(), openingCordsHOR.rend());

	sort(openingCordsVERT.rbegin(), openingCordsVERT.rend());

	sort(closingCordsHOR.rbegin(), closingCordsHOR.rend());

	sort(closingCordsVERT.rbegin(), closingCordsVERT.rend());

	long long counter = 0;
	long long counterMax = 0;
	pair<long long, long long> cordsMax = make_pair(0, 0);


	long long o = openingCordsVERT.size() - 1;
	long long c = closingCordsVERT.size() - 1;

	bool emp1 = openingCordsVERT.empty();
	bool emp2 = closingCordsVERT.empty();
	if (!emp1 && !emp2) {
		while (true) {
			if ((openingCordsVERT[o] <= closingCordsVERT[c])) {
				counter++;
				if (counter > counterMax) {
					counterMax = counter;
					cordsMax = make_pair(xMax, openingCordsVERT[o]);
				}
				o--;
			}
			else {
				counter--;
				c--;
			}
			if (o == -1 || c == -1) {
				break;
			}
		}
	}
	if (o == -1) {
		while (c != -1) {
			counter--;
			c--;
		}
	}
	else {
		while (o != -1) {
			counter++;
			if (counter > counterMax) {
				counterMax = counter;
				cordsMax = make_pair(xMax, openingCordsVERT[o]);
			}
			o--;
		}
	}

	o = 0;
	c = 0;
	emp1 = openingCordsHOR.empty();
	emp2 = closingCordsHOR.empty();
	if (!emp1 && !emp2) {
		while (true) {
			if (openingCordsHOR[o] >= closingCordsHOR[c]) {
				counter++;
				if (counter > counterMax) {
					counterMax = counter;
					cordsMax = make_pair(openingCordsHOR[o], yMax);
				}
				o++;
			}
			else {
				counter--;
				c++;
			}
			if (o == openingCordsHOR.size()) {
				break;
			}
		}
	}

	fout << counterMax << " " << cordsMax.first << " " << cordsMax.second;
	
	return 0;
}

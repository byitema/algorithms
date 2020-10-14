#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <stack>
using namespace std;


int main() {
	ifstream fin("maze.in");
	ofstream fout("maze.out");

	int m, n;
	fin >> m >> n;
	int xStart, yStart, xFinish, yFinish;
	fin >> xStart >> yStart;
	fin >> xFinish >> yFinish;

	vector<vector<int>> labirinth(m + 2, vector<int>(n + 2));
	//ввод
	int tmp;
	for (int i = 0; i < m + 2; i++) {
		for (int j = 0; j < n + 2; j++) {
			if (i != 0 && i != m + 1 && j != 0 && j != n + 1) {
				fin >> tmp;
				if (tmp == 1) {
					labirinth[i][j] = 1;
				}
				else {
					labirinth[i][j] = 0;
				}
			}
			else {
				labirinth[i][j] = 0;
			}
		}
	}
	
	/*for (int i = 0; i < m + 2; i++) {
		for (int j = 0; j < n + 2; j++) {
			fout << labirinth[i][j] << " ";
		}
		fout << "\n";
	}fout << "\n";*/

	//в очередь закидываю все что равны 1 рядом с уже находящимися в очереди
	queue<pair<int, int>> ueue;
	ueue.push(make_pair(xStart, yStart));
	labirinth[xStart][yStart] = 2;
	bool start = false;
	bool middle = false;
	while (!ueue.empty()) {
		if (labirinth[ueue.front().first + 1][ueue.front().second] == 1) {
			ueue.push(make_pair(ueue.front().first + 1, ueue.front().second));
			labirinth[ueue.front().first + 1][ueue.front().second] = labirinth[ueue.front().first][ueue.front().second] + 1;
			/*if (!middle) {
				labirinth[ueue.front().first + 1][ueue.front().second] = labirinth[ueue.front().first][ueue.front().second] + 2;
				middle = true;
			}
			else {
				labirinth[ueue.front().first + 1][ueue.front().second] = labirinth[ueue.front().first][ueue.front().second] + 1;
			}*/
		}
		if (labirinth[ueue.front().first][ueue.front().second + 1] == 1) {
			ueue.push(make_pair(ueue.front().first, ueue.front().second + 1));
			labirinth[ueue.front().first][ueue.front().second + 1] = labirinth[ueue.front().first][ueue.front().second] + 1;
		}
		if (labirinth[ueue.front().first][ueue.front().second - 1] == 1) {
			ueue.push(make_pair(ueue.front().first, ueue.front().second - 1));
			labirinth[ueue.front().first][ueue.front().second - 1] = labirinth[ueue.front().first][ueue.front().second] + 1;
		}
		
		if (labirinth[ueue.front().first - 1][ueue.front().second] == 1) {
			ueue.push(make_pair(ueue.front().first - 1, ueue.front().second));
			labirinth[ueue.front().first - 1][ueue.front().second] = labirinth[ueue.front().first][ueue.front().second] + 1;
		}

		/*if (!start) {
			labirinth[ueue.front().first][ueue.front().second] = 0;
			start = true;
		}*/
		if (ueue.front().first == xFinish && ueue.front().second == yFinish) {
			break;
		}
		ueue.pop();
	}
	
	/*for (int i = 0; i < m + 2; i++) {
		for (int j = 0; j < n + 2; j++) {
			fout << labirinth[i][j] << "                 ";
		}
		fout << "\n";
	}*/
	
	stack<pair<int, int>> ue;
	if (labirinth[xFinish][yFinish] == 0 || labirinth[xFinish][yFinish] == 1) {
		fout << (-1);
	}
	else {

		//fout << labirinth[xFinish][yFinish] - 2 << "\n";
		//ue.push(make_pair(xStart, yStart));
		int xCur = xFinish;
		int yCur = yFinish;
		while (labirinth[xCur][yCur] != 2) {
			ue.push(make_pair(xCur, yCur));
			//fout << xCur << " " << yCur << "\n";
			if (labirinth[xCur][yCur] == (labirinth[xCur + 1][yCur] + 1)) {
				xCur++;
			}
			else if (labirinth[xCur][yCur] == (labirinth[xCur][yCur + 1] + 1)) {
				yCur++;
			}
			else if (labirinth[xCur][yCur] == (labirinth[xCur - 1][yCur] + 1)) {
				xCur--;
			}
			else if (labirinth[xCur][yCur] == (labirinth[xCur][yCur - 1] + 1)) {
				yCur--;
			}
		}
		fout << ue.size() << "\n";
		fout << xStart << " " << yStart << "\n";
		while (!ue.empty()) {
			fout << ue.top().first << " " << ue.top().second << "\n";
			ue.pop();
		}
		//fout << xFinish << " " << yFinish;
		//fout << xFinish << " " << yFinish << "\n";
	}
	
	/*
	vector<pair<int, int>> road;
	if (labirinth[xFinish][yFinish]){
		fout << (-1);
	}
	else {
		int xCur = xFinish;
		int yCur = yFinish;
		road.push_back(make_pair(xCur, yCur));
		while (xCur != xStart || yCur != yStart) {
			if (root[xCur][yCur] == 'u') {
				xCur--;
				road.push_back(make_pair(xCur, yCur));
			} else if (root[xCur][yCur] == 'd') {
				xCur++;
				road.push_back(make_pair(xCur, yCur));
			} else if (root[xCur][yCur] == 'r') {
				yCur++;
				road.push_back(make_pair(xCur, yCur));
			} else if (root[xCur][yCur] == 'l') {
				yCur--;
				road.push_back(make_pair(xCur, yCur));
			}

		}
		road.push_back(make_pair(xStart, yStart));
		int s = road.size();
		fout << (s - 2) << "\n";
		for (int i = (s - 1); i > 0; i--) {
			fout << road[i - 1].first << " " << road[i - 1].second << "\n";
		}
	}*/
	return 0;
}

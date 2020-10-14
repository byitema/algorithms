#include <iostream>
#include <stdio.h>
#include <vector>
#include <deque>
#include <queue>
#include <fstream>
#pragma warning (disable: 4996)
using namespace std;

void findMinVertex(int* distance, bool* visited, int n, int& minVertex) {
	minVertex = -234;
	for (int i = 0; i < n; i++) {
		if (!visited[i] && (minVertex == -234 || distance[i] < distance[minVertex])) {
			minVertex = i;
		}
	}
	minVertex++;
}

int main() {
	freopen("minpath.in", "r", stdin);
	//ifstream fin("minpath.in");
	int n, m, a, b;
	scanf("%d%d", &n, &m);
	//fin >> n >> m;
	scanf("%d%d", &a, &b);
	//fin >> a >> b;
	vector<pair<int, int>>* adjacencyList = new vector<pair<int, int>>[n];
	int tmp1, tmp2, tmp3;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &tmp1, &tmp2, &tmp3);
		//fin >> tmp1 >> tmp2 >> tmp3;
		if (tmp1 == tmp2) {
			continue;
		}
		else {
			adjacencyList[tmp1 - 1].push_back(make_pair(tmp2 - 1, tmp3));
		}
	}
	freopen("minpath.out", "w", stdout);
	//ofstream fout("minpath.out");
	if (adjacencyList[a - 1].size() == 0) {
		printf("0");
		//fout << "0";
		return 0;
	}
	else if (adjacencyList[a - 1].size() == 1) {
		if (adjacencyList[a - 1][0].first == (b - 1)) {
			printf("%d\n%d %d", adjacencyList[a - 1][0].second, a, b);
			//fout << adjacencyList[a - 1][0].second << "\n" << a << " " << b;
			return 0;
		}
	}
	int* distance = new int[n];
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++) {
		if (i != (a - 1)) {
			distance[i] = INT_MAX;
		}
		else {
			distance[i] = 0;
		}
		visited[i] = false;
	}

	int* whereFrom = new int[n];

	int minVertex;
	for (int i = 0; i < n; i++) {
		findMinVertex(distance, visited, n, minVertex);
		if (distance[minVertex - 1] == INT_MAX) break;
		visited[minVertex - 1] = true;
		for (int j = 0; j < adjacencyList[minVertex - 1].size(); j++) {
			if (distance[adjacencyList[minVertex - 1][j].first] > distance[minVertex - 1] + adjacencyList[minVertex - 1][j].second) {
				distance[adjacencyList[minVertex - 1][j].first] = distance[minVertex - 1] + adjacencyList[minVertex - 1][j].second;
				whereFrom[adjacencyList[minVertex - 1][j].first] = minVertex - 1;
			}
		}
	}
	
	if (distance[b - 1] == INT_MAX) {
		printf("%d", 0);
		//fout << "0";
		return 0;
	}
	else {
		printf("%d\n", distance[b - 1]);
		//fout << distance[b - 1] << "\n";
		deque<int> road;
		while (b != a) {
			road.push_back(b);
			b = whereFrom[b - 1] + 1;
		}
		printf("%d ", a);
		//fout << a << " ";
		while (!road.empty()) {
			printf("%d ", road.back());
			//fout << road.back() << " ";
			road.pop_back();
		}
		return 0;
	}
}

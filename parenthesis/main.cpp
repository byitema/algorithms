#include <iostream>
#include <stack>
#include <string>
using namespace std;
#pragma warning(disable : 4996)

int main() {
	
	//freopen("smiles.in", "r", stdin);
	//freopen("smiles.out", "w", stdout);

	int n; cin >> n;
	cin.ignore(numeric_limits<size_t>::max(), '\n');

	string* sentences = new string[n];

	for (int i = 0; i < n; i++) {
		getline(cin, sentences[i]);
	}

	stack <char> parentheses;

	for (int i = 0; i < n; i++) {
		int answer = 0;
		
		for (int j = 0; j < sentences[i].length(); j++) {
			if (j < (sentences[i].length() - 1) && sentences[i][j] == ':' && sentences[i][j+1] != ':') {
				j++;
				continue;
			}
			/*if (j > 0 && sentences[i][j-1] == ':')
				continue;*/
			if (sentences[i][j] == '(' || sentences[i][j] == '[' || sentences[i][j] == '{') {
				parentheses.push(sentences[i][j]);
				continue;
			}
			if (sentences[i][j] == ')' || sentences[i][j] == ']' || sentences[i][j] == '}'){
				if (parentheses.empty()){
					answer = 1;
					break;
				}
				else {
					if ((parentheses.top() == '(' && sentences[i][j] != ')') || (parentheses.top() == '[' && sentences[i][j] != ']') || (parentheses.top() == '{' && sentences[i][j] != '}')) {
						answer = 2;
						break;
					}
					parentheses.pop();
				}
			}
			/*if (parentheses.empty()) {
				if (sentences[i][j] == ')' || sentences[i][j] == ']' || sentences[i][j] == '}') {
					answer = 1;
					break;
				}
			}*/
			/*if (sentences[i][j] == ')') {
				if (parentheses.empty()) {
					answer = 1;
					break;
				}
				if (parentheses.top() == '[' || parentheses.top() == '{') {
					answer = 2;
					break;
				}
				parentheses.pop();
			}
			if (sentences[i][j] == ']') {
				if (parentheses.empty()) {
					answer = 1;
					break;
				}
				if (parentheses.top() == '(' || parentheses.top() == '{') {
					answer = 2;
					break;
				}
				parentheses.pop();
			}
			if (sentences[i][j] == '}') {
				if (parentheses.empty()) {
					answer = 1;
					break;
				}
				if (parentheses.top() == '(' || parentheses.top() == '[') {
					answer = 2;
					break;
				}
				parentheses.pop();
			}*/
			
		}
		if (!parentheses.empty() && answer == 0)
			answer = 3;
		cout << answer << endl;
		while (!parentheses.empty())
			parentheses.pop();
	}

	delete[] sentences;
	return 0;
}

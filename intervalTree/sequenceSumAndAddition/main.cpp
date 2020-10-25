#include <iostream>
#include <string>

void createIntervalTree(long long* seq, long long* tree, long long father, long long newLeft, long long newRight) {
	if (newRight - newLeft == 1) {
		tree[father] = seq[newLeft];
		return;
	}

	long long medium = (newLeft + newRight) / 2;
	long long child = 2 * father;

	createIntervalTree(seq, tree, child, newLeft, medium);
	createIntervalTree(seq, tree, child + 1, medium, newRight);
	tree[father] = tree[child] + tree[child + 1];
}

void addition(long long* tree, long long &i, long long &x, long long father, long long newLeft, long long newRight) {
	if (newRight - newLeft == 1) {
		tree[father] += x;
		return;
	}

	long long medium = (newLeft + newRight) / 2;
	long long child = 2 * father;

	if (i < (newLeft + newRight) / 2) {
		addition(tree, i, x, child, newLeft, medium);
		tree[father] = tree[child] + tree[child + 1];
		return;
	}
	else {
		addition(tree, i, x, child + 1, medium, newRight);
		tree[father] = tree[child] + tree[child + 1];
		return;
	}
}

long long sum(long long* tree, long long &l, long long &r, long long father, long long newLeft, long long newRight) {
	if (newLeft == l && newRight == r) {
		return tree[father];
	}

	long long medium = (newLeft + newRight) / 2;
	long long child = 2 * father;

	if (r <= medium) {
		return sum(tree, l, r, child, newLeft, medium);
	}

	if (medium <= l) {
		return sum(tree, l, r, child + 1, medium, newRight);
	}
	
	return (sum(tree, l, medium, child, newLeft, medium) + sum(tree, medium, r, child + 1, medium, newRight));
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	long long n, q;

	std::cin >> n;
	long long* sequence = new long long[n];

	for (long long i = 0; i < n; i++) {
		std::cin >> sequence[i];
	}

	long long* intervalTree = new long long[4 * n]();
	createIntervalTree(sequence, intervalTree, 1, 0, n);

	/* creating right!
	for (int i = 0; i < 4 * n; i++) {
		std::cout << intervalTree[i] << " ";
	}
	*/
	
	std::cin >> q;
	std::string command;
	long long i, x, l, r;
	for (long long index = 0; index < q; index++) {
		std::cin >> command;
		if (command.compare("FindSum") == 0) {
			std::cin >> l;
			std::cin >> r;
			std::cout << sum(intervalTree, l, r, 1, 0, n) << '\n';
		}
		else {
			std::cin >> i;
			std::cin >> x;
			addition(intervalTree, i, x, 1, 0, n);
			/* addition right!
			for (int ind = 0; ind < 4 * n; ind++) {
				std::cout << intervalTree[ind] << " ";
			}
			*/
		}
	}

	/* reading command right!
	std::cout << command;
	*/

	return 0;
}

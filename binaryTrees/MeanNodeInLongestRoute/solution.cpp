#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <deque>
#pragma warning (disable: 4996)

struct BinaryTreeNode {
	long long data;
	long long height;
	long long leftHeight;
	long long rightHeight;
	long long ifRootPathLength;
	struct BinaryTreeNode* right;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* parent;
};

struct BinaryTree {
	struct BinaryTreeNode* root;
};

struct BinaryTreeNode* createNode(long long data) {
	struct BinaryTreeNode* newNode = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));

	newNode->data = data;
	newNode->height = -1;
	newNode->leftHeight = -1;
	newNode->rightHeight = -1;
	newNode->ifRootPathLength = 0;
	newNode->right = NULL;
	newNode->left = NULL;
	newNode->parent = NULL;

	return newNode;
}

struct BinaryTree* createTree(struct BinaryTreeNode* node) {
	struct BinaryTree* newTree = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));

	newTree->root = node;

	return newTree;
}

struct BinaryTreeNode* find(struct BinaryTreeNode* node, long long data) {
	if (node == NULL) {
		return NULL;
	}
	if (node->data == data) {
		return node;
	}
	else if (node->data > data) {
		find(node->left, data);
	}
	else {
		find(node->right, data);
	}
}

struct BinaryTreeNode* findMin(struct BinaryTreeNode* node) {
	if (node->left == NULL) {
		return node;
	}
	else {
		return findMin(node->left);
	}
}

void insertNode(struct BinaryTreeNode* node, long long data) {
	if (node->data > data) {
		if (node->left == NULL) {
			node->left = createNode(data);
			node->left->parent = node;
		}
		else {
			insertNode(node->left, data);
		}
	}
	else if (node->data < data) {
		if (node->right == NULL) {
			node->right = createNode(data);
			node->right->parent = node;
		}
		else {
			insertNode(node->right, data);
		}
	}
}

void deleteNode(struct BinaryTreeNode* node, long long data, struct BinaryTree* tree) {
	if (node == NULL) {
		return;
	}

	struct BinaryTreeNode* neededToDelete = find(node, data);

	if (neededToDelete == NULL) {
		return;
	}

	if (neededToDelete->right == NULL && neededToDelete->left == NULL) {
		if (neededToDelete->parent != NULL) {
			if (neededToDelete->parent->left == neededToDelete) {
				neededToDelete->parent->left = NULL;
			}
			else {
				neededToDelete->parent->right = NULL;
			}
			return;
		}
		tree->root = NULL;
		return;
	}

	if (neededToDelete->right == NULL) {
		if (neededToDelete->parent != NULL) {
			if (neededToDelete->parent->left == neededToDelete) {
				neededToDelete->parent->left = neededToDelete->left;
			}
			else {
				neededToDelete->parent->right = neededToDelete->left;
			}
			neededToDelete->left->parent = neededToDelete->parent;
			return;
		}
		neededToDelete->left->parent = neededToDelete->parent;
		tree->root = neededToDelete->left;
		return;
	}

	if (neededToDelete->left == NULL) {
		if (neededToDelete->parent != NULL) {
			if (neededToDelete->parent->left == neededToDelete) {
				neededToDelete->parent->left = neededToDelete->right;
			}
			else {
				neededToDelete->parent->right = neededToDelete->right;
			}
			neededToDelete->right->parent = neededToDelete->parent;
			return;
		}
		neededToDelete->right->parent = neededToDelete->parent;
		tree->root = neededToDelete->right;
		return;
	}

	struct BinaryTreeNode* min = findMin(neededToDelete->right);
	neededToDelete->data = min->data;
	deleteNode(neededToDelete->right, min->data, tree);
}

void leftInOrderTraversal(struct BinaryTreeNode* node, FILE* fout) {
	fprintf(fout, "%lld\n", node->data);

	if (node->left != NULL) {
		leftInOrderTraversal(node->left, fout);
	}

	if (node->right != NULL) {
		leftInOrderTraversal(node->right, fout);
	}
}

//считаем высоты и записываем корни максимальных путей
std::vector<struct BinaryTreeNode*> maxRootsRL;
std::vector<struct BinaryTreeNode*> maxRootsLL;
long long MAXPATHLENGTH = LLONG_MIN;
void rootsWithMaxPathes(struct BinaryTreeNode* node) {
	if (node->left != NULL) {
		rootsWithMaxPathes(node->left);
	}

	if (node->right != NULL) {
		rootsWithMaxPathes(node->right);
	}

	if (node->left == NULL && node->right == NULL) {
		node->height = 0;
		node->leftHeight = -1;
		node->rightHeight = -1;
		node->ifRootPathLength = 0;

		if (MAXPATHLENGTH < 0) {
			maxRootsRL.clear();
			maxRootsLL.clear();
			maxRootsRL.push_back(node);
			MAXPATHLENGTH = 0;
		}
		else if (MAXPATHLENGTH == 0){
			maxRootsRL.push_back(node);
		}
	}
	else if (node->left == NULL) {
		node->leftHeight = -1;
		node->rightHeight = node->right->height;
		node->height = node->right->height + 1;
		node->ifRootPathLength = node->height;

		if (MAXPATHLENGTH < node->ifRootPathLength) {
			maxRootsRL.clear();
			maxRootsLL.clear();
			maxRootsRL.push_back(node);
			MAXPATHLENGTH = node->ifRootPathLength;
		}
		else if (MAXPATHLENGTH == node->ifRootPathLength) {
			maxRootsRL.push_back(node);
		}
	}
	else if (node->right == NULL) {
		node->leftHeight = node->left->height;
		node->rightHeight = -1;
		node->height = node->left->height + 1;
		node->ifRootPathLength = node->height;

		if (MAXPATHLENGTH < node->ifRootPathLength) {
			maxRootsRL.clear();
			maxRootsLL.clear();
			maxRootsRL.push_back(node);
			MAXPATHLENGTH = node->ifRootPathLength;
		}
		else if (MAXPATHLENGTH == node->ifRootPathLength) {
			maxRootsRL.push_back(node);
		}
	}
	else {
		node->leftHeight = node->left->height;
		node->rightHeight = node->right->height;
		if (node->right->height > node->left->height) {
			node->height = node->right->height + 1;
		}
		else {
			node->height = node->left->height + 1;
		}
		node->ifRootPathLength = node->left->height + node->right->height + 1;//не плюс два так как между листом и предыдущей второму листу вершиной
		//между двумя листами
		if (MAXPATHLENGTH < node->ifRootPathLength) {
			maxRootsLL.clear();
			maxRootsRL.clear();
			maxRootsLL.push_back(node);
			MAXPATHLENGTH = node->ifRootPathLength;
		}
		else if (MAXPATHLENGTH == node->ifRootPathLength) {
			maxRootsLL.push_back(node);
		}
	}
}

bool comp(struct BinaryTreeNode* node1, struct BinaryTreeNode* node2) {
	return node1->data < node2->data;
}
//если сортировка неправильная, то переписать дек в вектор
struct BinaryTreeNode* MeanNode(std::deque<struct BinaryTreeNode*> vec) {
	int vecSize = vec.size();
	if (vecSize % 2 == 0) {
		return NULL;
	}

	sort(vec.begin(), vec.end(), comp);
	return vec[(vecSize - 1) / 2];
}

std::deque<struct BinaryTreeNode*> longestPathFromRoot(struct BinaryTreeNode* root) {
	std::deque<struct BinaryTreeNode*> vec;
	vec.push_back(root);
	struct BinaryTreeNode* tmpNode;
	if (root->left != NULL) {
		tmpNode = root->left;
		while (tmpNode->left != NULL || tmpNode->right != NULL) {
			vec.push_front(tmpNode);
			if (tmpNode->left != NULL && tmpNode->right == NULL) {
				tmpNode = tmpNode->left;
			}
			else if (tmpNode->left == NULL && tmpNode->right != NULL) {
				tmpNode = tmpNode->right;
			}
			else {
				if (tmpNode->leftHeight >= tmpNode->rightHeight) {
					tmpNode = tmpNode->left;
				}
				else {
					tmpNode = tmpNode->right;
				}
			}
		}
		vec.push_front(tmpNode);
	}

	if (root->right != NULL) {
		tmpNode = root->right;
		while (tmpNode->left != NULL || tmpNode->right != NULL) {
			vec.push_back(tmpNode);
			if (tmpNode->left != NULL && tmpNode->right == NULL) {
				tmpNode = tmpNode->left;
			}
			else if (tmpNode->left == NULL && tmpNode->right != NULL) {
				tmpNode = tmpNode->right;
			}
			else {
				if (tmpNode->leftHeight >= tmpNode->rightHeight) {
					tmpNode = tmpNode->left;
				}
				else {
					tmpNode = tmpNode->right;
				}
			}
		}
		vec.push_back(tmpNode);
	}

	return vec;
}
struct BinaryTreeNode* minSumRootGlobal = NULL;
std::deque<struct BinaryTreeNode*> longestPath() {
	long long minSum = LLONG_MAX;
	struct BinaryTreeNode* minSumRoot = createNode(LLONG_MAX);
	long long sum = LLONG_MIN;
	for (struct BinaryTreeNode* node : maxRootsRL) {
		std::deque<struct BinaryTreeNode*> tmpVec = longestPathFromRoot(node);
		sum = tmpVec.front()->data + tmpVec.back()->data;
		if (sum == minSum) {
			//может быть ошибка, которая в примечаниях(((((9
			if (node->data < minSumRoot->data) {
				minSumRoot = node;
			}
		}
		else if (sum < minSum) {
			minSum = sum;
			minSumRoot = node;
		}
	}
	long long sum1 = LLONG_MIN;
	long long sum2 = LLONG_MIN;
	for (struct BinaryTreeNode* node : maxRootsLL) {
		std::deque<struct BinaryTreeNode*> tmpVec = longestPathFromRoot(node);
		sum1 = tmpVec[0]->data + tmpVec[tmpVec.size() - 2]->data;
		sum2 = tmpVec[1]->data + tmpVec[tmpVec.size() - 1]->data;
		if (sum1 < sum2) {
			if (sum1 == minSum) {
				//может быть ошибка, которая в примечаниях(((((9
				if (node->data < minSumRoot->data) {
					minSumRoot = node;
				}
			}
			else if (sum1 < minSum) {
				minSum = sum1;
				minSumRoot = node;
			}
		}
		else if (sum1 > sum2) {
			if (sum2 == minSum) {
				//может быть ошибка, которая в примечаниях(((((9
				if (node->data < minSumRoot->data) {
					minSumRoot = node;
				}
			}
			else if (sum2 < minSum) {
				minSum = sum2;
				minSumRoot = node;
			}
		}
		else {// что делать если сам1 = сам2?!
			if (sum2 == minSum) {
				//может быть ошибка, которая в примечаниях(((((9
				if (node->data < minSumRoot->data) {
					minSumRoot = node;
				}
			}
			else if (sum2 < minSum) {
				minSum = sum2;
				minSumRoot = node;
			}
		}
	}
	minSumRootGlobal = minSumRoot;
	return longestPathFromRoot(minSumRoot);
}



int main() {
	//открытие файлов
	FILE* inputFile = fopen("tst.in", "r");
	FILE* outputFile = fopen("tst.out", "w");

	//чтение и создание дерева
	long long data;
	fscanf(inputFile, "%lld", &data);
	struct BinaryTreeNode* node = createNode(data);
	struct BinaryTree* tree = createTree(node);

	while (fscanf(inputFile, "%lld", &data) != EOF) {
		insertNode(tree->root, data);
	}
	
	//основное тело
	rootsWithMaxPathes(tree->root);//далее найти по корням все пути, а потом выбрать с минимальными крайними, потом найти с меньшим корнем, потом удалить среднюю
	std::deque<struct BinaryTreeNode*> lngstpth = longestPath();
	if (lngstpth.front()->left == NULL && lngstpth.front()->right == NULL &&
		lngstpth.back()->left == NULL && lngstpth.back()->right == NULL) {

		std::deque<struct BinaryTreeNode*> tmpdeque;
		for (struct BinaryTreeNode* n : lngstpth) {
			tmpdeque.push_back(n);
		}

		lngstpth.pop_back();
		long long sum1 = lngstpth.front()->data + lngstpth.back()->data;
		tmpdeque.pop_front();
		long long sum2 = tmpdeque.front()->data + tmpdeque.back()->data;

		struct BinaryTreeNode* tmpnode1 = MeanNode(lngstpth);
		struct BinaryTreeNode* tmpnode2 = MeanNode(tmpdeque);
		if (sum1 < sum2) {
			if (tmpnode1 != NULL) {
				deleteNode(tree->root, tmpnode1->data, tree);
			}
		}
		else if (sum1 > sum2) {
			if (tmpnode2 != NULL) {
				deleteNode(tree->root, tmpnode2->data, tree);
			}
		}
		else {
			if (tmpnode1 != NULL) {
				if (tmpnode1->data == tmpnode2->data) {
					deleteNode(tree->root, tmpnode1->data, tree);
				}
			}
		}
	}
	else {
		struct BinaryTreeNode* tmpnode = MeanNode(lngstpth);
		deleteNode(tree->root, tmpnode->data, tree);
	}

	//вывод
	leftInOrderTraversal(tree->root, outputFile);
}
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#pragma warning (disable: 4996)

struct BinaryTreeNode {
	long long data;
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

std::vector<struct BinaryTreeNode*> nodes;

void insertNode(long long data, struct BinaryTreeNode* node, char son) {
	if (son == 'R') {
		node->right = createNode(data);
		node->right->parent = node;
		nodes.push_back(node->right);
	}
	else {
		node->left = createNode(data);
		node->left->parent = node;
		nodes.push_back(node->left);
	}
}

bool ForIsInRightSubtree(struct BinaryTreeNode* node, struct BinaryTreeNode* baseNode) {
	if (baseNode == NULL) {
		return false;
	}
	if (node == baseNode) {
		return true;
	}
	else {
		if (!ForIsInRightSubtree(node, baseNode->left) && !ForIsInRightSubtree(node, baseNode->right)) {
			return false;
		}
	}
	return true;
}

bool isInRightSubtree(struct BinaryTreeNode* node, struct BinaryTreeNode* baseNode) {
	if (ForIsInRightSubtree(node, baseNode->right)) {
		return true;
	}

	return false;
}

struct BinaryTreeNode* prevNode = NULL;

bool traversal(struct BinaryTreeNode* node) {
	if (node->left != NULL) {
		if (!traversal(node->left)) {
			return false;
		}
	}

	if ((prevNode == NULL) || (prevNode->data < node->data)) {
		prevNode = node;
	}
	else if (prevNode->data > node->data) {
		return false;
	}
	else {
		if (isInRightSubtree(node, prevNode)) {
			prevNode = node;
		}
		else {
			return false;
		}
	}

	if (node->right != NULL) {
		if (!traversal(node->right)) {
			return false;
		}
	}

	return true;
}

int main() {
	FILE* inputFile = fopen("bst.in", "r");
	FILE* outputFile = fopen("bst.out", "w");

	long long n;
	fscanf(inputFile, "%lld", &n);
	long long root;
	fscanf(inputFile, "%lld", &root);

	struct BinaryTreeNode* node = createNode(root);
	struct BinaryTree* tree = createTree(node);

	nodes.push_back(node);

	long long data, row;
	char son;
	for (int i = 0; i < (n - 1); i++) {
		fscanf(inputFile, "%lld %lld %c", &data, &row, &son);
		insertNode(data, nodes[row - 1], son);
	}

	if (traversal(tree->root)) {
		fprintf(outputFile, "YES");
	}
	else {
		fprintf(outputFile, "NO");
	}

	return 0;
}

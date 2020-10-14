#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)

struct BinaryTreeNode {
	long long data;
	BinaryTreeNode* right;
	BinaryTreeNode* left;
};

struct BinaryTree {
	BinaryTreeNode* root;
};

BinaryTreeNode* createNode(long long data) {
	BinaryTreeNode* newNode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));

	newNode->data = data;
	newNode->right = NULL;
	newNode->left = NULL;

	return newNode;
}

BinaryTree* createTree(BinaryTreeNode* node) {
	BinaryTree* newTree = (BinaryTree*)malloc(sizeof(BinaryTree));

	newTree->root = node;

	return newTree;
}

void insertNode(BinaryTreeNode* node, long long data) {
	if (node->data > data) {
		if (node->left == NULL) {
			node->left = createNode(data);
		}
		else {
			insertNode(node->left, data);
		}
	}
	else if (node->data < data) {
		if (node->right == NULL) {
			node->right = createNode(data);
		}
		else {
			insertNode(node->right, data);
		}
	}
}

void traversal(BinaryTreeNode* node, FILE* fout) {
	fprintf(fout, "%lld\n", node->data);

	if (node->left != NULL) {
		traversal(node->left, fout);
	}

	if (node->right != NULL) {
		traversal(node->right, fout);
	}
}

int main() {
	FILE* inputFile = fopen("input.txt", "r");
	FILE* outputFile = fopen("output.txt", "w");

	long long data;
	fscanf(inputFile, "%lld", &data);
	BinaryTreeNode* node = createNode(data);
	BinaryTree* tree = createTree(node);

	while (fscanf(inputFile, "%lld", &data) != EOF) {
		insertNode(tree->root, data);
	}

	traversal(tree->root, outputFile);
}

#include <stdio.h>
#include <stdlib.h>
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

struct BinaryTreeNode* find(struct BinaryTreeNode* node, long long data) {
	if (node == NULL) {
		return NULL;
	}
	if (node->data == data) {
		return node;
	}
	else if (node->data > data){
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

void insertNode (struct BinaryTreeNode* node, long long data) {
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

void deleteNode (struct BinaryTreeNode* node, long long data, struct BinaryTree* tree) {
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

void traversal(struct BinaryTreeNode* node, FILE* fout) {
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

	long long target;
	fscanf(inputFile, "%lld", &target);

	long long data;
	fscanf(inputFile, "%lld", &data);
	struct BinaryTreeNode* node = createNode(data);
	struct BinaryTree* tree = createTree(node);

	while (fscanf(inputFile, "%lld", &data) != EOF) {
		insertNode(tree->root, data);
	}

	deleteNode(tree->root, target, tree);
	traversal(tree->root, outputFile);
}

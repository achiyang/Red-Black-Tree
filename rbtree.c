#include "rbtree.h"

#include <stdio.h>
#include <stdlib.h>

void initTree(RBTree* tree) {
	tree->root = NULL;
}

static void freeTreeCore(Node* node) {
	if (node == NULL) {
		return;
	}
	freeTreeCore(node->left);
	freeTreeCore(node->right);
	free(node);
}

void freeTree(RBTree* tree) {
	freeTreeCore(tree->root);
	tree->root = NULL;
}

static void printTreeCore(Node* node) {
	if (node == NULL) {
		return;
	}
	printf("%d ", node->data);
	printTreeCore(node->left);
	printTreeCore(node->right);
}

void printTree(RBTree tree) {
	printTreeCore(tree.root);
}

static void leftRotation(RBTree* tree, Node* node) {
	Node* child = node->right;

	node->right = child->left;
	if (child->left != NULL) {
		child->left->parent = node;
	}

	child->parent = node->parent;
	if (node->parent == NULL) {
		tree->root = child;
	}
	else if (node == node->parent->left) {
		node->parent->left = child;
	}
	else if (node == node->parent->right) {
		node->parent->right = child;
	}
	else {
		fprintf(stderr, "node is not a child of node->parent\n");
		exit(EXIT_FAILURE);
	}

	child->left = node;
	node->parent = child;
}

static void rightRotation(RBTree* tree, Node* node) {
	Node* child = node->left;

	node->left = child->right;
	if (child->right != NULL) {
		child->right->parent = node;
	}

	child->parent = node->parent;
	if (node->parent == NULL) {
		tree->root = child;
	}
	else if (node == node->parent->left) {
		node->parent->left = child;
	}
	else if (node == node->parent->right) {
		node->parent->right = child;
	}
	else {
		fprintf(stderr, "node is not a child of node->parent\n");
		exit(EXIT_FAILURE);
	}

	child->right = node;
	node->parent = child;
}

static void fixInsert(RBTree* tree, Node* node) {
	while (node->parent != NULL && node->parent->color == 'r') {
		if (node->parent == node->parent->parent->left) {
			Node* uncle = node->parent->parent->right;
			if (uncle != NULL && uncle->color == 'r') {
				node->parent->color = 'b';
				uncle->color = 'b';
				node->parent->parent->color = 'r';
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->right) {
					node = node->parent;
					leftRotation(tree, node);
				}
				node->parent->color = 'b';
				node->parent->parent->color = 'r';
				rightRotation(tree, node->parent->parent);
			}
		}
		else {
			Node* uncle = node->parent->parent->left;
			if (uncle != NULL && uncle->color == 'r') {
				node->parent->color = 'b';
				uncle->color = 'b';
				node->parent->parent->color = 'r';
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->left) {
					node = node->parent;
					rightRotation(tree, node);
				}
				node->parent->color = 'b';
				node->parent->parent->color = 'r';
				leftRotation(tree, node->parent->parent);
			}
		}
	}
	tree->root->color = 'b';
}

static Node* createNode(int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	node->data = data;
	node->color = 'r';
	node->parent = node->left = node->right = NULL;
	return node;
}

void insertTree(RBTree* tree, int data) {
	Node* newNode = createNode(data);

	if (tree->root == NULL) {
		tree->root = newNode;
		tree->root->color = 'b';
		return;
	}

	Node* parent = NULL;
	Node* current = tree->root;

	while (current != NULL) {
		parent = current;
		if (data < current->data) {
			current = current->left;
		}
		else if (data > current->data) {
			current = current->right;
		}
		else {
			free(newNode);
			return;
		}
	}

	if (data < parent->data) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}
	newNode->parent = parent;

	fixInsert(tree, newNode);
}
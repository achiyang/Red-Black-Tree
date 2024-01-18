#ifndef RBTREE_H
#define RBTREE_H

typedef struct _Node {
	int data;
	char color; // 'r' for red, 'b' for black
	struct _Node* parent;
	struct _Node* left;
	struct _Node* right;
} Node;

typedef struct _RBTree {
	Node* root;
} RBTree;

void initTree(RBTree* tree);

void freeTree(RBTree* tree);

void printTree(RBTree tree);

void insertTree(RBTree* tree, int data);

#endif // RBTREE_H
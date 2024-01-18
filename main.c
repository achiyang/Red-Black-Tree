#include "rbtree.h"

int main() {
	RBTree tree;
	initTree(&tree);

	for (int i = 0; i < 10000; i++) {
		insertTree(&tree, i);
	}
	printTree(tree);

	freeTree(&tree);

	return 0;
}
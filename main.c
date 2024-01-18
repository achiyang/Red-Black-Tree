#include <stdlib.h>
#include <time.h>
#include "rbtree.h"

int main() {
	RBTree tree;
	initTree(&tree);

	srand(time(NULL));
	for (int i = 0; i < 30; i++) {
		insertTree(&tree, rand() % 20);
	}
	printTree(tree);

	freeTree(&tree);

	return 0;
}
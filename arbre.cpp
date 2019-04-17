#include <cstdlib>
#include <iostream>

using namespace std;

struct branch {
	int data;
	branch *left;
	branch *right;
	int visited;
};

struct tree {
	branch *root;
};

branch *newBranch(int val) {
	branch *b = (branch*) malloc (sizeof(branch));
	b -> data = val;
	b -> visited = 0;
	b -> left = NULL;
	b -> right = NULL;
	return b;
}

void showRec(branch *b, int space) {
	for (int i = 0; i < space; i++) {
		if (i < space - 1)
			cout << "  ";
		else
			cout << "\u21B3 ";
	}
	cout << b -> data << endl;
	if (b -> left != NULL) {
		showRec(b -> left, space+1);
	}
	if (b -> right != NULL) {
		showRec(b -> right, space+1);
	}
}

void showTree(tree *t) {
	branch *b = t -> root;
	showRec(b, 0);
}

void addValIter(tree *t, int val) {
	branch *b = t -> root;
	while(b -> left != NULL || b -> right != NULL) {
		if (val >= b -> data) {
			b = b -> right;
		} else {
			b = b -> left;
		}
	}
	if (val >= b -> data) {
		b -> right = newBranch(val);
	} else {
		b -> left = newBranch(val);
	}
}

void recAddVal(branch *b, int val) {
	if (val >= b -> data && b ->right != NULL)
		recAddVal(b -> right, val);
	else if (val < b -> data && b ->left != NULL)
		recAddVal(b -> left, val);
	if (b ->left == NULL || b ->right == NULL) {
		if (val >= b -> data) {
			b -> right = newBranch(val);
		} else {
			b -> left = newBranch(val);
		}
	}
}

void addValRec(tree *t, int val) {
	recAddVal(t -> root, val);
}

int searchMin(tree *t) {
	branch *b = t -> root;
	while (b -> left == NULL) {
		b = b -> left;
	}
	return b -> data;
}

int recDeepness(branch *b) {
	if (b -> left != NULL && b -> right != NULL) {
		return 1 + max(recDeepness(b -> left), recDeepness(b -> right));
	} else if (b -> right != NULL) {
		return 1 + recDeepness(b ->right);
	} else if (b -> left != NULL) {
		return 1 + recDeepness(b -> left);
	} else {
		return 1;
	}
}

int deepnessRec(tree *t) {
	return recDeepness(t -> root);
}

int deepnessIter(tree *t) {
	branch *b = t -> root;
	int max = 0;
	int nb = 0;
	while (b && !b -> visited) {
		if (b -> left && !b -> left->visited) {
			nb++;
			b = b -> left;
		} else if (b -> right && !b -> right->visited) {
			nb++;
			b = b -> right;
		} else {
			nb++;
			if (nb > max)
				max = nb;
			nb = 0;
			b -> visited = 1;
			b = t -> root;
		}
	}
	return max;
}

int main() {
	tree *t = (tree*) malloc (sizeof(tree));
	t -> root = newBranch(5);
	t -> root -> left = newBranch(4);
	t -> root -> right = newBranch(6);
	t -> root -> left -> left = newBranch(3);
	addValRec(t, 4);
	addValRec(t, 4);
	addValIter(t, 3);
	cout << "Profondeur recursive: " << deepnessRec(t) << endl;
	cout << "Profondeur iterative: " << deepnessIter(t) << endl;
	showTree(t);
	return 0;
}
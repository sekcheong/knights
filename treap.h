#ifndef TREAP_H
#define TREAP_H
#include "treapnode.h"

class Treap {
	int nsplits;
	TreapNode *root;
	void insertNode(TreapNode **t, TreapNode *p);
	void split(long k, TreapNode *t, TreapNode **t1, TreapNode **t2);
public:
	Treap() {root = 0; nsplits=0;}
	void insert(long k, int p);
	int findKey(long k);
	int findKey(long k, TreapNode *n);
	void preorder() {preorder(root);}
	void inorder() {inorder(root);}
	void preorder(TreapNode *t);
	void inorder(TreapNode *t);
	int ns() {return nsplits;}
};
#endif

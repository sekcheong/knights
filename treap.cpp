#include <iostream>
#include "treap.h"
#include "treapnode.h"

using namespace std;

void Treap::split(long k, TreapNode *t, TreapNode **t1, TreapNode **t2) {	
	TreapNode *x;
	*t1=*t2=0;	
        x = t;
	nsplits++;
	while (x!=0) {
		if (x->getKey()>k) {
			t = x->getLeft();
			x->setLeft(0);			// disconnect the left branch
			insertNode(t2,x);
			x = t;
		}
		else {
			t = x->getRight();
			x->setRight(0);			// disconnect the right branch
			insertNode(t1,x);
			x = t;
		}
	}		
}


void Treap::insertNode(TreapNode **t, TreapNode *z) {
	TreapNode *x=(*t), *y=0;	
	while (x!=0) {
		y=x;
		if (z->getKey()>x->getKey())
			x = x->getRight();
		else
			x = x->getLeft();
	}	
	if (y==0) *t = z; 
	else 
		if (z->getKey()>y->getKey())
			y->setRight(z);
		else
			y->setLeft(z);	
}


void Treap::insert(long k, int p) {
	TreapNode *x = root, *y=0, *t1, *t2, *z;
	
	z = new TreapNode(k,p);
	while (x!=0 && z->getPriority()>x->getPriority()) {
		y = x;                                // y keeps track on x's parent
		if (z->getKey()>x->getKey()) 
			x = x->getRight();
		else
			x = x->getLeft();
	}		
	if (y==0) root = z;	
	else {
		if (z->getKey() > y->getKey()) {
			if (y->getRight()!=0) x = y->getRight();  // x = node to be splited
			y->setRight(z);
		}
		else {
			if (y->getLeft()!=0) x = y->getLeft();
			y->setLeft(z);
		}		
	}
	if (x!=0) {
		split(z->getKey(), x, &t1, &t2);
		z->setLeft(t1);
		z->setRight(t2);
	}
}


void Treap::preorder(TreapNode *t) {
	if (t!=0) {
		cout << t->getKey() << "," << t->getPriority() << " ";
		preorder(t->getLeft());
		preorder(t->getRight());
	}
}


void Treap::inorder(TreapNode *t) {
	if (t!=0) {
		inorder(t->getLeft());
		cout << t->getKey() << "," << t->getPriority() << " ";
		inorder(t->getRight());
	}
}


int Treap::findKey(long k, TreapNode *n) {
	if (n==0) return 0;
	if (k==n->getKey()) return 1;	
	if (k>n->getKey()) 
		return findKey(k, n->getRight());
	else
		return findKey(k, n->getLeft());
}


int Treap::findKey(long k) {
	return findKey(k,root);
}
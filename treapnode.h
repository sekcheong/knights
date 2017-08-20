#ifndef TREAPNODE_H
#define TREAPNODE_H

class TreapNode {
	int priority;
	long key;
public:
	TreapNode *left, *right;
	TreapNode() {left=right=0;}
	TreapNode(int k, int p) {key=k; priority=p; left=right=0;}
	void setKey(long k) {key = k;}
	void setPriority(int p) {priority = p;}
	long getKey() {return key;}
	int getPriority() {return priority;}
	TreapNode *getLeft() {return left;}
	TreapNode *getRight() {return right;}
	TreapNode *setLeft(TreapNode *n) {left = n; return this;}
	TreapNode *setRight(TreapNode *n) {right =n; return this;}
};

#endif
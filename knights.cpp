#include <iostream>
#include <stdlib.h>
#include "treap.h"

using namespace std;

#define MAXD 64

int board[11][3] = {
{0,0,0}, 
{7,8,0}, 
{9,0,0}, 
{5,8,0}, 
{6,9,0}, 
{3,9,0}, 
{4,10,0}, 
{1,0,0}, 
{1,3,0}, 
{2,4,5}, 
{6,0,0}};

// The chess board layout
// +---+---+---+---+
// | 1 | 2 | 3 | 4 | 
// +---+---+---+---+
// | 5 | 6 | 7 |
// +---+---+---+
//     | 8 | 9 |
//     +---+---+
//         |10 | 
//         +---+   


int ib1, iw1, ib2, iw2, count;
char *msg[4]={"black knight 1 moved from ", "white knight 1 moved form ", 
	"black knight 2 moved from ", "white knight 2 moved from " };

Treap badb1;
Treap badb2; 
Treap badw1;
Treap badw2;


int key(int d, int b1, int w1, int b2, int w2, int n) {
	return (((((d*10+b1)*10+w1)*10+w1)*10+b2)*10+w2)*10+n;
}


int empty(int p, int b1, int w1, int b2, int w2) {
	return ((p!=b1) && (p!=b2) && (p!=w1) && (p!=w2));
}


int solved(int b1, int w1, int b2, int w2) {
	return (((b1==iw1) && (w1==ib1) && (b2==iw2) && (w2==ib2)) || 
		((b2==iw1) && (w1==ib2) && (b1==iw2) && (w2==ib1)));
}


int findsol(int b1, int w1, int b2, int w2, int depth, int moves[3][MAXD]) {
	if (solved(b1, w1, b2, w2)) return 1;
	if (depth>=MAXD) return 0;
	
	for (int i=0; i<3; i++) {		
		if (!(badb1.findKey(key(depth, b1, w1, b2, w2, board[b1][i])) || 
			badw1.findKey(key(depth, b1, w1, b2, w2, board[w1][i])) || 
			badb2.findKey(key(depth, b1, w1, b2, w2, board[b2][i])) || 
			badw2.findKey(key(depth, b1, w1, b2, w2, board[w2][i]))))  {

				//move b1
				if (board[b1][i] && empty(board[b1][i], b1, w1, b2, w2)) {	
					if (findsol(board[b1][i], w1, b2, w2, depth+1, moves)) {			
						moves[0][depth] = 0;
						moves[1][depth] = b1;
						moves[2][depth] = board[b1][i];
						return 1;
					} 
					else {
						badb1.insert(key(depth, b1, w1, b2, w2, board[b1][i]), rand());
					}
				}

				//move w1
				if (board[w1][i] && empty(board[w1][i], b1, w1, b2, w2)) {
					if (findsol(b1, board[w1][i], b2, w2, depth+1, moves)) {				
						moves[0][depth] = 1;
						moves[1][depth] = w1;
						moves[2][depth] = board[w1][i];
						return 1;				
					} 
					else {
						badw1.insert(key(depth, b1, w1, b2, w2, board[w1][i]), rand());
					}
				}		

				//move b2
				if (board[b2][i] && empty(board[b2][i],b1,w1,b2,w2)) {	
					if (findsol(b1, w1, board[b2][i], w2, depth+1, moves)) {				
						moves[0][depth] = 2;
						moves[1][depth] = b2;
						moves[2][depth] = board[b2][i];
						return 1;
					} 
					else {
						badb2.insert(key(depth, b1, w1, b2, w2, board[b2][i]), rand());
					}
				}		

				//move w2
				if (board[w2][i] && empty(board[w2][i], b1, w1, b2, w2)) {
					if (findsol(b1, w1, b2, board[w2][i], depth+1, moves)) {				
						moves[0][depth] = 3;
						moves[1][depth] = w2;
						moves[2][depth] = board[w2][i];
						return 1;				
					} 
					else {
						badw2.insert(key(depth, b1, w1, b2, w2, board[w2][i]), rand());
					}
				}	
		}
	}
	::count++;
	return 0;
}


void printsol(int moves[3][MAXD]) {
	for (int i=0; i<MAXD; i++) {
		cout << "The " << msg[moves[0][i]] << moves[1][i] << " to " << moves[2][i] << endl;
	}
}


int main() {
	int b1, w1, b2, w2, moves[3][MAXD];
	cout << "Enter black knight 1 position: "; cin >> b1;
	cout << "Enter white knight 1 position: "; cin >> w1;
	cout << "Enter black knight 2 position: "; cin >> b2;
	cout << "Enter white knight 2 position: "; cin >> w2;
	ib1=b1; iw1=w1; ib2=b2; iw2=w2;
	if (findsol(b1,w1,b2,w2,0,moves)) {
		printsol(moves);
		cout << endl;				
	}
	else cout << " NO SOLUTION" << endl;
	cout << "** " << ::count << " recursive calls" << endl;	
	cout << "** badb1.nsplits " << badb1.ns() << endl;
	cout << "** badw1.nsplits " << badw1.ns() << endl;
	cout << "** badb2.nsplits " << badb2.ns() << endl;
	cout << "** badw2.nsplits " << badw2.ns() << endl;
}
#pragma once

#include "Tiles.h"
#include "Nines.h"

class Board
{
private:
	Nine rows[9];
	Nine cols[9];
	Nine sqrs[9];
public:
	Board();
	Nine* getNine(int type, int index);
	void setBoard();
	void print(int i);
	bool solve();
	bool simplify();
	bool levelOne();
	bool levelTwo();
	bool levelThree();
	bool solveOnes(Nine* nine, int index);
	bool check();
};

//Number of thre threes square: (j / 3) + ((i / 3) * 3)
//Number inside of the threes square: (j % 3) + ((i % 3) * 3)

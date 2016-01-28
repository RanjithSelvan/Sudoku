#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include "Board.h"
#include "Tiles.h"
#include "Nines.h"

using namespace std;

void testTile();
void testNine();
void testBoard();

void test() {
	cout << "Test Tile:\n";
	testTile();

	cout << "Test Nine:\n";
	testNine();

	cout << "Test Board:\n";
	testBoard();
}

int main()
{
	test();
	cin.get();
	return 0;
}

void testTile() {
	Tile a;
	//Check empty initialization
	cout << a.getVal() << endl;
	list<int> pos = a.getPos();
	cout << "[";
	for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
		cout << *iter;
	}
	cout << "]" << endl;
	//Check remPos(int)
	a.remPos(5);
	pos = a.getPos();
	cout << "[";
	for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
		cout << *iter;
	}
	cout << "]" << endl;
	//Check remPos(list<int>)
	list<int> rem;
	rem.push_back(1);
	rem.push_back(2);
	a.remPos(rem);
	pos = a.getPos();
	cout << "[";
	for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
		cout << *iter;
	}
	cout << "]" << endl;
	//Check setVal(int)
	a.setVal(5);
	cout << a.getVal() << endl;
	pos = a.getPos();
	cout << "[";
	for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
		cout << *iter;
	}
	cout << "]" << endl;
}

void testNine() {
	//Test Nine()
	cout << "Nine()\n";
	Nine a;
	
	//Test Nine(std::list<Tile*>)
	cout << "Nine(std::list<Tile>)\n";
	list<Tile*> init;
	init.push_back(new Tile());
	init.push_back(new Tile());
	init.push_back(new Tile());
	init.push_back(new Tile());
	init.push_back(new Tile());
	init.push_back(new Tile());
	init.push_back(new Tile());
	init.push_back(new Tile());
	init.push_back(new Tile());

	Nine b(init);
	Tile** val = b.getNine();
	for (int i = 0; i < 9; i++) {
		cout << val[i]->getVal() << endl;
		cout << "\t[";
		list<int> pos = val[i]->getPos();
		for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	list<int> nums;
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(4);
	nums.push_back(5);
	nums.push_back(6);
	nums.push_back(7);
	nums.push_back(8);
	nums.push_back(9);

	//Test setTile(index, val);
	cout << "setTile(0, 1)\n";
	b.setTile(0, 1);
	val = b.getNine();
	for (int i = 0; i < 9; i++) {
		cout << val[i]->getVal() << endl;
		cout << "\t[";
		list<int> pos = val[i]->getPos();
		for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	//Test remTilePos(index, pos);
	cout << "remTilePos(1, 1)\n";
	b.remTilePos(1, 1);
	val = b.getNine();
	for (int i = 0; i < 9; i++) {
		cout << val[i]->getVal() << endl;
		cout << "\t[";
		list<int> pos = val[i]->getPos();
		for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	//Test remPos(int)
	cout << "remPos(int)\n";
	b.remPos(3);
	val = b.getNine();
	for (int i = 0; i < 9; i++) {
		cout << val[i]->getVal() << endl;
		cout << "\t[";
		list<int> pos = val[i]->getPos();
		for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	
	nums.remove(1);
	nums.remove(3);
	nums.remove(6);
	nums.remove(7);
	//Test remTilePos(index, std::list<int>)
	cout << "remTilePos(index, std::list<int>)\n";
	b.remTilePos(2, nums);
	val = b.getNine();
	for (int i = 0; i < 9; i++) {
		cout << val[i]->getVal() << endl;
		cout << "\t[";
		list<int> pos = val[i]->getPos();
		for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	//Test remPos(std::list<int>)
	cout << "remPos(std::list<int>)\n";
	b.remPos(nums);
	val = b.getNine();
	for (int i = 0; i < 9; i++) {
		cout << val[i]->getVal() << endl;
		cout << "\t[";
		list<int> pos = val[i]->getPos();
		for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}

	nums.push_back(1);
	nums.push_back(3);
	nums.push_back(6);
	nums.push_back(7);
	//Test setNine(std::list<int> newVal)
	cout << "setNine(std::list<int> newVal)\n";
	b.setNine(nums);
	val = b.getNine();
	for (int i = 0; i < 9; i++) {
		cout << val[i]->getVal() << endl;
		cout << "\t[";
		list<int> pos = val[i]->getPos();
		for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	//Test setNine(int index, Tile* newTile)
	cout << "setNine(int, Tile*)\n";
	b.setNine(1, init.back());
	val = b.getNine();
	for (int i = 0; i < 9; i++) {
		cout << val[i]->getVal() << endl;
		cout << "\t[";
		list<int> pos = val[i]->getPos();
		for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	//Test setNine(std::list<Tile*> newVal)
	cout << "setNine(std::list<Tile*>)\n";
	init.reverse();
	b.setNine(init);
	val = b.getNine();
	for (int i = 0; i < 9; i++) {
		cout << val[i]->getVal() << endl;
		cout << "\t[";
		list<int> pos = val[i]->getPos();
		for (list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	//Test List
	cout << "Original List of Tiles\n[";
	for (list<Tile*>::iterator iter = init.begin(); iter != init.end(); iter++) {
		cout << (*iter)->getVal();
	}
	cout << "]" << endl;
}

void testBoard() {
	//Initialize Board
	cout << "Testing Board():\n";
	Board a;
	a.print(1);
	a.print(2);
	a.print(3);
	//Test getNine(type, index)
	cout << "Testing getNine(type, index)\n";
	Nine* nine = a.getNine(1, 1);
	for (int i = 0; i < 9; i++) {
		Tile* tile = nine->getTile(i);
		cout << tile->getVal() << endl;
		cout << "\t[";
		std::list<int> pos = tile->getPos();
		for (std::list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	//Test solveNine(Nine*)
	cout << "Testing solveNine(Nine*)\n";
	a.solveOnes(nine, 1);
	for (int i = 0; i < 9; i++) {
		Tile* tile = nine->getTile(i);
		cout << tile->getVal() << endl;
		cout << "\t[";
		std::list<int> pos = tile->getPos();
		for (std::list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
			cout << *iter;
		}
		cout << "]" << endl;
	}
	//Test solve()
	cout << "Testing solve()\n";
	a.solve();
	a.print(1);
}
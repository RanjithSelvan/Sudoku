#pragma once

#include <list>

class Tile {
private:
	bool fixed;
	int val;
	std::list<int> pos;
public:
	Tile();
	Tile(int newVal);
	~Tile();
	bool isFixed();
	int getVal();
	void setVal(int newVal);
	std::list<int> getPos();
	bool remPos(int p);
	bool remPos(std::list<int> p);
};
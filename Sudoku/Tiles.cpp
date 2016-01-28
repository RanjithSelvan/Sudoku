#include "Tiles.h"

Tile::Tile() {
	val = 0;
	for (int i = 0; i < 9; i++) {
		pos.push_back(i + 1);
	}
	fixed = false;
}

Tile::Tile(int newVal) {
	val = newVal;
	fixed = true;
}

Tile::~Tile() {
	;
}

bool Tile::isFixed() {
	return fixed;
}

int Tile::getVal() {
	return val;
}

void Tile::setVal(int newVal) {
	val = newVal;
	if (newVal != 0) {
		fixed = true;
		pos.clear();
	}
}

std::list<int> Tile::getPos() {
	return pos;
}

void Tile::remPos(int p) {
	pos.remove(p);
}

void Tile::remPos(std::list<int> p) {
	for (int i = 0; !p.empty(); i++) {
		pos.remove(p.front());
		p.pop_front();
	}
}
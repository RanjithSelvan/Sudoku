#include "Nines.h"
#include <list>

Nine::Nine() {
	;
}

Nine::Nine(std::list<Tile*> newTiles) {
	std::list<Tile*>::iterator iter = newTiles.begin();
	for (int i = 0; i < 9; i++) {
		val[i] = *iter++;
	}
}
Nine::~Nine() {
	;
}
Tile** Nine::getNine() {
	return val;
}
Tile* Nine::getTile(int index) {
	return val[index];
}
void Nine::setNine(int index, Tile* newTile) {
	val[index] = newTile;
}
void Nine::setNine(std::list<Tile*> newVal) {
	int size = newVal.size();
	if (size != 9) {
		return;
	}
	std::list<Tile*>::iterator iter = newVal.begin();
	for (int i = 0; i < 9; i++) {
		val[i] = *iter++;
	}
}
void Nine::setNine(std::list<int> newVal) {
	int size = newVal.size();
	if (size != 9) {
		return;
	}
	std::list<int>::iterator iter = newVal.begin();
	for (int i = 0; i < 9; i++) {
		val[i]->setVal(*iter++);
	}
}
void Nine::setTile(int index, int newVal) {
	val[index]->setVal(newVal);
}
bool Nine::remTilePos(int index, int pos) {
	return val[index]->remPos(pos);
}
bool Nine::remTilePos(int index, std::list<int> p) {
	return val[index]->remPos(p);
}
bool Nine::remPos(int newVal) {
	bool dirty = false;
	for (int i = 0; i < 9; i++) {
		dirty |= val[i]->remPos(newVal);
	}
	return dirty;
}
bool Nine::remPos(std::list<int> p) {
	bool dirty = false;
	for (int i = 0; i < 9; i++) {
		dirty |= val[i]->remPos(p);
	}
	return dirty;
}
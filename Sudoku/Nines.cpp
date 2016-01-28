#include "Nines.h"
#include <list>

Nine::Nine(){
	;
}

Nine::Nine(std::list<Tile*> newTiles) {
	std::list<Tile*>::iterator iter = newTiles.begin();
	for (int i = 0; i < 9; i++) {
		val[i] = *iter++;
	}
}
Nine::~Nine(){
	;
}
Tile** Nine::getNine(){
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
void Nine::setNine(std::list<int> newVal){
	int size = newVal.size();
	if (size != 9) {
		return;
	}
	std::list<int>::iterator iter = newVal.begin();
	for (int i = 0; i < 9; i++) {
		val[i]->setVal(*iter++);
	}
}
void Nine::setTile(int index, int newVal){
	val[index]->setVal(newVal);
}
void Nine::remTilePos(int index, int pos){
	val[index]->remPos(pos);
}
void Nine::remTilePos(int index, std::list<int> p){
	val[index]->remPos(p);
}
void Nine::remPos(int newVal){
	for (int i = 0; i < 9; i++) {
		val[i]->remPos(newVal);
	}
}
void Nine::remPos(std::list<int> p){
	for (int i = 0; i < 9; i++) {
		val[i]->remPos(p);
	}
}
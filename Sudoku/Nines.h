#pragma once

#include "Tiles.h"
#include <list>

class Nine {
private:
	Tile* val[9];
public:
	Nine();
	Nine(std::list<Tile*> newTiles);
	~Nine();
	Tile** getNine();
	Tile* getTile(int index);
	void setNine(int index, Tile* newTile);
	void setNine(std::list<Tile*> newVal);
	void setNine(std::list<int> newVal);
	void setTile(int index, int newVal);
	void remTilePos(int index, int pos);
	void remTilePos(int index, std::list<int> p);
	void remPos(int newVal);
	void remPos(std::list<int> p);
};

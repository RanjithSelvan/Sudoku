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
	bool remTilePos(int index, int pos);
	bool remTilePos(int index, std::list<int> p);
	bool remPos(int newVal);
	bool remPos(std::list<int> p);
};

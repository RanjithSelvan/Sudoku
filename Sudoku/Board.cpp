#include <sstream>
#include <iostream>
#include <fstream>
#include <list>

#include "Board.h"
#include "Nines.h"

std::string readFile(std::string fileName) {
	std::fstream fs(fileName);
	std::string line, file;
	while (!fs.eof()) {
		getline(fs, line);
		file += line + " ";
	}
	fs.close();

	return file;
}
Board::Board() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			Tile* a = new Tile();
			rows[i].setNine(j, a);
			cols[j].setNine(i, a);
			sqrs[(j / 3) + ((i / 3) * 3)].setNine((j % 3) + ((i % 3) * 3), a);

		}
	}
	setBoard();
}
Nine* Board::getNine(int type, int index) {
	if (type > 3 || type < 1 || index < 0 || index > 8) {
		return (Nine*)NULL;
	}
	switch (type) {
	case 1:
		return &rows[index];
		break;
	case 2:
		return &cols[index];
		break;
	case 3:
		return &sqrs[index];
		break;
	default:
		return (Nine*)NULL;
		break;
	}
}
void Board::setBoard() {
	Nine* b = &rows[0];
	std::stringstream ss(readFile("puzzle.txt"));
	int a = 0;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			ss >> a;
			ss.get();
			rows[i].setTile(j, a);
		}
		
	}
}
void Board::print(int i) {
	std::stringstream ss;
	switch (i) {
	case 3:
		ss << "Print 3: This uses sqrs to print:\n";
		for (int i = 0; i < 9; i++) {
			int j = 0;
			if (i % 3 == 0) {
				ss << "-------------------------------\n";
			}
			for (j = 0; j < 9; j++) {

				if (j % 3 == 0) {
					ss << " || ";
				}
				else {
					ss << " ";
				}
				ss << sqrs[(j / 3) + ((i / 3) * 3)].getTile((j % 3) + ((i % 3) * 3))->getVal();
			}

			ss << " ||\n";
		}
		ss << "-------------------------------\n";
		std::cout << ss.str();
		break;
	case 2:
		ss << "Print 2: This uses cols to print:\n";
		for (int i = 0; i < 9; i++) {
			int j = 0;
			if (i % 3 == 0) {
				ss << "-------------------------------\n";
			}
			for (j = 0; j < 9; j++) {

				if (j % 3 == 0) {
					ss << " || ";
				}
				else {
					ss << " ";
				}
				ss << cols[j].getTile(i)->getVal();
			}

			ss << " ||\n";
		}
		ss << "-------------------------------\n";
		std::cout << ss.str();
		break;
	case 1:
	default:
		ss << "Print 1(Default Print): This uses rows to print:\n";
		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) {
				ss << "-------------------------------\n";
			}
			for (int j = 0; j < 9; j++) {

				if (j % 3 == 0) {
					ss << " || ";
				}
				else {
					ss << " ";
				}
				ss << rows[i].getTile(j)->getVal();
			}

			ss << " ||\n";
		}
		ss << "-------------------------------\n";
		std::cout << ss.str();
	}
	
}
bool Board::solve() {
	bool simpUpdate = false;
	
	while (!check()) {
		simpUpdate = false;
		//Simplify the Nines, by checking if only one possiblity exists
		for (int i = 0; i < 9; i++) {
			simpUpdate = simpUpdate || simplify(&rows[i]);
			simpUpdate = simpUpdate || simplify(&cols[i]);
			simpUpdate = simpUpdate || simplify(&sqrs[i]);
		}
		if (simpUpdate) {
			print(1);
		}
		//If we can no longer simplify we must look for one unique possiblity in the nine
		if (!simpUpdate) {
			for (int i = 0; i < 9; i++) {
				solveOnes(&sqrs[i], i);
			}
		}
		print(1);
	}
	return true;
}
bool Board::simplify(Nine* nine) {
	bool updated = false;
	std::list<std::list<int>> poses;
	std::list<int> fixed;	//List of tiles that have known values
	//Fill the fixed-list
	for (int i = 0; i < 9; i++) {
		poses.push_back(nine->getTile(i)->getPos());
		if (nine->getTile(i)->isFixed()) {
			fixed.push_back(nine->getTile(i)->getVal());
		}
	}
	nine->remPos(fixed);	//Remove the known values from the possibilties of the unknown tiles
	
	//If a Tile has only one possibilty of value left, set the tile to that value and make it fixed
	for (int i = 0; i < 9; i++ ) {
		Tile* tile = nine->getTile(i);
		if (tile->getPos().size() == 1) {
			std::list<int> pos = tile->getPos();
			tile->setVal(pos.front());
			updated = true;
		}
	}
	return updated;
}
//Check to see if only one of the titles has a certain possibly value. 
//That is, it is not possible for 8 of the 9 titles to be a certain value.
//Then the remaining tile must be that value.
bool Board::solveOnes(Nine* nine, int index) {
	bool update = false;
	//Continer to coount the number of value occurances in possiblities for all tiles in a nine
	int tuple[9][4];
		for (int i = 0; i < 9; i++) {
		tuple[i][0] = 0;	//Total number of occurances
		tuple[i][1] = -1;	//First index of occurance
		tuple[i][2] = -1;	//Second index of occurance
		tuple[i][3] = -1;	//Last index of occurance (Not necessarily the third occurance)
	}
	//Fill the tuple
	for (int i = 0; i < 9; i++) {
		Tile* tile = nine->getTile(i);
		if (!tile->isFixed()) {
			std::list<int> pos = tile->getPos();
			for (std::list<int>::iterator iter = pos.begin(); iter != pos.end(); iter++) {
				tuple[*iter-1][0] += 1;
				if (tuple[*iter - 1][1] == -1) {
					tuple[*iter - 1][1] = i;
					continue;
				}
				if ((tuple[*iter - 1][1] != -1) && (tuple[*iter - 1][2] == -1)) {
					tuple[*iter - 1][2] = i;
					continue;
				}
				if ((tuple[*iter - 1][1] != -1) && (tuple[*iter - 1][2] != -1)) {
					tuple[*iter - 1][3] = i;
				}
			}
		}
	}
	//Check if the tuple contains a count of one indicating a value occurs only once in the tiles possiblies.
	for (int i = 0; i < 9; i++) {
		if (tuple[i][0] == 1) {
			nine->getTile(tuple[i+1][1])->setVal(i+1);
			update = true;
		}
		if (tuple[i][0] == 2) {
			int a = tuple[i][1];
			int b = tuple[i][2];
			// a/3 == b/3 determines if tiles are in same row, a%3 == b%3 determines if tiles are in the same col
			if ((a / 3 == b / 3) ){
				int row = ((index / 3) * 3)+ (a / 3);
				for (int j = 0; j < 9; j++) {
					if (j != a && j != b) {
						rows[row].getTile(j)->remPos(i+1);
					}
				}
				update = true;
			}
			if ((a % 3 == b % 3)) {
				int col = ((index % 3) * 3) + (a % 3);
				for (int j = 0; j < 9; j++) {
					if (j != a && j != b) {
						rows[col].getTile(j)->remPos(i);
					}
				}
				update = true;
			}
		}
		if (tuple[i][0] == 3) {
			update = true;
		}
	}
	
	return update;
}

bool Board::check() {
	return false;
}
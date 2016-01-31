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
	int solveCycle = 0;
	while (!check()) {
		simplify();
		if (levelOne()) {
			continue;
		}
		if (levelTwo()) {
			continue;
		}
		if (levelThree()) {
			continue;
		}
		std::cout << "Solve Cycle: " << solveCycle++ << std::endl;
		print(0);
	}
	return true;
}

//Iterate over the entire board and check if a tile has only one possible value and set it.
bool Board::simplify() {
	bool dirty = false;
	std::list<int> fixed;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (rows[i].getTile(j)->getPos().size() == 1) {
				rows[i].getTile(j)->setVal(rows[i].getTile(j)->getPos().back());
				dirty = true;
			}
		}
	}
	return dirty;
}
//Iterate ove the entire board in the view of rows, cols, and sqrs, to remove the fixed values from the possiblities of unset Tiles.
bool Board::levelOne() {
	bool dirty = false;
	for (int i = 0; i < 9; i++) {
		std::list<int> pos[3];
		for (int j = 0; j < 9; j++) {
			pos[0].push_back(rows[i].getTile(j)->getVal());
			pos[1].push_back(cols[i].getTile(j)->getVal());
			pos[2].push_back(sqrs[i].getTile(j)->getVal());
		}
		dirty |= rows[i].remPos(pos[0]);
		dirty |= cols[i].remPos(pos[1]);
		dirty |= sqrs[i].remPos(pos[2]);
	}
	return dirty;
}
//Check each row to see if there are ONLY two tiles in the same square with a certain pos value.
//Remove that value from the other squares;
bool Board::levelTwo() {
	bool dirty = false;
	int posCountRows[9][3];
	int posCountCols[9][3];
	//Go through the Rows and Cols
	for (int i = 0; i < 9; i++) {
		//Zero out PosCountRows and PosCountCols
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 3; k++) {
				posCountRows[j][k] = 0;
				posCountCols[j][k] = 0;
			}
		}
		//Get the Pos of each tile and add the number of occurances and indexes of occurances.
		for (int j = 0; j < 9; j++) {
			//Get Pos of a tile
			std::list<int> posRows = rows[i].getTile(j)->getPos();
			std::list<int> posCols = cols[i].getTile(j)->getPos();
			//Sum the occurances on Rows
			for (std::list<int>::iterator k = posRows.begin(); k != posRows.end(); k++) {
				if (*k - 1 >= 0 && *k - 1 <= 8) {
					posCountRows[*k - 1][0]++;
					if (posCountRows[*k - 1][1] == 0) {
						posCountRows[*k - 1][1] = j + 1;
					}
					else if (posCountRows[*k - 1][2] == 0) {
						posCountRows[*k - 1][2] = j + 1;
					}
				}
			}
			//Sum the occurances on Cols
			for (std::list<int>::iterator k = posCols.begin(); k != posCols.end(); k++) {
				if (*k - 1 >= 0 && *k - 1 <= 8) {
					posCountCols[*k - 1][0]++;
					if (posCountCols[*k - 1][1] == 0) {
						posCountCols[*k - 1][1] = j + 1;
					}
					else if (posCountCols[*k - 1][2] == 0) {
						posCountCols[*k - 1][2] = i + 1;
					}
				}
			}
		}
		//Determine and execute if Level 2 reductions can occur.
		for (int j = 0; j < 9; j++) {
			if (posCountRows[j][0] == 2) {
				//Determine if they are in the same square
				if (posCountRows[j][1] - 1 / 3 == posCountRows[j][2] - 1 / 3) {
					int sqrsIndex = (posCountRows[j][1] - 1 / 3) + (3 * (i / 3));
					//Remove that pos from the other tiles in the square.
					for (int k = 0; k < 9; k++) {
						if (k != posCountRows[j][1] - 1 && k != posCountRows[j][2] - 1) {
							sqrs[sqrsIndex].getTile(k)->remPos(j + 1);
							dirty = true;
						}
					}
				}
			}
			if (posCountCols[j][0] == 2) {
				//Determine if they are in the same square
				if (posCountCols[j][1] - 1 / 3 == posCountCols[j][2] - 1 / 3) {
					int sqrsIndex = (i / 3) + (3 * (posCountRows[j][1] - 1 / 3));
					//Remove that pos from the other tiles in the square.
					for (int k = 0; k < 9; k++) {
						if (k != posCountCols[j][1] - 1 && k != posCountCols[j][2] - 1) {
							sqrs[sqrsIndex].getTile(k)->remPos(j + 1);
							dirty = true;
						}
					}
				}
			}
		}
	}


	return dirty;
}
bool Board::levelThree() {
	return false;
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
				tuple[*iter - 1][0] += 1;
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
			nine->getTile(tuple[i + 1][1])->setVal(i + 1);
			update = true;
		}
		if (tuple[i][0] == 2) {
			int a = tuple[i][1];
			int b = tuple[i][2];
			// a/3 == b/3 determines if tiles are in same row, a%3 == b%3 determines if tiles are in the same col
			if ((a / 3 == b / 3)) {
				int row = ((index / 3) * 3) + (a / 3);
				for (int j = 0; j < 9; j++) {
					if (j != a && j != b) {
						rows[row].getTile(j)->remPos(i + 1);
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
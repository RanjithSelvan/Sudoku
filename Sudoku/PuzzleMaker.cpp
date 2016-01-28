#include "PuzzleMaker.h"
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>

PuzzleMaker::PuzzleMaker()
{
	a = NULL;
	for(int i = 0; i < 9; i++)
	{
		n_arr[i] = i+1;
	}
}

PuzzleMaker::PuzzleMaker(Board* nboard)
{
	a = nboard;
	for(int i = 0; i < 9; i++)
	{
		n_arr[i] = i+1;
	}
}

Board* PuzzleMaker::fillBoard(int numClues)
{
	std::vector<int> work_arr;
	int work_size = 0;
	srand(time(NULL));
	for(int i = 0; i < 9; i++)
	{
		work_arr.assign(n_arr, n_arr+9);
		Row* curr_row = a->getRow(i);
		for( int j = 0; j < 9; j ++)
		{
			work_size = work_arr.size();
			int rand_index = (rand() % work_size);

			if( checkCol(work_arr[rand_index],j,i) )
			{
				Tile* curr_tile = a->setTile(i,j,work_arr[rand_index]);
				curr_row->setTile(j, curr_tile);
				a->getCol(j)->setTile(i,curr_tile);
				a->getSqr(i,j)->setTile(i,j,curr_tile);

				work_arr.erase(work_arr.begin()+rand_index);
				std::cout << "(" << i << ", " << j << ")" << std::endl;
			}
			else{
				j--;
				std::cout << "(" << i << ", " << j << ")" << std::endl;
			}
		}
	}
	return 0;
}

bool PuzzleMaker::checkRow(int num, int row, int xpos)
{
	Row* toCheck = a->getRow(row);
	for(int i = 0; i < 9; i++)
	{
		int check = toCheck->getTile(i)->getNum();
		if( num == check && i != xpos)
			return false;
	}
	return true;
}

bool PuzzleMaker::checkCol(int num, int col, int ypos)
{
	Col* toCheck = a->getCol(col);
	for(int i = 0; i < 9; i++)
	{
		int check = toCheck->getTile(i)->getNum();
		if( num == check && i != ypos)
			return false;
	}
	return true;
}

bool PuzzleMaker::checkSqr(int num, int sqr, int xpos)
{
	Sqr* toCheck = a->getSqr(sqr);
	for(int i = 0; i < 9; i++)
	{
		int check = toCheck->getTile(i)->getNum();
		if( num == check && i != xpos)
			return false;
	}
	return true;
}

int* PuzzleMaker::getNArr()
{
	return n_arr;
}

bool PuzzleMaker::setWorkingArr(int* arr)
{
	memcpy(arr,&n_arr,9*(sizeof(int)));
	return 1;
}
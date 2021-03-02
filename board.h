/*
 * board.h
 *
 *  Created on: 23 févr. 2021
 *      Author: alexirypinski
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <vector>

class Board {
	public:
		Board(int xSize, int ySize);
		int uncover(int x, int y);
		void flag(int x, int y);
		void print();



	private:
		float percentMines;
		void uncoverAdjacent(int x, int y);
		bool isMine(int x, int y);
		bool isZero(int x, int y);
		bool isCovered(int x, int y);

		std::vector<std::vector<int> > trueVals;
		std::vector<std::vector<char> > userVals;

		int xSize;
		int ySize;

		void mineGen();
		void numGen();
		void userValsGen();


};

#endif /* BOARD_H_ */


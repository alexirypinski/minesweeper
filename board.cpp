/*
 * board.cpp
 *
 *  Created on: 23 févr. 2021
 *      Author: alexirypinski
 */

#include "board.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>


Board::Board(int xSize, int ySize){
	percentMines = 0.2;
	trueVals.resize(xSize, std::vector<int>(ySize, 0));
	userVals.resize(xSize, std::vector<char>(ySize, 0));
	mineGen();
	numGen();
	userValsGen();
}

/*
in: VALID x and y coords for the board
out: an integer: -1, 0, 1.
-1 signifies that the block is a mine
0 signifies the block is zero
1 if the block is a nonzero number
updates userVals accordingly (does NOT print)
*/
int Board::uncover(int x, int y) {
	if (trueVals[x][y] == -1){
		return -1;
	} else if (trueVals[x][y] == 0) {
		//makes all adjacent values in userVals equal to zero
		uncoverAdjacent(x, y);
		return 0;
	} else {
		//uncovers userVals[x][y] in its character representation
		if (trueVals[x][y] == 1){
			userVals[x][y] = '1';
		} else if (trueVals[x][y] == 2){
			userVals[x][y] = '2';
		} else if (trueVals[x][y] == 3){
			userVals[x][y] = '3';
		} else if (trueVals[x][y] == 4){
			userVals[x][y] = '4';
		} else if (trueVals[x][y] == 5){
			userVals[x][y] = '5';
		} else if (trueVals[x][y] == 6){
			userVals[x][y] = '6';
		} else if (trueVals[x][y] == 7){
			userVals[x][y] = '7';
		} else if (trueVals[x][y] == 8){
			userVals[x][y] = '8';
		}
		return 1;
	}

}

bool Board::isCovered(int x, int y) {
	return userVals[x][y] == 'f' || userVals[x][y] == 'X';

}

void Board::flag(int x, int y){
	if (userVals[x][y] == 'X'){
		userVals[x][y] = 'f';
	} else if (userVals[x][y] == 'f'){
		userVals[x][y] = 'X';
	}
}

bool Board::isMine(int x, int y){
	if(x >= xSize || y >= ySize){
		return false;
	}
	return trueVals[x][y] == -1;
}

bool Board::isZero(int x, int y){
	if(x >= xSize || y >= ySize){
		return false;
	}
	return trueVals[x][y] == 0;
}

//in: a trueVals board populated with -1 mine values from mineGen
//out: a trueVals board with
void Board::numGen() {
	for (int i = 0; i < xSize; i++){
		for (int j = 0; j < ySize; j++){
			//making sure current block isn't a mine
			if (!isMine(i, j)){
				int numMines = 0;
				//checking all adjacent squares and counting mine occurences
				if (isMine(i + 1, j + 1)){
					numMines++;
				} if (isMine(i + 1, j)){
					numMines++;
				} if (isMine(i + 1, j - 1)){
					numMines++;
				} if (isMine(i, j - 1)){
					numMines++;
				} if (isMine(i - 1, j - 1)){
					numMines++;
				} if (isMine(i - 1, j)){
					numMines++;
				} if (isMine(i - 1, j + 1)){
					numMines++;
				} if (isMine(i, j + 1)){
					numMines++;
				}
				trueVals[i][j] = numMines;
			}
		}
	}
}

//in: nubile trueVals board
//out: a trueVals board populated with mines (value -1)
void Board::mineGen(){
	float k = std::floor((float) xSize * (float) ySize * percentMines);
	int K = k;
	//seed gen based on current time
	std::srand(std::time(0));
	for (int i = 0; i < K; i++){
		int num = rand() % (xSize * ySize);
		trueVals[(int) num / xSize][num % ySize] = -1;
	}
}

//out: a board full of Xs
void Board::userValsGen(){
	for (int i = 0; i < xSize; i++){
		for (int j = 0; j < ySize; j++){
			userVals[i][j] = 'X';
		}
	}
}

//out: the current state of userVals
void Board::print(){
	std::cout << std::setw(2);
	for(int i = 0; i < xSize; i++){
		for(int j = 0; j < ySize; j++){
			std::cout << userVals[i][j];
		}
		std::cout << "\n";
	}
}

void Board::uncoverAdjacent(int i, int j){
	userVals[i][j] = '0';
	if (isZero(i + 1, j + 1)){
		uncoverAdjacent(i + 1, j + 1);
	} if (isZero(i + 1, j)){
		uncoverAdjacent(i + 1, j);
	} if (isZero(i + 1, j - 1)){
		uncoverAdjacent(i + 1 , j - 1);
	} if (isZero(i, j - 1)){
		uncoverAdjacent(i, j - 1);
	} if (isZero(i - 1, j - 1)){
		uncoverAdjacent(i - 1, j - 1);
	} if (isZero(i - 1, j)){
		uncoverAdjacent(i - 1, j);
	} if (isZero(i - 1, j + 1)){
		uncoverAdjacent(i - 1, i + 1);
	} if (isZero(i, j + 1)){
		uncoverAdjacent(i, j + 1);
	}
}


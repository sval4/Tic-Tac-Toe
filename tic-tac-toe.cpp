#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include "board.h"

int main(int argc, char* argv[]){
	Board board;
	board.createGame();
	board.printBoard();
	board.play();

}
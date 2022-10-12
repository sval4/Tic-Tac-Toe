#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include "board.h"

Board::Board(){

}

void Board::play(){
	
}

void Board::createGame(){
	std::cout << "Enter the token you would like to use: "; 
	std::cin >> player_token;

	std::cout << "Enter the token you would like the computer to use: "; 
	std::cin >> computer_token;

	for(int i = 0; i < 3; i++){
		grid.push_back(std::vector<char>());
		for(int j = 0; j < 3; j++){
			grid[i].push_back(' ');
		}
	}
}

void Board::printBoard(){
	for(int i = 0 ; i < 3; i++){
		for(int j = 0; j < 2; j++){
			std::cout << grid[i][j] << "|";
		}
		std::cout << grid[i][2] << std::endl;
		if(i != 2)
		std::cout << "— — —" << std::endl;
	}
}
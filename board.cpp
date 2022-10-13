#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include "board.h"

Board::Board(){

}

bool Board::endGame(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (grid[i][j]==' '){
                return false;
            }
        }
    }
    return true;
}

int Board::revealResult(){
	//Check if row win has occured
	for(int row = 0; row < 3; row++){
		if(grid[row][0] == grid[row][1] && grid[row][1] == grid[row][2]){
			if(grid[row][0] == player_token){
				return -1;
			}else{
				return 1;
			}
		}
	}
	//Check if col win has occured
	for(int col = 0; col < 3; col++){
		if(grid[0][col] == grid[1][col] && grid[1][col] == grid[2][col]){
			if(grid[0][col] == player_token){
				return -1;
			}else{
				return 1;
			}
		}
	}

	//check if diagonal win has occured
	if((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) || (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])){
		if(grid[1][1] == player_token){
			return -1;
		}else{
			return 1;
		}
	}
	return 0;
}

void Board::play(){
	/*
	srand(time(NULL));
	bool player_turn = (rand() % 2 == 0) ? true : false;
	while(!endGame()){
		if(player_turn){
			int num;
			std::cout << "Make a move (ENTER # from 1-9): ";
			std::cin >> num;
			if()
		}else{

		}



		player_turn = !player_turn;
	}
	*/
}

int Board::minimax(int counter, bool player_turn){
    int score = revealResult();

    if (score == 1){
        return score;
    }else if (score == -1){
        return score;
    }else if (endGame()){
        return 0;
    }
 	int best;

    if (!player_turn){
        best = INT_MIN;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (grid[i][j]==' '){

                    grid[i][j] = computer_token;
                    best = std::max(best, minimax(counter+1, !player_turn));
                    grid[i][j] = ' ';
                }
            }
        }
        return best;
    }else{
        best = INT_MAX;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (grid[i][j]==' '){

                    grid[i][j] = player_token;
                    best = std::min(best, minimax(counter+1, !player_turn));
                    grid[i][j] = ' ';
                }
            }
        }
        return best;
    }
}


void Board::findBestMove(int& row, int& col){
    int best = INT_MIN;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (grid[i][j]==' '){

                grid[i][j] = computer_token;
                int move = minimax(0, false);
                grid[i][j] = ' ';

                if (move > best){
                	row = i;
                	col = j;
                	best = move;
                }
            }
        }
    }
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
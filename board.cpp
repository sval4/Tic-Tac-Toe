#include <iostream>
#include <climits>
#include <string>
#include <vector>
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

/* Return value needs to have higher magnitude than 1
because the +counter or -counter. Since counter starts at 0
max amount counter can become, while still affecting the return
value of minimax, is 8. So return values needs to be greater than 8  
*/
int Board::revealResult(){
	//Check if row win has occured
	for(int row = 0; row < 3; row++){
		if(grid[row][0] == grid[row][1] && grid[row][1] == grid[row][2]){
			if(grid[row][0] == player_token){
				return -9;
			}else if(grid[row][0] == computer_token){
				return 9;
			}
		}
	}
	//Check if col win has occured
	for(int col = 0; col < 3; col++){
		if(grid[0][col] == grid[1][col] && grid[1][col] == grid[2][col]){
			if(grid[0][col] == player_token){
				return -9;
			}else if(grid[0][col] == computer_token){
				return 9;
			}
		}
	}

	//check if diagonal win has occured
	if((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) || (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])){
		if(grid[1][1] == player_token){
			return -9;
		}else if(grid[1][1] == computer_token){
			return 9;
		}
	}
	return 0;
}

void Board::play(){
	srand(time(NULL));
	bool replay = true;
	while(replay){
		bool player_turn = (rand() % 2 == 0) ? true : false;

		while(!endGame() && revealResult() == 0){
			printBoard();
			if(player_turn){
				int num;
				int row;
				int col;
				std::cout << "Make a move (ENTER # from 1-9): ";
				std::cin >> num;
				if(num >= 1 && num <= 3){
					row = 0;
					col = num - 1;
				}else if(num >= 4 && num <= 6){
					row = 1;
					col = num - 4;
				}else if(num >= 7 && num <= 9){
					row = 2;
					col = num - 7;
				}
				
				if(grid[row][col] != ' '){
					std::cout << "Please make a move on an empty space" << std::endl;
					continue;
				}else{
					grid[row][col] = player_token;
				}
			}
			else{
				std::cout << "Computer Move:" << std::endl;
				int row;
				int col;
				findBestMove(row, col);
				grid[row][col] = computer_token;
			}
			player_turn = !player_turn;
		}

		printBoard();
		if(revealResult() < 0){
			std::cout << "Congratulations you won!" <<std::endl;
		}else if(revealResult() > 0){
			std::cout << "You Lost" <<std::endl;
		}else{
			std::cout << "It's a tie" << std::endl;
		}

		std::string answer;
		std::cout << "Would you like to replay? (y/n): ";
		std::cin >> answer;
		if(answer == "y"){
			clearGrid();
		}else{
			replay = false;
		}
	}
	
	
}

int Board::minimax(int counter, bool player_turn){
    int score = revealResult();
    if (score != 0){
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
                    //the - counter ensures quickest path to victory is taken
                    best = std::max(best, minimax(counter+1, !player_turn) - counter);
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
                    //the + counter assumes player is taking quickest path to victory
                    best = std::min(best, minimax(counter+1, !player_turn) + counter);
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
                int move = minimax(0, true);
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
	std::cout << "--------------------------------" << std::endl;
}

void Board::clearGrid(){
	for(int i = 0; i < (int)grid.size(); i++){
		for(int j = 0; j < (int) grid[i].size(); j++){
			grid[i][j] = ' ';
		}
	}
}
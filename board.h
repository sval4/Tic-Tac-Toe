#ifndef __board_h
#define __board_h
#include <string>
#include <fstream>
#include <vector>


class Board{
public:
	//Constructor
	Board();

	void createGame();
	void printBoard();
	void play();
	bool endGame();
	int revealResult();
	int minimax(int counter, bool player_turn);
	void findBestMove(int& row, int& col);

private:
	char player_token;
	char computer_token;
	std::vector<std::vector<char>> grid;
};

#endif


#include <iostream>
#include <random>

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void computerMove(char *spaces, char computer);
char getWinner(char *spaces, char player, char computer);

int main() {
	char spaces[9];
	std::fill(spaces, spaces + 9, ' ');
	char player = 'X';
	char computer = 'O';
	char winner = 'N';
	while (winner == 'N') {
		playerMove(spaces, player);
		winner = getWinner(spaces, player, computer);
		if (winner != 'N') break;
		computerMove(spaces, computer);
		winner = getWinner(spaces, player, computer);
	}
	if (winner == player)
		std::cout << "\nPLAYER WINS!\n";
	else if (winner == computer)
		std::cout << "\nCOMPUTER WINS!\n";
}

void drawBoard(char *spaces) {
	for (int i = 0; i < 9; i+=3) {
		std::cout << " " << spaces[i] << " | " << spaces[i + 1] << " | " << spaces[i + 2] << " \n";
		if (i != 6) {
			std::cout << "---|---|---\n";
		}
	}
}

void playerMove(char *spaces, char player) {
	int move;
	do {
		std::cout << "Enter move (1: top left, 2: top middle etc): \n";
		std::cin >> move;
	} while (move > 9 || move < 1 || spaces[move - 1] != ' ');
	spaces[move - 1] = player;
	drawBoard(spaces);
}

void computerMove(char *spaces, char computer) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 8);
	int move;
	do {
		move = distr(gen);
	} while (spaces[move] != ' ');
	std::cout << "Computer chooses slot " << move + 1 << '\n';
	spaces[move] = computer;
	drawBoard(spaces);
}

char getWinner(char *spaces, char player, char computer) {
	int wins[8][3] = {
		{0,1,2},
		{3,4,5},
		{6,7,8},
		{0,3,6},
		{1,4,7},
		{2,5,8},
		{0,4,8},
		{2,4,6}
	};
	for (auto &combo : wins) {
		if (spaces[combo[0]] == player && spaces[combo[1]] == player && spaces[combo[2]] == player ) {
			std::cout << "PLAYER WINS!";
			return player;
		}
		if (spaces[combo[0]] == computer && spaces[combo[1]] == computer && spaces[combo[2]] == computer ) {
			std::cout << "COMPUTER WINS!";
			return computer;
		}

	}
	return 'N';
}

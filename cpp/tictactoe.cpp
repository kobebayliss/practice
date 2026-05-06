#include <iostream>
#include <random>

void drawBoard();
void playerMove(char player);
void computerMove(char computer);
char getWinner(char player, char computer);

char spaces[9];

int main() {
	std::fill(spaces, spaces + 9, ' ');
	char player = 'X';
	char computer = 'O';
	char winner = 'N';
	while (winner == 'N') {
		playerMove(player);
		winner = getWinner(player, computer);
		if (winner != 'N') break;
		computerMove(computer);
		winner = getWinner(player, computer);
	}
	if (winner == player)
		std::cout << "\nPLAYER WINS!\n";
	else if (winner == computer)
		std::cout << "\nCOMPUTER WINS!\n";
}

void drawBoard() {
	for (int i = 0; i < 9; i+=3) {
		std::cout << " " << spaces[i] << " | " << spaces[i + 1] << " | " << spaces[i + 2] << " \n";
		if (i != 6) {
			std::cout << "---|---|---\n";
		}
	}
	std::cout << '\n';
}

void playerMove(char player) {
	int move;
	do {
		std::cout << "Enter move (1: top left, 2: top middle, etc): \n";
		std::cin >> move;
	} while (move > 9 || move < 1 || spaces[move - 1] != ' ');
	spaces[move - 1] = player;
	drawBoard();
}

void computerMove(char computer) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 8);
	int move;
	do {
		move = distr(gen);
	} while (spaces[move] != ' ');
	std::cout << "\nComputer chooses slot " << move + 1 << '\n';
	spaces[move] = computer;
	drawBoard();
}

char getWinner(char player, char computer) {
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
			return player;
		}
		if (spaces[combo[0]] == computer && spaces[combo[1]] == computer && spaces[combo[2]] == computer ) {
			return computer;
		}

	}
	return 'N';
}

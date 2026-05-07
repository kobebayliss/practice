#include <iostream>

class Spreadsheet {
	int rows;
	int cols;

public:
	Spreadsheet(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
	}
	bool runCommand(std::string command) {
		int first_space = command.find(' ');
		std::string keyword = command.substr(0, first_space);
		if (keyword == "SET") {
			// set logic
		} else if (keyword == "PRINT") {
			// print logic
		} else if (keyword == "EXIT") {
			// exit logic
		} else {
			std::cout << "Enter a valid command.";
		}
	}
};

int main() {
	int rows, cols;
	std::cout << "Welcome to your spreadsheet.\n";
	do {
		std::cout << "Enter number of rows and columns (eg. '2 3'): \n";
		std::cin >> rows >> cols;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (std::cin.fail() || rows <= 0 || cols <= 0);

	std::string command;
	do {
		std::cout << "Enter commands (SET A1 50, PRINT, EXIT): ";
		std::getline(std::cin, command);

	} while (command != "EXIT");
	return 0;
}

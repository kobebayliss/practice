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
		if (command == "SET") {
			return set(command);
		} else if (command == "PRINT") {
			std::cout << "print command\n";
		} else if (command == "EXIT") {
			std::cout << "exit command\n";
		} else {
			std::cout << "Enter a valid command.\n";
		}
		return true;
	}
	bool set(std::string command) {
		int row, col;
		std::string value;
		std::cout << "Enter a square to change (eg. '1 4'): \n";
		std::cin >> row >> col;
		std::cin.ignore();
		std::cout << "enter value (eg. =14 or =1,4 + 5,3): \n";
		std::getline(std::cin, value);
		value = value.substr(1);
		size_t opIndex = value.find_first_of("+-/*");
		if (opIndex == std::string::npos) {
			// basic setting logic
		} else {
			// setting from other squares logic
		}
		return true;
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
	std::cin.ignore(10000, '\n');
	Spreadsheet sheet(rows, cols);
	std::string command;
	do {
		std::cout << "Enter command (SET A1 50, PRINT, EXIT): ";
		std::getline(std::cin, command);
		sheet.runCommand(command);

	} while (command != "EXIT");
	return 0;
}

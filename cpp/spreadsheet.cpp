#include <iomanip>
#include <iostream>

class Spreadsheet {
private:
	int rows, cols;
	int** sheet;

	void print() {
		const int cellWidth = 8;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				std::cout << "|" << std::setw(cellWidth - 1) << sheet[i][j];
			}
			std::cout << "|\n";
		}
	}

	bool set(std::string command) {
		int row, col;
		std::string value;
		std::cout << "Enter a square to change (eg. '0 4'): \n";
		std::cin >> row >> col;
		std::cin.ignore();
		std::cout << "enter value (eg. =14 or =1,4 + 5,3): \n";
		std::getline(std::cin, value);
		value = value.substr(1);
		int result = evaluateExpression(value);
		if (result == -1)
			return false;
		sheet[row][col] = result;
		std::cout << "You have set " << row << ',' << col << " to " << result << ".\n";
		return true;
	}

	int evaluateExpression(std::string expression) {
		size_t opIndex = expression.find_first_of("+-/*");
		if (opIndex == std::string::npos) {
			try {
				return std::stoi(expression);
			} catch (...) {
				std::cout << "Enter an integer number or formula only.\n";
				return -1;
			}
		} else {
			return evaluateFormula(expression, opIndex);
		}
	}

	int evaluateFormula(std::string expression, size_t opIndex) {
		char op = expression[opIndex];
		std::string left = expression.substr(0, opIndex);
		std::string right = expression.substr(opIndex + 1);
		left.erase(std::remove(left.begin(), left.end(), ' '), left.end());
		right.erase(std::remove(right.begin(), right.end(), ' '), right.end());
		int l1, l2, r1, r2;
		size_t leftComma = left.find(',');
		size_t rightComma = right.find(',');
		if (leftComma == std::string::npos || rightComma == std::string::npos) {
			std::cout << "Invalid formula format.";
			return -1;
		}
		l1 = std::stoi(left.substr(0, leftComma));
		l2 = std::stoi(left.substr(leftComma + 1));
		r1 = std::stoi(right.substr(0, rightComma));
		r2 = std::stoi(right.substr(rightComma + 1));
		int leftValue = sheet[l1][l2];
		int rightValue = sheet[r1][r2];
		switch (op) {
		case '+':
			return leftValue + rightValue;
			break;
		case '-':
			return leftValue - rightValue;
			break;
		case '*':
			return leftValue * rightValue;
			break;
		case '/':
			if (rightValue == 0) {
				std::cout << "Division by zero not allowed.\n";
				return false;
			}
			return leftValue / rightValue;
			break;
		default:
			std::cout << "Unknown operator.\n";
			return -1;
		}
	}

public:
	Spreadsheet(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
		sheet = new int*[rows];
		for (int i = 0; i < rows; i++) {
			sheet[i] = new int[cols];
			std::fill(sheet[i], sheet[i] + cols, 0);
		}
	}
	~Spreadsheet() {
		for (int i = 0; i < rows; i++) {
			delete[] sheet[i];
		}
		delete[] sheet;
	}
	bool runCommand(std::string command) {
		if (command == "SET") {
			if (!set(command)) {
				std::cout << "Failed to set cell.\n";
			}
		} else if (command == "PRINT") {
			print();
		} else if (command == "EXIT") {
			std::cout << "Exiting spreadsheet...\n";
		} else {
			std::cout << "Enter a valid command.\n";
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
		std::cout << "Enter command (SET, PRINT, EXIT): ";
		std::getline(std::cin, command);
		sheet.runCommand(command);

	} while (command != "EXIT");
	return 0;
}

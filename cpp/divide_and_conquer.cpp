#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
	std::vector<std::vector<int>> rows;
	std::string line;

	while (std::getline(std::cin, line)) {
	if (line.empty()) continue;
	std::vector<int> row;
	std::istringstream iss(line);
	int value;
	while (iss >> value) {
	    row.push_back(value);
	}
	rows.push_back(row);
	}

	int n = rows[1].size();
	for (int i = 0; i < n; i++) {
	    std::cout << rows[1][i] + rows[0].size() << '\n';
	}
	return 0;
}

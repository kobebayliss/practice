#include <iostream>
#include <vector>
#include <memory>

int main() {
	size_t nodes;
	std::vector<std::unique_ptr<std::vector<std::vector<size_t>>>> graphs;  // stores pointers to each graph, which is a 2d vector for adj matrix
	do {
		std::cin >> nodes;
		if (nodes == 0) {
			break;
		}
		std::vector<std::vector<size_t>> adj_matrix(nodes, std::vector<size_t>(nodes));
		for (size_t i = 0; i < nodes; i++) {
			for (size_t j = 0; j < nodes; j++) {
				std::cin >> adj_matrix[i][j];
			}
		}
		graphs.push_back(std::make_unique<std::vector<std::vector<size_t>>>(adj_matrix));
	} while (nodes != 0);
	std::cout << graphs[0]->at(0).at(2);
	return 0;
}

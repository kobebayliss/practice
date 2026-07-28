#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <unordered_set>
#include <tuple>
#include <functional>

using AdjMatrix = std::vector<std::vector<size_t>>;
using EdgeData = std::tuple<size_t, size_t, size_t>;  // edge weight, node 1, node 2

int main() {
	size_t nodes;
	std::vector<std::unique_ptr<AdjMatrix>> graphs;  // stores pointers to each graph, which is a 2d vector for adj matrix
	do {
		std::cin >> nodes;
		if (nodes == 0) {
			break;
		}
		AdjMatrix adj_matrix(nodes, std::vector<size_t>(nodes));
		for (size_t i = 0; i < nodes; i++) {
			for (size_t j = 0; j < nodes; j++) {
				std::cin >> adj_matrix[i][j];
			}
		}
		graphs.push_back(std::make_unique<AdjMatrix>(std::move(adj_matrix)));
	} while (nodes != 0);
	for (size_t i = 0; i < graphs.size(); i++) {
		size_t total_weight = 0;
		AdjMatrix& graph = *graphs[i];
		std::unordered_set<size_t> seen;
		std::priority_queue<EdgeData, std::vector<EdgeData>, std::greater<EdgeData>> edges;
		for (size_t j = 0; j < graph.size(); j++) {
			for (size_t k = j + 1; k < graph[j].size(); k++) {
				size_t edge_weight = graph[j][k];
				if (edge_weight != 0) {
					EdgeData edge(edge_weight, j, k);
					edges.push(edge);
				}
			}
		}
		while (!(edges.empty())) {
			EdgeData edge = edges.top();
			edges.pop();
			size_t edge1 = std::get<1>(edge);
			size_t edge2 = std::get<2>(edge);
			if (seen.find(edge1) != seen.end() && seen.find(edge2) != seen.end()) {
				continue;
			}
			seen.insert(edge1);
			seen.insert(edge2);
			total_weight += std::get<0>(edge);
		}
		std::cout << total_weight << std::endl;
	}
	return 0;
}

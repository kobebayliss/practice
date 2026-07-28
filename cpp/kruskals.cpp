#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <tuple>
#include <functional>

using AdjMatrix = std::vector<std::vector<size_t>>;
using EdgeData = std::tuple<size_t, size_t, size_t>;  // edge weight, node 1, node 2

size_t fetch_root(std::vector<size_t> &parent, size_t x) {
	while (parent[x] != x) {
		parent[x] = parent[parent[x]];
		x = parent[x];
	}
	return x;
}

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
		std::vector<size_t> parent(graph.size());
		std::priority_queue<EdgeData, std::vector<EdgeData>, std::greater<EdgeData>> edges;
		for (size_t j = 0; j < graph.size(); j++) {
			parent[j] = j;
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
			size_t root1 = fetch_root(parent, edge1);
			size_t root2 = fetch_root(parent, edge2);
			if (root1 == root2) {
				continue;
			}
			parent[root1] = root2;
			total_weight += std::get<0>(edge);
		}
		std::cout << total_weight << std::endl;
	}
	return 0;
}

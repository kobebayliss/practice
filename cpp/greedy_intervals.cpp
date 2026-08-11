// no ai used
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	size_t n;
	std::cin >> n;
	std::cin.ignore();
	std::vector<size_t> results;
	results.reserve(n);
	for (size_t i = 0; i < n; i++) {
		std::vector<std::pair<size_t, size_t>> values;
		while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
			int a, b;
			std::cin >> a >> b;
			values.push_back({a, b});
		}
		std::cin.ignore();
		std::vector<std::pair<size_t, int>> events;
		for (auto& [start, finish] : values) {
			events.push_back({start, 1});
			events.push_back({finish, -1});
		}
		std::sort(events.begin(), events.end(),
				[](auto& a, auto& b)
				{
					if (a.first == b.first) return a.second > b.second;
					return a.first < b.first;
				}
		);
		int count = 0;
		int highest = 0;
		for (auto& [time, change] : events) {
			count += change;
			if (count > highest) {
				highest = count;
			}
		}
		std::cout << highest << '\n';
	}
	return 0;
}

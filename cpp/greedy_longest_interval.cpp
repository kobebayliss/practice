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
		std::sort(values.begin(), values.end(),
				[](auto& a, auto& b)
				{
					return a.first < b.first;
				}
		);
		size_t cur_start = 0;
		size_t cur_end = 0;
		size_t longest_interval = 0;
		size_t longest = 0;
		bool first = true;
		for (auto& [start, end] : values) {
			if (first) {
				cur_start = start;
				cur_end = end;
				longest_interval = end - start;
				first = false;
				continue;
			}
			if (start <= cur_end) {
				cur_end = std::max(end, cur_end);
				longest_interval = cur_end - cur_start;
			} else {
				if (longest_interval > longest) {
					longest = longest_interval;
				}
				longest_interval = end - start;
				cur_start = start;
				cur_end = end;
			}
		}
		if (longest_interval > longest) {
			longest = longest_interval;
		}
		std::cout << longest << '\n';
	}
	return 0;
}

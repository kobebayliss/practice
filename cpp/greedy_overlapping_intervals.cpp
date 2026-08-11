// no ai was used
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
        std::vector<std::pair<int, int>> values;

        while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
            int a, b;
            std::cin >> a >> b;
            values.push_back({a, b});
        }
        std::cin.ignore();
        std::sort(values.begin(), values.end(),
                [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                    return a.second < b.second;
                }
        );

        size_t count = 0;
        bool first = true;
        int last_end = 0;

        for (auto& [start, finish] : values) {
            if (first || start > last_end) {
                count++;
                last_end = finish;
                first = false;
            }
        }

        results.push_back(count);
    }

    for (size_t total : results) {
        std::cout << total << '\n';
    }

    return 0;
}

#include <iostream>

int bsearch(int arr[], int size, int target);

int main() {
    int numbers[] = {1, 3, 7, 10, 16, 29, 100, 1001};
    int size = sizeof(numbers)/sizeof(numbers[0]);
    int target;
    std::cout << "Enter a target: " << '\n';
    std::cin >> target;
    std::cout << bsearch(numbers, size, target);
}

int bsearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int val = (left + right) / 2;
        if (arr[val] < target) {
            left = val + 1;
        } else {
            right = val - 1;
        }
    }
    return left;
}
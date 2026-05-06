#include <iostream>

void swap(int* a, int* b);

int main() {
    int num1;
    int num2;
    std::cout << "Enter first num: " << '\n';
    std::cin >> num1;
    std::cout << "Enter second num: " << '\n';
    std::cin >> num2;
    int *pNum1 = &num1;
    int *pNum2 = &num2;
    swap(pNum1, pNum2);
    std::cout << "num1 = " << *pNum1 << " and num2 = " << *pNum2;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

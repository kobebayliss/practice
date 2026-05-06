#include <iostream>

template <typename T> T* createArray(int capacity, int& size) {
	size = 0;
	return new T[capacity];
}

template <typename T> T* resize(T* arr, int& capacity, int size) {
	capacity *= 2;
	T* newArr = new T[capacity];

	// copy elements
	for (int i = 0; i < size; i++) {
		newArr[i] = arr[i];
	}
	delete[] arr;
	return newArr;
}

template <typename T> void append(T*& arr, int& size, int& capacity, T value) {
	if (size == capacity) {
		arr = resize(arr, capacity, size);
	}
	arr[size++] = value;
}

template <typename T> void printArray(T* arr, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}

template <typename T> void pop(T* arr, int& size) {
	if (size > 0) {
		size--;
	}
}

template <typename T> void insertAt(T*& arr, int& size, int& capacity, int index, T value) {
	if (size == capacity) {
		arr = resize(arr, capacity, size);
	}
	size++;
	T temp_prev = arr[index];
	T temp_next;
	arr[index] = value;
	for (int i = index + 1; i < size; i++) {
		temp_next = arr[i];
		arr[i] = temp_prev;
		temp_prev = temp_next;
	}
}

template <typename T> int find(T* arr, int size, T target) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == target) {
			return i;
		}
	}
	return -1;
}

int main() {
	int size, capacity = 2;

	int* arr = createArray<int>(capacity, size);

	append(arr, size, capacity, 10);
	append(arr, size, capacity, 20);
	append(arr, size, capacity, 30);
	append(arr, size, capacity, 35);
	pop(arr, size);
	printArray(arr, size);
	append(arr, size, capacity, 24);
	append(arr, size, capacity, 500);
	insertAt(arr, size, capacity, 2, 19);
	printArray(arr, size);
	std::cout << find(arr, size, 24);

	delete[] arr;
}

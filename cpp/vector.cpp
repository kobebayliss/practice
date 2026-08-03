#include <iostream>

template <typename T>
class Vector {
	T* data;
	size_t size;
	size_t capacity;
public:
	Vector() : size{0}, capacity{1} {
		data = new T[capacity];
	}


	void push(const T& element) {
		if (size == capacity) {
			capacity *= 2;
			T* new_data = new T[capacity];
			for (size_t i{0}; i < size; i++) {
				new_data[i] = data[i];
			}
			delete[] data;
			data = new_data;
		}
		data[size] = element;
		size++;
	}
};
		

int main() {
	return 0;
}

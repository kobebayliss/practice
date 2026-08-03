#include <algorithm>
#include <utility>
#include <cassert>

template <typename T>
class Vector {
	T* data;
	size_t size;
	size_t capacity;
	void resize() {
		capacity *= 2;
		T* new_data = new T[capacity];
		for (size_t i{0}; i < size; i++) {
			new_data[i] = std::move(data[i]);
		}
		delete[] data;
		data = new_data;
	}
public:
	Vector() : size{0}, capacity{1} {
		data = new T[capacity];
	}
	// rule of 5 functions
	~Vector() {
		delete[] data;
	}
	Vector(const Vector& other) : size(other.size), capacity(other.capacity) {
		data = new T[capacity];
		std::copy(other.data, other.data + other.size, data);
	}
	Vector& operator=(const Vector& other) {
		if (this != &other) {
			delete[] data;
			size = other.size;
			capacity = other.capacity;
			data = new T[capacity];
			std::copy(other.data, other.data + other.size, data);
		}
		return *this;
	}
	Vector(Vector&& other) noexcept : size(other.size), capacity(other.capacity) {
		data = other.data;
		other.data = nullptr;
	}
	Vector& operator=(Vector&& other) noexcept {
		if (this != &other) {
			delete[] data;
			size = other.size;
			capacity = other.capacity;
			data = other.data;
			other.data = nullptr;
		}
		return *this;
	}

	T& operator[](size_t i) {
		return data[i];
	}
	void push(const T& element) {
		if (size == capacity) {
			resize();
		}
		data[size] = element;
		size++;
	}
	void push(T&& element) {
		if (size == capacity) {
			resize();
		}
		data[size] = std::move(element);
		size++;
	}
	void pop() {
		if (size == 0) return;
		size--;
	}
	T& top() {
		return data[size - 1];
	}
	bool empty() {
		return size == 0;
	}
};

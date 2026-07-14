#include <iostream>
#include <string>
#include <vector>

struct Item {
	std::string name;
	size_t quantity;
	double price;
	Item(std::string name, size_t quantity, double price) {
		this->name = name;
		this->quantity = quantity;
		this->price = price;
	}
};

template <typename Filter> void generateReport(std::vector<Item>* pItems, Filter filter, std::string (*derive)(Item)) {
	for (const Item& item : *pItems) {
		if (filter(item)) {
			std::cout << item.name << ": " << derive(item) << std::endl;
		}
	}
}

auto makeThresholdTracker(double startingTotal) {
	double total = startingTotal;
	size_t count = 0;
	return [total, count](const Item& item) mutable {
		total += (item.quantity * item.price);
		count++;
		std::string s = std::format("{}: running total = ${} ({} items tracked)", item.name, total, count);
		return s;
	};
}

int main() {
	Item i1("a", 500, 14.99);
	Item i2("b", 750, 21.99);
	Item i3("c", 1200, 9.99);
	Item i4("d", 300, 49.95);
	Item i5("e", 100, 5.49);
	Item i6("f", 2000, 99.99);
	Item i7("g", 850, 17.50);
	Item i8("h", 650, 29.95);
	std::vector<Item> items = {i1, i2, i3, i4, i5, i6, i7, i8};
	std::cout << "Enter quantity threshold: " << std::endl;
	size_t quantity_threshold;
	std::cin >> quantity_threshold;
	generateReport(&items, [quantity_threshold](Item i) { return i.quantity > quantity_threshold; }, [](Item i) { return std::to_string(i.quantity * i.price); });
	auto tracker1 = makeThresholdTracker(0.0);
	auto tracker2 = makeThresholdTracker(1000.0);
	for (Item item : items) {
	    std::cout << tracker1(item) << std::endl;
	}
	for (Item item : items) {
	    std::cout << tracker2(item) << std::endl;
	}
	return 0;
}

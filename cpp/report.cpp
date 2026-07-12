#include <iostream>
#include <string>
#include <vector>

struct Item {
	std::string name;
	size_t quantity;
	double price;
};

void generateReport(std::vector<Item>* pItems, bool (*filter)(Item), std::string (*derive)(Item)) {
	for (const Item& item : *pItems) {
		if (filter(item)) {
			std::cout << item.name << ": " << derive(item) << std::endl;
		}
	}
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
	generateReport(&items, [](Item i) { return i.quantity > 600; }, [](Item i) { return std::to_string(i.quantity * i.price); });
	return 0;
}

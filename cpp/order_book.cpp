#include <iostream>
#include <map>

struct Order {
	inline static size_t id = 1;
	size_t quantity;
	Order* next;
	Order* prev;

public:
	Order(size_t quantity, Order* next, Order* prev) {
		this->quantity = quantity;
		this->next = next;
		this->prev = prev;
	}
};

struct PriceLevel {
	double price;
	size_t volume;
	Order* head;
	Order* tail;

public:
	PriceLevel(double price, size_t volume, Order* head, Order* tail) {
		this->price = price;
		this->volume = volume;
		this->head = head;
		this->tail = tail;
	}
};

typedef std::map<double, PriceLevel> prices_map;
class OrderBook {
	prices_map buy_orders;
	prices_map sell_orders;

public:
	void place_order(double price, size_t quantity, std::string side) {
		Order* order = new Order(quantity, nullptr, nullptr);
		prices_map& map = (side == "buy") ? buy_orders : (side == "sell") ? sell_orders : throw std::invalid_argument("Invalid side");
		if (map.find(price) == map.end()) {
			// new price level
			map.emplace(price, PriceLevel(price, quantity, order, order));
		} else {
			// existing price level
		}
	}
};

int main() { return 0; }

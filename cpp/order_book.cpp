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
		auto it = map.find(price);
		if (it == map.end()) {
			// new price level
			map.emplace(price, PriceLevel(price, quantity, order, order));
		} else {
			// existing price level
			PriceLevel& price_level = it->second;
			price_level.volume += quantity;
			Order* tail = price_level.tail;
			tail->next = order;
			order->prev = tail;
			price_level.tail = order;
			std::cout << &price_level.tail;
		}
	}
};

int main() {
	OrderBook* order_book = new OrderBook();
	order_book->place_order(33.34, 20, "buy");
	order_book->place_order(33.67, 30, "buy");
	return 0;
}

#include <iostream>
#include <map>
#include <stdexcept>

struct Order {
	inline static size_t next_id = 1;
	size_t id;
	size_t quantity;
	Order* next;
	Order* prev;

public:
	Order(size_t quantity, Order* next, Order* prev) {
		this->id = next_id++;
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
			std::cout << price_level.tail->quantity << std::endl;
			std::cout << price_level.head->quantity << std::endl;
		}
	}
	double get_top(std::string side) {
		if (side == "buy") {
			return buy_orders.rbegin()->first;
		} else if (side == "sell") {
			return sell_orders.begin()->first;
		} else {
			throw std::invalid_argument("Invalid side");
		}
	}
};

int main() {
	OrderBook* order_book = new OrderBook();
	order_book->place_order(33.34, 20, "buy");
	order_book->place_order(33.34, 30, "buy");
	order_book->place_order(33.36, 50, "buy");
	order_book->place_order(33.40, 20, "sell");
	order_book->place_order(33.39, 20, "sell");
	std::cout << order_book->get_top("buy") << std::endl;
	std::cout << order_book->get_top("sell") << std::endl;
	return 0;
}

#include <iostream>
#include <map>

struct Order {
	inline static size_t next_id = 1;
	size_t id;
	double price;
	size_t quantity;
	std::string side;
	Order* next;
	Order* prev;

public:
	Order(double price, size_t quantity, std::string side, Order* next, Order* prev) {
		this->id = next_id++;
		this->price = price;
		this->quantity = quantity;
		this->side = side;
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
	std::unordered_map<size_t, Order*> orders;

public:
	void place_order(double price, size_t quantity, std::string side) {
		Order* order = new Order(price, quantity, side, nullptr, nullptr);
		orders[order->id] = order;
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
		}
		std::cout << "Your order is Order # : " << order->id << std::endl;
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
	void cancel_order(size_t id) {
		Order* order = orders.find(id)->second;
		prices_map& map = (order->side == "buy") ? buy_orders : sell_orders;
		PriceLevel& price_level = map.find(order->price)->second;
		if (order->next != nullptr) {
			Order* next_order = order->next;
			if (order->prev != nullptr) {
				Order* prev_order = order->prev;
				prev_order->next = next_order;
				next_order->prev = prev_order;
			} else {
				next_order->prev = nullptr;
				price_level.head = next_order;
			}
		} else if (order->prev != nullptr) {
			Order* prev_order = order->prev;
			prev_order->next = nullptr;
			price_level.tail = prev_order;
		}
		price_level.volume -= order->quantity;
		if (price_level.volume == 0) {
			map.erase(order->price);
		}
		order->next = nullptr;
		order->prev = nullptr;
		orders.erase(id);
		delete order;
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
	order_book->cancel_order(3);
	std::cout << order_book->get_top("buy") << std::endl;
	delete order_book;
	return 0;
}

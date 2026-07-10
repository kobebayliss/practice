#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

enum class Side { Buy, Sell };

using hashmap = std::unordered_map<std::string, float>;

class PnLTracker {
	hashmap instruments;
	hashmap balances;
	std::unordered_map<std::string, std::unordered_map<std::string, float>> holdings;

public:
	PnLTracker(hashmap instruments) { this->instruments = instruments; }
	void process_fill(const std::string& trader, const std::string& instrument, float quantity, float price, Side side) {
		auto it = balances.find(trader);
		if (it == balances.end()) {
			std::cout << "Inserting new trader..." << std::endl;
			balances.insert({trader, 0});
			holdings.insert({trader, {}});
		}
		instruments[instrument] = price;
		float total = price * quantity;
		if (side == Side::Buy) {
			balances[trader] -= total;
			holdings[trader][instrument] += quantity;
		} else {
			balances[trader] += total;
			holdings[trader][instrument] -= quantity;
		}
	}
	float get_trader_pnl(const std::string& trader) {
		auto it = balances.find(trader);
		if (it == balances.end()) {
			std::cout << "Trader not registered" << std::endl;
			return 0;
		}
		float balance = balances[trader];
		float total_holdings = 0;
		for (auto it2 = holdings[trader].begin(); it2 != holdings[trader].end(); it2++) {
			std::string instrument = it2->first;
			float quantity = it2->second;
			total_holdings += (instruments[instrument] * quantity);
		}
		return balance + total_holdings;
	}
	std::string get_best_trader() {
		auto it = balances.begin();
		if (it == balances.end()) {
			return "No traders in system.";
		}
		float best_pnl = get_trader_pnl(it->first);
		std::string best_trader = it->first;
		float pnl;
		while (it != balances.end()) {
			pnl = get_trader_pnl(it->first);
			if (pnl > best_pnl) {
				best_pnl = pnl;
				best_trader = it->first;
			}
			it++;
		}
		return best_trader;
	}
	std::string* get_top_k_traders(size_t k) {
		std::priority_queue<std::pair<float, std::string>> pq;
		auto it = balances.begin();
		if (it == balances.end() || k > balances.size()) {
			return nullptr;
		}
		while (it != balances.end()) {
			pq.push(std::pair(get_trader_pnl(it->first), it->first));
			it++;
		}
		std::string* trader_names = new std::string[k];
		for (int i = 0; i < k; i++) {
			auto info = pq.top();
			pq.pop();
			trader_names[i] = info.second;
		}
		return trader_names;
	}
};

int main() {
	PnLTracker pnltracker({{"AAPL", 150.0}, {"MSFT", 100.5}});
	pnltracker.process_fill("John", "AAPL", 20, 145.0, Side::Buy);
	pnltracker.process_fill("John", "AAPL", 15, 144.0, Side::Sell);
	pnltracker.process_fill("Steve", "AAPL", 10, 144.0, Side::Buy);
	pnltracker.process_fill("Steve", "AAPL", 10, 146.0, Side::Sell);
	pnltracker.process_fill("Mark", "AAPL", 10, 146.0, Side::Buy);
	pnltracker.process_fill("Mark", "AAPL", 10, 150.0, Side::Sell);
	pnltracker.process_fill("John", "AAPL", 15, 150.0, Side::Buy);
	std::cout << pnltracker.get_trader_pnl("Steve") << std::endl;
	std::cout << pnltracker.get_best_trader() << std::endl;
	size_t k = 2;
	std::string* traders = pnltracker.get_top_k_traders(k);
	for (int i = 0; i < k; i++) {
		std::cout << traders[i] << std::endl;
	}
	delete[] traders;
	return 0;
}

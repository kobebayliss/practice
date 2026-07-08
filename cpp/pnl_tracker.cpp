#include <iostream>
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
	void process_fill(std::string trader, std::string instrument, float quantity, float price, Side side) {
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
	float get_trader_pnl(std::string trader) {
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
};

int main() {
	PnLTracker pnltracker({{"AAPL", 150.0}, {"MSFT", 100.5}});
	pnltracker.process_fill("John", "AAPL", 20, 145.0, Side::Buy);
	pnltracker.process_fill("John", "AAPL", 15, 148.0, Side::Sell);
	std::cout << pnltracker.get_trader_pnl("John") << std::endl;
	return 0;
}

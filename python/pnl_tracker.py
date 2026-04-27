import heapq

class PnLTracker:
    def __init__(self, market_prices):
        self.market_prices = market_prices
        self.positions = {}  # trader_id: {instrument: quantity}
        self.cash = {}       # trader_id: cash balance

    def process_fill(self, trader_id, instrument, quantity, price, side):
        if trader_id not in self.positions:
            self.positions[trader_id] = {}
            self.cash[trader_id] = 0

        if side == "buy":
            if instrument in self.positions[trader_id]:
                self.positions[trader_id][instrument] += quantity
            else:
                self.positions[trader_id][instrument] = quantity
            self.cash[trader_id] -= quantity * price
        elif side == "sell":
            # we are holding the instrument
            if instrument in self.positions[trader_id]:
                final_quantity = self.positions[trader_id][instrument] - quantity
                if final_quantity == 0:
                    del self.positions[trader_id][instrument]
                elif final_quantity > 0:
                    self.positions[trader_id][instrument] -= quantity
                self.cash[trader_id] += quantity * price

    def get_pnl(self, trader_id):
        if trader_id not in self.positions:
            return 0
        market_value = 0
        for instrument, quantity in self.positions[trader_id].items():
            market_value += quantity * self.market_prices[instrument]
        return market_value + self.cash[trader_id]

    def get_best_trader(self):
        best = None
        best_pnl = float('-inf')
        for trader_id in self.positions:
            pnl = self.get_pnl(trader_id)
            if pnl > best_pnl:
                best = trader_id
                best_pnl = pnl
        return best
    
    def get_top_k_traders(self, k):
        if k > len(self.positions):
            return "k too big"
        heap = []
        result = []
        for trader_id in self.positions:
            heapq.heappush_max(heap, (self.get_pnl(trader_id), trader_id))
        while len(result) < k:
            result.append(heapq.heappop_max(heap)[1])
        return result

    
tracker = PnLTracker({"AAPL": 150.0})

# trader sells entire position
tracker.process_fill("T1", "AAPL", 100, 150.0, "buy")
tracker.process_fill("T1", "AAPL", 100, 155.0, "sell")
print(tracker.cash["T1"])  # what does this print?

# all traders are losing money
tracker2 = PnLTracker({"AAPL": 100.0})
tracker2.process_fill("T1", "AAPL", 100, 150.0, "buy")
tracker2.process_fill("T2", "AAPL", 20000, 150.0, "buy")
tracker2.process_fill("T3", "AAPL", 400, 151.0, "buy")
tracker2.process_fill("T4", "AAPL", 500, 130.0, "buy")
print(tracker2.get_top_k_traders(2))
print(tracker2.get_best_trader())  # what does this print?
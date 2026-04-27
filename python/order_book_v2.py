import heapq

class OrderBook:
    def __init__(self):
        self.bids = []  # buy orders
        self.asks = []  # sell orders

    def add_order(self, side, price, quantity):
        if side == "buy":
            heapq.heappush(self.bids, (-price, quantity))
        elif side == "sell":
            heapq.heappush(self.asks, (price, quantity))

    def best_bid(self):
        if not self.bids:
            return None
        return -self.bids[0][0]

    def best_ask(self):
        if not self.asks:
            return None
        return self.asks[0][0]
    
    def match_orders(self):
        if not self.bids or not self.asks:
            return None
        best_bid = self.bids[0]
        best_ask = self.asks[0]
        if -best_bid[0] >= best_ask[0]:
            executed_price = best_ask[0]
            if best_bid[1] == best_ask[1]:
                executed_quantity = best_bid[1]
                heapq.heappop(self.bids)
                heapq.heappop(self.asks)
            elif best_bid[1] > best_ask[1]:
                executed_quantity = best_ask[1]
                heapq.heappop(self.bids)
                heapq.heappush(self.bids, (-best_bid[0], (best_bid[1] - executed_quantity)))
                heapq.heappop(self.asks)
            else:
                executed_quantity = best_bid[1]
                heapq.heappop(self.asks)
                heapq.heappush(self.asks, (best_ask[0], (best_ask[1] - executed_quantity)))
                heapq.heappop(self.bids)
            return (executed_price, executed_quantity)
        else:
            return None

    
a = OrderBook()
a.add_order("buy", 35, 4000)
a.add_order("buy", 37, 8000)
a.add_order("buy", 38.0, 3000)
a.add_order("sell", 38, 4000)
a.add_order("sell", 37.5, 4000)
print(a.best_bid())
print(a.best_ask())
print(a.match_orders())
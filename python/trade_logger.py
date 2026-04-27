class TradeLogger:
    def __init__(self):
        self.trades = {}       # instrument: (total_quantity, current VWAP)
        self.heap = []         # max heap of (total_quantity, instrument)

    def record_trade(self, instrument, quantity, price):
        if instrument not in self.trades:
            self.trades[instrument] = (quantity, price)
        else:
            old_quantity, old_price = self.trades[instrument]
            new_quantity = old_quantity + quantity
            new_price = ((old_price * old_quantity) + (price * quantity))/new_quantity
            self.trades[instrument] = (new_quantity, new_price)
    
    def total_volume(self, instrument):
        if instrument not in self.trades:
            return 0
        return self.trades[instrument][0]

    def average_price(self, instrument):
        if instrument not in self.trades:
            return 0
        return self.trades[instrument][1]
    
logger = TradeLogger()
logger.record_trade("AAPL", 100, 150.0)
logger.record_trade("AAPL", 200, 152.0)
print(logger.total_volume("AAPL"))
print(logger.average_price("AAPL"))
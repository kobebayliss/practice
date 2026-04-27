import heapq

def binary_search(array, target):
    left = 0
    right = len(array)
    while left < right:
        mid = (left + right) // 2
        if array[mid][0] < target:
            left = mid + 1
        elif array[mid][0] > target:
            right = mid
        else:
            right = mid
            left = right
    return right

class RiskMonitor:
    def __init__(self):
        self.pnl = {}                # trader_id: current pnl
        self.trader_events = {}      # trader_id: array of (timestamp, pnl, instrument_id)
        self.current_time = 0        # global most recent timestamp

    def add_event(self, instrument_id, trader_id, timestamp, pnl_delta):
        if timestamp > self.current_time:
            self.current_time = timestamp

        if trader_id not in self.pnl:
            self.pnl[trader_id] = 0
        self.pnl[trader_id] += pnl_delta

        events = self.trader_events.setdefault(trader_id, [])

        if not events or timestamp >= events[-1][0]:
            entry = (timestamp, self.pnl[trader_id], instrument_id)
            events.append(entry)
        else:
            idx = binary_search(events, timestamp)
            if idx == 0:
                pnl_before = 0
            else:
                pnl_before = self.trader_events[trader_id][idx - 1][1]
            entry = (timestamp, pnl_before + pnl_delta, instrument_id)
            events.insert(idx, entry)
            for i in range(idx + 1, len(events)):
                time, pnl, instr = self.trader_events[trader_id][i]
                self.trader_events[trader_id][i] = (time, pnl + pnl_delta, instr)
        return True

    def get_top_k_traders(self, k, window_seconds) -> List[str]:
        heap = []
        window_start = self.current_time - window_seconds

        for trader in self.trader_events:
            idx = binary_search(self.trader_events[trader], window_start)
            events = self.trader_events[trader]

            if idx == 0:
                window_pnl = self.pnl[trader]
            elif idx == len(self.trader_events[trader]):
                window_pnl = 0
            else:
                window_pnl = events[-1][1] - events[idx - 1][1]

            if len(heap) < k:
                heapq.heappush(heap, (window_pnl, trader))
            else:
                if heap[0][0] < window_pnl:
                    heapq.heappop(heap)
                    heapq.heappush(heap, (window_pnl, trader))

        result = [str(x[1]) for x in heap]
        return result
    
rsk = RiskMonitor()
print(rsk.add_event("AAPL", 1, 10, 300))
print(rsk.add_event("GOOG", 2, 12, 150))
print(rsk.add_event("MSFT", 3, 14, -200))
print(rsk.add_event("TSLA", 4, 16, 400))
print(rsk.add_event("AMZN", 5, 18, 250))

print(rsk.add_event("AAPL", 1, 20, 100))
print(rsk.add_event("GOOG", 2, 22, -50))
print(rsk.add_event("MSFT", 3, 24, 300))
print(rsk.add_event("TSLA", 4, 26, -150))
print(rsk.add_event("AMZN", 5, 28, 200))

print(rsk.add_event("AAPL", 1, 30, -200))
print(rsk.add_event("GOOG", 2, 32, 500))
print(rsk.add_event("MSFT", 3, 34, -100))
print(rsk.add_event("TSLA", 4, 36, 250))
print(rsk.add_event("AMZN", 5, 38, -300))

print(rsk.add_event("AAPL", 1, 40, 500))
print(rsk.add_event("GOOG", 2, 42, 100))
print(rsk.add_event("MSFT", 3, 44, 200))
print(rsk.add_event("TSLA", 4, 46, -50))
print(rsk.add_event("AMZN", 5, 48, 350))

print(rsk.add_event("AAPL", 1, 60, 300))
print(rsk.add_event("GOOG", 2, 62, -200))
print(rsk.add_event("MSFT", 3, 64, 400))
print(rsk.add_event("TSLA", 4, 66, 150))
print(rsk.add_event("AMZN", 5, 68, -100))

# 🔥 Edge cases: out-of-order timestamps (per trader)
print(rsk.add_event("AAPL", 1, 50, 800))   # out of order
print(rsk.add_event("GOOG", 2, 55, 250))   # out of order
print(rsk.add_event("MSFT", 3, 33, -150))  # out of order

print(rsk.add_event("TSLA", 4, 70, 300))
print(rsk.add_event("AMZN", 5, 72, 100))
print(rsk.get_top_k_traders(3, 12))
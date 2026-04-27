from sortedcontainers import SortedList

class riskTracker:
    def __init__(self):
        self.bst = SortedList()
        self.dic = {}

    def update(self, instrument_id, pnl):
        # Time: O(log n) for new and existing
        # Space: O(1)
        if instrument_id not in self.dic:
            self.bst.add((pnl, instrument_id))
        else:
            self.bst.discard((self.dic[instrument_id], instrument_id))
            self.bst.add((pnl, instrument_id))
        self.dic[instrument_id] = pnl

    def remove(self, instrument_id):
        # Time: O(log n)
        # Space: O(1)
        if instrument_id not in self.dic:
            return False
        self.bst.discard((self.dic[instrument_id], instrument_id))
        del self.dic[instrument_id]
        return True
    
    def get_worst(self, k):
        # Time: O(k + log n)
        # Space: O(k)
        if len(self.bst) >= k:
            return list(self.bst.islice(0, k))
        else:
            return list(self.bst)

    def get_worst_in_range(self, lo_pnl, hi_pnl, k):
        # Time: O(p + log n) where p is instruments > lo_pnl and < hi_pnl
        # Space: O(p)
        instruments_in_range = list(self.bst.irange((lo_pnl, chr(255)), (hi_pnl, "")))
        return instruments_in_range[:k]

rt = riskTracker()
rt.update("AAPL", 500.0)
rt.update("MSFT", 800.0)
rt.update("NVDA", 350.0)
rt.update("META", 680.0)
rt.update("META", 480.0)
print(rt.get_worst(2))
print(rt.get_worst_in_range(480.0, 1000.0, 2))
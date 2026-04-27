import threading
import heapq

class TradeEvent:
    def __init__(self, account_id, instrument_id, quantity, timestamp):
        self.account_id = account_id
        self.instrument_id = instrument_id
        self.quantity = quantity
        self.timestamp = timestamp

class PositionTracker:
    def __init__(self, num_shards=10, num_instruments=1000):
        self.num_shards = num_shards
        self.shards = [{} for _ in range(num_shards)]      # account_id: {instrument_id: held quantity}
        self.locks = [threading.Lock() for _ in range(num_shards)]
        self.instruments = {}          # instrument_id: {accounts}
        self.num_instruments = num_instruments
        self.rev_locks = [threading.Lock() for _ in range(num_instruments)]

    def get_shard(self, account_id):
        return hash(account_id) % self.num_shards

    def get_rev_lock(self, instrument_id):
        return self.rev_locks[hash(instrument_id) % self.num_instruments]

    def process(self, event: TradeEvent) -> None:
        shard_id = self.get_shard(event.account_id)
        rev_lock = self.get_rev_lock(event.instrument_id)
        with self.locks[shard_id]:
            positions = self.shards[shard_id]
            if event.account_id not in positions:
                positions[event.account_id] = {}
            if event.instrument_id not in positions[event.account_id]:
                positions[event.account_id][event.instrument_id] = 0
            final_pnl = positions[event.account_id][event.instrument_id] + event.quantity
            positions[event.account_id][event.instrument_id] = final_pnl
        with rev_lock:
            if event.instrument_id not in self.instruments:
                self.instruments[event.instrument_id] = set()
            if final_pnl != 0:
                self.instruments[event.instrument_id].add(event.account_id)
            else:
                self.instruments[event.instrument_id].discard(event.account_id)


    def get_net_position(self, account_id: str, instrument_id: str) -> int:
        shard_id = self.get_shard(account_id)
        with self.locks[shard_id]:
            positions = self.shards[shard_id]
            if account_id in positions and instrument_id in positions[account_id]:
                return positions[account_id][instrument_id]
            return 0

    def get_top_k_accounts(self, instrument_id: str, k: int):
        rev_lock = self.get_rev_lock(instrument_id)
        with rev_lock:
            accounts = list(self.instruments.get(instrument_id, []))

        heap = []    # (pnl, account id)
        for account in accounts:
            shard_id = self.get_shard(account)
            with self.locks[shard_id]:
                pnl = abs(self.shards[shard_id][account][instrument_id])
                if len(heap) < k:
                    heapq.heappush(heap, (pnl, account))
                elif pnl > heap[0][0]:
                    heapq.heappop(heap)
                    heapq.heappush(heap, (pnl, account))
        
        return [x[1] for x in heap]



        
pt = PositionTracker()

trade = TradeEvent("Joe", 1, 100, 1)
t1 = threading.Thread(target=pt.process, args=(trade,))

result = []
def read():
    result.append(pt.get_net_position("Joe", 1))

t2 = threading.Thread(target=read)

t1.start()
t2.start()

t1.join()
t2.join()

print(result)  # might be [0] or [100] depending on timing
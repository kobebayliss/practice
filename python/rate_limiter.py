from collections import deque

class RateLimiter:
    def __init__(self, limit, window):
        self.limit = limit
        self.window = window
        self.requests = {}  # user_id: queue of timestamps

    def allow_request(self, user_id, timestamp):
        if user_id not in self.requests:
            self.requests[user_id] = deque()

        while self.requests[user_id] and timestamp - self.requests[user_id][0] > self.window:
            self.requests[user_id].popleft()

        if len(self.requests[user_id]) < self.limit:
            self.requests[user_id].append(timestamp)
            return True

        return False

    def remaining_requests(self, user_id, timestamp):
        if user_id not in self.requests:
            return self.limit
        while self.requests[user_id] and timestamp - self.requests[user_id][0] > self.window:
            self.requests[user_id].popleft()

        return self.limit - len(self.requests[user_id])
    
rate = RateLimiter(3, 4)
rate.allow_request(1, 2)
rate.allow_request(1, 3)
rate.allow_request(1, 8)
rate.allow_request(1, 9)
def optimise_schedule(bookings, slew_time=0):
    n = len(bookings)
    bookings.sort(key=lambda x: x.end)

    # find the booking which finishes last before booking[i] starts
    def most_recent_compatible(i):
        goal = bookings[i].start - slew_time
        left = 0
        right = i - 1
        ans = -1

        # binary search to find in O(log n)
        while right >= left:
            mid = (left + right) // 2
            if bookings[mid].end <= goal:
                # store candidate and continue looking
                ans = mid
                left = mid + 1
            else:
                right = mid - 1
        return ans
    
    # stores maximum revenue using the first i bookings
    max_revenue = [0] * (n + 1)
    schedule = [[] for _ in range(n + 1)]
    for i in range(1, n + 1):
        curr = i - 1
        prev = most_recent_compatible(curr)
        value = bookings[curr].total_price
        if prev != -1:
            value += max_revenue[prev + 1]
        
        if value > max_revenue[curr]:
            max_revenue[i] = value
            schedule[i] = schedule[prev + 1] + [bookings[curr]]
            print(schedule)
        else:
            max_revenue[i] = max_revenue[curr]
            schedule[i] = schedule[curr]

    # return most optimised schedule for revenue
    return (schedule[-1], max_revenue[-1])

class Booking:
    def __init__(self, id, start, end, price):
        self.id = id
        self.start = start
        self.end = end
        self.total_price = price

    def __repr__(self):
        return f"{self.id}: {self.start} - {self.end}, ${self.total_price})"

bookings = [
    Booking("A", 0, 10, 100),
    Booking("B", 5, 15, 120),
    Booking("C", 12, 20, 150),
    Booking("D", 18, 25, 200),
    Booking("E", 22, 30, 180),
    Booking("F", 28, 35, 90),
    Booking("G", 30, 40, 250),
]

result = optimise_schedule(bookings, slew_time=2)
print(result)
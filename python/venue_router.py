from collections import deque
import heapq

class VenueRouter:
    def __init__(self):
        self.connections = {}

    def add_venue(self, venue):
        if venue not in self.connections:
            self.connections[venue] = []

    def add_connection(self, from_venue, to_venue, latency):
        if from_venue not in self.connections or to_venue not in self.connections:
            return "Add both venues first"
        self.connections[from_venue].append((to_venue, latency))
        self.connections[to_venue].append((from_venue, latency))

    def find_route(self, start, end):
        """Find the route with the fewest hops between two venues."""
        visited = set()
        queue = deque([(start, [start])])
        # [(B, [A, B])]
        while queue:
            venue, path = queue.popleft()

            if venue == end:
                return path

            if venue in visited:
                continue

            visited.add(venue)

            for neighbor, latency in self.connections.get(venue, []):
                if neighbor not in visited:
                    queue.append((neighbor, path + [neighbor]))

        return None

    def find_lowest_latency_route(self, start, end):
        heap = [(0, start)]    # contains (total latency, node) | min heap
        predecesssor = {start: (0, None)}      # node: (best latency, predecessor)
        visited = set()
        while heap:
            total_latency, node = heapq.heappop(heap)
            if node == end:
                path = []
                curr = (total_latency, node)
                path.append(curr[1])
                while curr[1] in predecesssor and predecesssor[curr[1]][1] is not None:
                    path.append(predecesssor[curr[1]][1])
                    curr = predecesssor[curr[1]]
                path.reverse()
                return (path, total_latency)
            if node in visited:
                continue
            visited.add(node)
            for neighbour, latency in self.connections.get(node, []):
                if neighbour not in visited:
                    if neighbour not in predecesssor or total_latency + latency < predecesssor[neighbour][0]:
                        predecesssor[neighbour] = (total_latency + latency, node)
                    heapq.heappush(heap, (total_latency + latency, neighbour))

        return None



ven = VenueRouter()
ven.add_venue("A")
ven.add_venue("B")
ven.add_venue("C")
ven.add_venue("D")
ven.add_venue("E")
ven.add_connection("A", "B", 40)
ven.add_connection("A", "D", 50)
ven.add_connection("D", "B", 90)
ven.add_connection("E", "D", 10)
ven.add_connection("C", "E", 30)
print(ven.find_route("A", "C"))
print(ven.find_lowest_latency_route("A", "A"))
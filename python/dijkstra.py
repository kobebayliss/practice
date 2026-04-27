import heapq

class SignalRouter:
    def __init__(self, graph, penalty):
        self.graph = graph         # A: [(B, 10, 0.9), (C, 20, 0.8)] | B: [(C, 5, 0.9)]
        self.penalty = penalty
    
    def best_path(self, start, end):
        heap = [(0, start, 1, 0)]     # cost, node, rel so far, total latency
        visited = set()
        best_cost = {}

        while heap:
            cost, node, rel, lat = heapq.heappop(heap)
            if node == end:
                result = []
                curr = end
                while curr is not None:
                    result.append(curr)
                    temp = best_cost.get(curr, (None, None))
                    curr = temp[1]
                return result[::-1]
            if node in visited:
                continue
            visited.add(node)

            for neighbour in self.graph.get(node, []):
                if neighbour[0] not in visited:
                    new_rel = rel * neighbour[2]
                    new_cost = (lat + neighbour[1]) + (self.penalty * (1 - new_rel))
                    if neighbour[0] not in best_cost or best_cost[neighbour[0]][0] > new_cost:
                        best_cost[neighbour[0]] = (new_cost, node)       # best cost, predecessor
                        heapq.heappush(heap, (new_cost, neighbour[0], new_rel, lat + neighbour[1]))

        return []

sr = SignalRouter({"A": [("B", 10, 0.9), ("C", 20, 0.8)], "B": [("C", 5, 0.9)]}, 1)
print(sr.best_path("A", "D"))

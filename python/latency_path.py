import heapq

def lowest_latency_path(graph, start, end):
    heap = [(0, start)]
    predecessor = {}
    visited = set()

    while heap:
        total_latency, node = heapq.heappop(heap)

        if node == end:
            break
        if node in visited:
            continue
        visited.add(node)

        for neighbour, latency in graph[node]:
            if neighbour not in visited:
                predecessor[neighbour] = node
                heapq.heappush(heap, (total_latency + latency, neighbour))
    
    curr = node
    result = []
    result.append(curr)
    while curr in predecessor:
        result.append(predecessor[curr])
        curr = predecessor[curr]
    return result[::-1]

graph = {
    "A": [("B", 1), ("C", 2)],
    "B": [("C", 10), ("D", 100)],
    "C": [("D", 1)],
    "D": []
}

print(lowest_latency_path(graph, "A", "D"))  # Should print 3
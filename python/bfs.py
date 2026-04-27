from collections import deque

def bfs(graph, start, end):
    visited = set([start])
    parent = {start: None}
    queue = deque([(0, start)])

    while queue:
        dist, node = queue.popleft()
        if node == end:
            path = []
            curr = end
            while curr is not None:
                path.append(curr)
                curr = parent[curr]
            path.reverse()
            return (dist, path)

        for neighbour in graph[node]:
            if neighbour not in visited:
                visited.add(neighbour)
                parent[neighbour] = node
                queue.append((dist + 1, neighbour))

    return -1

graph = {
    "A": ["B", "C"],
    "B": ["D"],
    "C": ["D"],
    "D": []
}

print(bfs(graph, "A", "D"))
from collections import deque

def get_reachable_users(graph, start):
    visited = set([start])
    queue = deque([start])
    result = []

    while queue:
        node = queue.popleft()
        result.append(node)

        for neighbour in graph.get(node, []):
            if neighbour not in visited:
                queue.append(neighbour)
                visited.add(neighbour)
    
    return result

graph = {
    "A": ["B", "C"],
    "B": ["D"],
    "C": ["E"],
    "D": [],
    "E": []
}
print(get_reachable_users(graph, "A"))
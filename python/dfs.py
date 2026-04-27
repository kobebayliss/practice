def has_cycle(graph):
    visited = set()
    rec_stack = set()

    def dfs(start):
        visited.add(start)
        rec_stack.add(start)

        for neighbour in graph[start]:
            if neighbour not in visited:
                if dfs(neighbour):
                    return True
            elif neighbour in rec_stack:
                return True
        
        rec_stack.remove(start)
        return False
        


    for node in graph:
        if node not in visited:
            if dfs(node):
                return True
    
    return False

graph = {
    "A": ["B", "C"],
    "B": ["C"],
    "C": ["D"],
    "D": []
}
print(has_cycle(graph))
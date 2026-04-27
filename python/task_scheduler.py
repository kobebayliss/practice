import heapq
from collections import deque

def least_time(tasks, n):
    freq = {}
    for task in tasks:
        if task not in freq:
            freq[task] = 1
        else:
            freq[task] += 1
    tasks.sort(key=lambda x: freq[x], reverse=True)
    queue = deque(tasks)
    time = 0
    last_executed = {}  # task: last time it was run
    heap = []           # (time at which task can be ran again, task)
    result = []
    
    while queue or heap:
        if heap and time == heap[0][0]:
            task = heapq.heappop(heap)
            result.append(task[1])
            time += 1
        elif queue and queue[0] not in last_executed:
            last_executed[queue[0]] = time
            result.append(queue.popleft())
            time += 1
        else:
            if queue:
                task = queue[0]
                heapq.heappush(heap, (last_executed[task] + n + 1, queue.popleft()))
                last_executed[task] = last_executed[task] + n + 1
            else:
                result.append("IDLE")
                time += 1
        
    
    return result

print(least_time(["A","A","A","B","B","B","C","D"], 2))
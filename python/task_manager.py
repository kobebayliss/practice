import heapq

class TaskManager:
    def __init__(self):
        self.tasks = {} # task_id: task
        self.heap = []  # (priority, task_id)
        self.position_map = {} # task_id: index in heap

    def add_task(self, task_id, priority, description):
        # O(log(n))
        task_obj = {
            "id": task_id,
            "priority": priority,
            "description": description
        }
        self.tasks[task_id] = task_obj
        heapq.heappush(self.heap, (priority, task_id))
        self.position_map[task_id] = len(self.heap) - 1
    
    def clean_heap(self):
        # O(1) amortised
        while self.heap:
            prio, task_id = self.heap[0]
            if task_id not in self.tasks:
                heapq.heappop(self.heap)
            elif self.tasks[task_id]["priority"] != prio:
                heapq.heappop(self.heap)
            else:
                break

    def get_highest_priority_task(self):
        # O(1)
        self.clean_heap()
        if not self.heap:
            return None
        return self.tasks[self.heap[0][1]]

    def remove_task(self, task_id):
        # O(n) worst
        if not self.tasks:
            return None
        if task_id not in self.tasks:
            return False
        
        del self.tasks[task_id]
        return True
    
    def update_task(self, task_id, new_priority=None, new_description=None):
        if not self.tasks:
            return None
        if task_id not in self.tasks:
            return False
        
        task = self.tasks[task_id]
        if new_priority is not None:
            task["priority"] = new_priority
            heapq.heappush(self.heap, (new_priority, task_id))
        if new_description is not None:
            task["description"] = new_description
        return True
    
    def get_top_k_tasks(self, k):
        self.clean_heap()
        result = []
        temp = []
        while self.heap and len(result) < k:
            prio, task_id = heapq.heappop(self.heap)
            if task_id in self.tasks and self.tasks[task_id]["priority"] == prio:
                result.append(self.tasks[task_id])
                temp.append((prio, task_id))
        for task in temp:
            heapq.heappush(self.heap, task)
        return result


task = TaskManager()
task.add_task(1, 4, "Hi")
task.add_task(2, 1, "Hi")
task.add_task(3, 5, "Hi")
task.add_task(4, 2, "Hi")
print(task.get_highest_priority_task())
task.update_task(2, 3, "BYEE")
print(task.get_top_k_tasks(2))
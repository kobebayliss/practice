import heapq

class TaskScheduler:
    def __init__(self):
        self.tasks = []  # max heap of (priority, task_name)
        self.priorities = {}
        self.dependencies = {}  # hasmap of task_name: set of dependencies

    def add_task(self, task_name, priority, dependencies=[]):
        if dependencies:
            self.dependencies[task_name] = set(dependencies)
        else:
            heapq.heappush(self.tasks, (-priority, task_name))
        self.priorities[task_name] = priority

    def get_next_task(self):
        if not self.tasks:
            return None
        copy = {}
        # Picks task with highest priority
        priority, task_name = heapq.heappop(self.tasks)
        for task in self.dependencies:

            self.dependencies[task].discard(task_name)
            if not self.dependencies[task]:
                heapq.heappush(self.tasks, (-self.priorities[task], task))
            else:
                copy[task] = self.dependencies[task]
        self.dependencies = copy
        return (task_name, -priority)
    
sched = TaskScheduler()
sched.add_task("A", 3)
sched.add_task("B", 5, ["A"])
sched.add_task("C", 6, ["A"])
sched.add_task("D", 10, ["C"])
print(sched.get_next_task())
print(sched.get_next_task())
print(sched.get_next_task())
print(sched.get_next_task())
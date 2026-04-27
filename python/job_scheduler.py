class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None


class Scheduler:
    def __init__(self):
        self.workers = {}     # worker_id: (skill, busy, BST node)
        self.jobs = {}        # job_id -> worker_id
        self.head = None      # head of BST

    def add_worker(self, worker_id, skill):
        if worker_id not in self.workers:
            worker_node = Node((skill, worker_id))
            self.workers[worker_id] = (skill, False, worker_node)
            self.add_to_bst(worker_node)

    def add_to_bst(self, worker_node):
        if self.head:
            curr = self.head
            while curr is not None:
                prev = curr
                if worker_node.val >= curr.val:
                    curr = curr.right
                else:
                    curr = curr.left
            if worker_node.val >= prev.val:
                prev.right = worker_node
            else:
                prev.left = worker_node
            worker_node.parent = prev
        else:
            self.head = worker_node

    def delete(self, node):
        if not node.left and not node.right:
            self.replace(node, None)
        elif not node.left:
            self.replace(node, node.right)
        elif not node.right:
            self.replace(node, node.left)
        else:
            curr = node.right
            while curr.left:
                curr = curr.left
            node.val = curr.val
            self.delete(curr)

    def replace(self, old_node, new_node):
        if old_node.parent is None:
            self.head = new_node
        elif old_node == old_node.parent.left:
            old_node.parent.left = new_node
        else:
            old_node.parent.right = new_node
        if new_node:
            new_node.parent = old_node.parent

    
    def assign_job(self, job_id, required_skill):
        if not self.head:
            return -1
        curr = self.head
        best = None
        while curr:
            if curr.val[0] >= required_skill:
                best = curr
                curr = curr.left
            else:
                curr = curr.right
        if best is None:
            return -1
        chosen_worker = best.val
        self.delete(best)
        self.jobs[job_id] = chosen_worker[1]
        self.workers[chosen_worker[1]] = (chosen_worker[0], True, best)
        return chosen_worker[1]

    def complete_job(self, job_id):
        if job_id not in self.jobs:
            return False

        worker_id = self.jobs[job_id]
        skill, busy, bst_node = self.workers[worker_id]
        del self.jobs[job_id]
        self.workers[worker_id] = (skill, False, bst_node)
        bst_node.parent = None
        bst_node.left = None
        bst_node.right = None
        self.add_to_bst(bst_node)
        print(self.workers)
        return True

    def update_worker(self, worker_id, new_skill):
        if worker_id in self.workers:
            skill, busy, node = self.workers[worker_id]
            if not busy:
                self.workers[worker_id] = (new_skill, busy, node)
                node.val = (new_skill, worker_id)
                self.delete(node)
                node.left = node.right = node.parent = None
                self.add_to_bst(node)
                return True
        return False
    
    def get_top_k_available(self, k):
        result = []
        curr = self.head
        while curr.right:
            curr = curr.right
        while curr.parent:
            result.append(curr.val[1])
            if curr.left:
                result.append(curr.left.val[1])
            curr = curr.parent
        return result
    
sch = Scheduler()
sch.add_worker(1, 5)
sch.add_worker(2, 10)
sch.add_worker(3, 6)
sch.add_worker(4, 30)
sch.add_worker(5, 4)
sch.add_worker(6, 9)
print(sch.assign_job(1, 5))
print(sch.assign_job(2, 11))
print(sch.complete_job(1))
print(sch.get_top_k_available(3))

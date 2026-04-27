import heapq

class Leaderboard:
    def __init__(self):
        self.players = {}     # player_id: (player, heap_index)
        self.heap = []        # (score, player_id)

    def sift_up_max(self, heap, index):
        curr = index
        while curr > 0:
            parent = curr // 2
            if heap[curr] > heap[parent]:
                curr_id = heap[curr][1]
                parent_id = heap[parent][1]
                self.players[curr_id] = (self.players[curr_id][0], parent)
                self.players[parent_id] = (self.players[parent_id][0], curr)
                heap[curr], heap[parent] = heap[parent], heap[curr]
            else:
                return None
            curr = parent

    def add_player(self, player_id, score, level):
        # O(log n)
        self.players[player_id] = ({
            "player_id": player_id,
            "score": score,
            "level": level
        }, len(self.heap))
        self.heap.append((score, player_id))
        self.sift_up_max(self.heap, len(self.heap)-1)

    def get_top_player(self):
        # O(1)
        if not self.players:
            return None
        return self.players[self.heap[0][1]][0]

    def remove_player(self, player_id):
        # O(log n)
        if player_id not in self.players:
            return False
        heap_index = self.players[player_id][1]
        del self.players[player_id]
        self.heap[heap_index], self.heap[-1] = self.heap[-1], self.heap[heap_index]
        self.heap.pop()
        heapq.heapify_max(self.heap)
        return True

    def update_player(self, player_id, new_score=None, new_level=None):
        if player_id not in self.players:
            return False
        heap_index = self.players[player_id][1]
        if new_score is not None:
            self.heap[heap_index] = (new_score, player_id)
            self.players[player_id][0]["score"] = new_score
        if new_level is not None:
            self.players[player_id][0]["level"] = new_level
        return True
    
    def get_top_k_players(self, k):
        if k > len(self.heap):
            return None

        largest_tuple_form = heapq.nlargest(k, self.heap)
        return [self.players[player[1]][0] for player in largest_tuple_form]


ldb = Leaderboard()

ldb.add_player(1, 133, 12)
ldb.add_player(2, 113, 11)
ldb.add_player(3, 200, 19)
ldb.add_player(4, 87, 4)
print(ldb.get_top_player())
ldb.remove_player(3)
print(ldb.get_top_player())
ldb
print(ldb.get_top_k_players(3))
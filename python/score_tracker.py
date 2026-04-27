import heapq

class ScoreTracker:
    def __init__(self):
        self.scores = []
        self.max_score = float('-inf')
        self.raw_scores = []
        heapq.heapify(self.raw_scores)

    def add_score(self, user_id, score):
        self.scores.append((user_id, score))
        heapq.heappush(self.raw_scores, -score)
        if score > self.max_score:
            self.max_score = score

    def get_top_score(self):
        if not self.scores:
            return 0
        return self.max_score

    def get_average_score(self):
        if not self.scores:
            return 0
        total = 0
        for user_id, score in self.scores:
            total += score
        return total / len(self.scores)

    
score = ScoreTracker()
print(score.get_average_score())
score.add_score(1, 10)
score.add_score(2, 5)
score.add_score(3, 3)
score.add_score(3, 9)
print(score.get_top_score())
print(score.get_average_score())
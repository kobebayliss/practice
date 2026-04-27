import heapq

class Twitter:

    def __init__(self):
        self.tweets = {}      # user_id: [(1, id), (4, id)]
        self.following = {}   # user_id: [following list]
        self.timestamp = 1

    def postTweet(self, userId: int, tweetId: int) -> None:
        if userId in self.tweets:
            self.tweets[userId].append((self.timestamp, tweetId))
        else:
            self.tweets[userId] = [(self.timestamp, tweetId)]
        self.timestamp += 1

    def getNewsFeed(self, userId: int) -> List[int]:
        heap = []
        users = self.following.get(userId, []).copy()
        users.append(userId)
        news_feed = []

        for user in users:
            if user in self.tweets and self.tweets[user]:
                idx = len(self.tweets[user]) - 1
                tweet_id = self.tweets[user][idx][1]
                heapq.heappush_max(heap, (self.tweets[user][idx][0], tweet_id, user, idx))
        while heap and len(news_feed) < 10:
            time, tweet_id, user_id, idx = heapq.heappop_max(heap)
            news_feed.append(tweet_id)

            if idx > 0:
                heapq.heappush_max(heap, (self.tweets[user_id][idx - 1][0], self.tweets[user_id][idx - 1][1], user_id, (idx - 1)))

        return news_feed

    def follow(self, followerId: int, followeeId: int) -> None:
        if followerId in self.following:
            self.following[followerId].append(followeeId)
        else:
            self.following[followerId] = [followeeId]

    def unfollow(self, followerId: int, followeeId: int) -> None:
        if followeeId in self.following[followerId]:
            self.following[followerId].remove(followeeId)

obj = Twitter()
obj.postTweet(1, 78)
obj.postTweet(2, 89)
obj.postTweet(3, 65)
obj.postTweet(1, 84)
obj.postTweet(3, 81)
obj.follow(1, 3)
print(obj.getNewsFeed(1))
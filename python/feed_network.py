class FeedNetwork:
    def __init__(self):
        self.subscriptions = {}  # feed: list of feeds it subscribes to

    def add_feed(self, feed):
        if feed not in self.subscriptions:
            self.subscriptions[feed] = []

    def add_subscription(self, source, subscriber):
        """subscriber receives data from source"""
        if source not in self.subscriptions:
            return
        self.subscriptions[source].append(subscriber)

    def get_impacted_feeds(self, failed_feed):
        """
        Return all feeds that are impacted if failed_feed goes down.
        A feed is impacted if it subscribes to the failed feed, directly or transitively.
        """
        impacted = set()
        stack = [failed_feed]

        while stack:
            current = stack.pop()
            for subscriber in self.subscriptions[current]:
                if subscriber not in impacted:
                    impacted.add(subscriber)
                    stack.append(subscriber)

        return impacted

    def has_cycle(self):
        """Detect if there is any circular subscription in the network."""
        visited = set()   # [A, B, C]
        rec_stack = set()

        def dfs(feed):
            rec_stack.add(feed)
            visited.add(feed)
            for source in self.subscriptions.get(feed, []):
                if source not in visited:
                    if dfs(source):
                        return True
                elif source in rec_stack:
                    return True
            rec_stack.remove(feed)
            return False

        for feed in self.subscriptions:
            if feed not in visited:
                if dfs(feed):
                    return True

        return False
    
    def get_feed_depths(self, source):
        """
        Return a dict mapping each feed to its shortest subscription 
        depth from source. Depth 0 is the source itself.
        """
        pass
    

feed = FeedNetwork()
feed.add_feed("A")
feed.add_feed("B")
feed.add_feed("C")
feed.add_feed("D")
feed.add_subscription("A", "B")
feed.add_subscription("B", "C")
feed.add_subscription("D", "C")
print(feed.get_impacted_feeds("A"))
print(feed.has_cycle())
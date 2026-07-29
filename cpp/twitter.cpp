#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Twitter {
    unordered_map<int, vector<int>> following;
    unordered_map<int, vector<pair<size_t, int>>> tweets;
    size_t timestamp;
public:
    Twitter() {
    	timestamp = 0;
    }

    void postTweet(int userId, int tweetId) {
        if (tweets.find(userId) == tweets.end()) {
            tweets.insert({userId, {}});
        }
	pair<size_t, int> tweet_data = {timestamp++, tweetId};
        tweets[userId].push_back(tweet_data);
    }

    vector<int> getNewsFeed(int userId) {
		vector<int> feed;
		priority_queue<pair<size_t, int>> pq;
		vector<int> following_list = following[userId];
		for (int user_id : following_list) {
			vector<pair<size_t, int>> user_tweets = tweets[user_id];
			for (int i = 0; i < user_tweets.size(); i++) {
				pq.push(user_tweets[i]);
			}
		}
		vector<pair<size_t, int>> own_tweets = tweets[userId];
		for (int i = 0; i < own_tweets.size(); i++) {
			pq.push(own_tweets[i]);
		}
		for (int i = 0; i < 10 && !pq.empty(); i++) {
			pair<size_t, int> topper = pq.top();
			pq.pop();
			feed.push_back(topper.second);
		}
		return feed;
    }

    void follow(int followerId, int followeeId) {
    	auto& f = following[followerId];
	if (find(f.begin(), f.end(), followeeId) == f.end()) {
		f.push_back(followeeId);
	}
    }

	void unfollow(int followerId, int followeeId) {
	    auto it = following.find(followerId);
	    if (it == following.end()) return;
	    auto& f = it->second;
	    auto pos = find(f.begin(), f.end(), followeeId);
	    if (pos != f.end()) f.erase(pos);
	    if (f.empty()) following.erase(it);
	}
};

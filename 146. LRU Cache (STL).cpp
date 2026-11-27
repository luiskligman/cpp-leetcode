class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        auto it = nodes_.find(key);
        if (it == nodes_.end()) {
            return -1;
        }

        l.splice(l.begin(), l, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = nodes_.find(key);
        if (it == nodes_.end()) {
            l.push_front({key, value});
            nodes_[key] = l.begin();
            if (l.size() > capacity_) {
                nodes_.erase(l.back().first);
                l.pop_back();
            }
        } else {
            auto it = nodes_[key];
            it->second = value;
            l.splice(l.begin(), l, it);
        }
    }

    int capacity_{};
    unordered_map<int, list<pair<int, int>>::iterator>
        nodes_; // <key, iterator>
    list<pair<int, int>> l{};
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

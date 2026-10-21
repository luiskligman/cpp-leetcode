struct Node {
    Node* prev;
    Node* next;
    int key;
    int value;
    Node(Node* p, Node* n, int k, int v) : prev(p), next(n), key(k), value(v) {}
    Node(int k, int v) : prev(nullptr), next(nullptr), key(k), value(v) {}
};

class LRUCache {
private:
    int capacity_;
    unordered_map<int, Node*> map_;
    Node* head;
    Node* tail;

public:
    LRUCache(int capacity) : capacity_(capacity), head(nullptr), tail(nullptr) {}
    
    int get(int key) {
        auto it = map_.find(key);
        if (it != map_.end()) {  // exists
            detachNode(it->second);
            replaceHead(it->second);
            return it->second->value;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        auto it = map_.find(key);
        if (it != map_.end()) {  // exists
            detachNode(it->second);
            replaceHead(it->second);
            it->second->value = value;
        } else {  // does not exist
            if (int(map_.size()) == capacity_) {
                deleteTail();
            }
            Node* n = new Node(key, value);
            replaceHead(n);
            map_[key] = n;
        }
    }

    void deleteTail() {
        Node* old = tail;
        detachNode(old);
        map_.erase(old->key);
        delete old;
    }

    void replaceHead(Node* n) {
        n->prev = nullptr;
        n->next = head;
        if (head) {
            head->prev = n;
        } else {
            tail = n;
        }
        head = n;
    }

    void detachNode(Node* n) {
        if (n->prev) {
            n->prev->next = n->next;
        } else {
            head = n->next;
        }

        if (n->next) {
            n->next->prev = n->prev;
        } else {
            tail = n->prev;
        }
        n->next = n->prev = nullptr;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

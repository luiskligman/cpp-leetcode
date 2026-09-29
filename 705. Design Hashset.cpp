#include <bits/stdc++.h>
using namespace std;

class MyHashSet {
    vector<bool> present;
public:
    MyHashSet() : present(1000001, false) {}
    
    void add(int key) {
        present[key] = true;
    }
    
    void remove(int key) {
        present[key] = false;
    }
    
    bool contains(int key) {
        return present[key];
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

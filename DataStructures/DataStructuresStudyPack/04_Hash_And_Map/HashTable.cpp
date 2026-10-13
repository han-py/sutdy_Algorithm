#include <cassert>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
class HashTableChaining {
public:
    explicit HashTableChaining(size_t n = 16) : b_(n) {}
    void insert(int k, int v) {
        auto& bucket = b_[k % b_.size()];
        for (auto& [key, val] : bucket) if (key == k) { val = v; return; }
        bucket.push_back({k, v});
    }
    bool find(int k, int& v) const {
        const auto& bucket = b_[k % b_.size()];
        for (auto& [key, val] : bucket) if (key == k) { v = val; return true; }
        return false;
    }
private:
    vector<list<pair<int,int>>> b_;
};
class HashTableLinearProbing {
public:
    explicit HashTableLinearProbing(size_t n = 16) : key_(n, EMPTY), val_(n, 0) {}
    void insert(int k, int v) {
        size_t idx = hash(k);
        while (key_[idx] != EMPTY && key_[idx] != k) idx = (idx + 1) % key_.size();
        key_[idx] = k; val_[idx] = v;
    }
    bool find(int k, int& v) const {
        size_t idx = hash(k), start = idx;
        while (key_[idx] != EMPTY) {
            if (key_[idx] == k) { v = val_[idx]; return true; }
            idx = (idx + 1) % key_.size();
            if (idx == start) break;
        }
        return false;
    }
private:
    static constexpr int EMPTY = -1;
    vector<int> key_, val_;
    size_t hash(int k) const { return (size_t)k % key_.size(); }
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    HashTableChaining h1;
    h1.insert(1, 10); h1.insert(17, 20);
    int v = 0;
    cout << "Chaining find = " << h1.find(17, v) << '\n';
    HashTableLinearProbing h2;
    h2.insert(2, 30);
    cout << "Linear probing find = " << h2.find(2, v) << '\n';
    assert(h2.find(2, v) && v == 30);
    return 0;
}

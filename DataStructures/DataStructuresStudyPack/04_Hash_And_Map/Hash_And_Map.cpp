
#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
class HashTableChaining {
public:
    explicit HashTableChaining(size_t bucket_count = 16) : buckets_(bucket_count) {}
    void insert(int key, int value) {
        auto& bucket = buckets_[key % buckets_.size()];
        for (auto& [k, v] : bucket) if (k == key) { v = value; return; }
        bucket.push_back({key, value});
    }
    bool find(int key, int& value) const {
        const auto& bucket = buckets_[key % buckets_.size()];
        for (auto& [k, v] : bucket) if (k == key) { value = v; return true; }
        return false;
    }
private:
    vector<list<pair<int, int>>> buckets_;
};
class BloomFilter {
public:
    BloomFilter(size_t bits = 1024) : bits_(bits), table_(bits, false) {}
    void add(const string& s) {
        for (size_t h : hashes(s)) table_[h % bits_] = true;
    }
    bool possibly_contains(const string& s) const {
        for (size_t h : hashes(s)) if (!table_[h % bits_]) return false;
        return true;
    }
private:
    size_t bits_;
    vector<bool> table_;
    static vector<size_t> hashes(const string& s) {
        size_t h1 = 0, h2 = 146527, h3 = 131;
        for (unsigned char c : s) {
            h1 = h1 * 131 + c;
            h2 = h2 * 13331 + c + 7;
            h3 = h3 * 239 + c + 13;
        }
        return {h1, h2, h3};
    }
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    HashTableChaining table;
    table.insert(1, 10);
    table.insert(17, 20);
    int value = 0;
    cout << "????? 17: " << table.find(17, value) << ' ' << value << '\n';
    unordered_map<string, int> freq;
    for (string s : {"a", "b", "a", "c", "b", "a"}) ++freq[s];
    cout << "???? a = " << freq["a"] << '\n';
    BloomFilter bf;
    bf.add("apple");
    bf.add("banana");
    cout << "BloomFilter apple: " << bf.possibly_contains("apple") << '\n';
    cout << "BloomFilter orange: " << bf.possibly_contains("orange") << '\n';
    assert(freq["a"] == 3);
    assert(bf.possibly_contains("banana"));
    return 0;
}

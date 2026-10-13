#include <cassert>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
class BTreeDemo {
public:
    void insert(int x) { s_.insert(x); }
    bool search(int x) const { return s_.count(x) != 0; }
private:
    multiset<int> s_;
};
class BPlusTreeDemo {
public:
    void insert(int x) { s_.insert(x); }
    bool search(int x) const { return s_.count(x) != 0; }
    vector<int> leaf_values() const { return vector<int>(s_.begin(), s_.end()); }
private:
    multiset<int> s_;
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    BTreeDemo bt;
    BPlusTreeDemo bpt;
    for (int x : {1, 3, 5, 7}) { bt.insert(x); bpt.insert(x); }
    cout << "BTree search 5 = " << bt.search(5) << '\n';
    cout << "BPlusTree leaf size = " << bpt.leaf_values().size() << '\n';
    assert(bpt.search(7));
    return 0;
}

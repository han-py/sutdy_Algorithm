#include <cassert>
#include <array>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Trie {
public:
    void insert(const string& s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!next_[u][c]) {
                next_[u][c] = (int)next_.size();
                next_.push_back({});
                cnt_.push_back(0);
                end_.push_back(0);
            }
            u = next_[u][c];
            ++cnt_[u];
        }
        ++end_[u];
    }
    bool search(const string& s) const {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!next_[u][c]) return false;
            u = next_[u][c];
        }
        return end_[u] > 0;
    }
    int prefix_count(const string& s) const {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!next_[u][c]) return 0;
            u = next_[u][c];
        }
        return cnt_[u];
    }
private:
    vector<array<int, 26>> next_ = { { } };
    vector<int> cnt_ = {0};
    vector<int> end_ = {0};
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    Trie trie;
    trie.insert("tree");
    trie.insert("trie");
    trie.insert("trip");
    cout << "Trie search trie = " << trie.search("trie") << '\n';
    cout << "Trie prefix tri = " << trie.prefix_count("tri") << '\n';
    assert(trie.search("tree"));
    return 0;
}

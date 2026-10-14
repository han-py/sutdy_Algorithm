#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
class SkipList {
public:
    SkipList() : gen_(random_device{}()) { head_ = new Node(INT_MIN, kMaxLevel); }
    bool search(int x) const {
        Node* cur = head_;
        for (int lvl = level_ - 1; lvl >= 0; --lvl) {
            while (cur->next[lvl] && cur->next[lvl]->val < x) cur = cur->next[lvl];
        }
        cur = cur->next[0];
        return cur && cur->val == x;
    }
    void insert(int x) {
        vector<Node*> up(kMaxLevel, nullptr);
        Node* cur = head_;
        for (int lvl = level_ - 1; lvl >= 0; --lvl) {
            while (cur->next[lvl] && cur->next[lvl]->val < x) cur = cur->next[lvl];
            up[lvl] = cur;
        }
        cur = cur->next[0];
        if (cur && cur->val == x) return;
        int lvl = random_level();
        if (lvl > level_) { for (int i = level_; i < lvl; ++i) up[i] = head_; level_ = lvl; }
        Node* node = new Node(x, lvl);
        for (int i = 0; i < lvl; ++i) { node->next[i] = up[i]->next[i]; up[i]->next[i] = node; }
    }
private:
    static constexpr int kMaxLevel = 16;
    struct Node { int val; vector<Node*> next; Node(int v, int level) : val(v), next(level, nullptr) {} };
    Node* head_;
    int level_ = 1;
    mt19937 gen_;
    int random_level() {
        int lvl = 1;
        uniform_int_distribution<int> dist(0, 1);
        while (lvl < kMaxLevel && dist(gen_)) ++lvl;
        return lvl;
    }
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    SkipList sk;
    sk.insert(10);
    sk.insert(5);
    sk.insert(20);
    cout << "SkipList search 10 = " << sk.search(10) << '\n';
    assert(sk.search(5));
    return 0;
}

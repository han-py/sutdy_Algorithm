
#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
class FenwickTree {
public:
    explicit FenwickTree(int n) : bit_(n + 1, 0) {}
    void add(int idx, long long delta) {
        for (int i = idx + 1; i < (int)bit_.size(); i += i & -i) bit_[i] += delta;
    }
    long long sum_prefix(int idx) const {
        long long res = 0;
        for (int i = idx + 1; i > 0; i -= i & -i) res += bit_[i];
        return res;
    }
    long long range_sum(int l, int r) const { return l > r ? 0 : sum_prefix(r) - (l ? sum_prefix(l - 1) : 0); }
private:
    vector<long long> bit_;
};
class SegmentTree {
public:
    explicit SegmentTree(vector<long long> a) : n_(a.size()), tree_(n_ * 4), lazy_(n_ * 4, 0) {
        build(1, 0, n_ - 1, a);
    }
    long long query(int l, int r) { return query(1, 0, n_ - 1, l, r); }
    void range_add(int l, int r, long long delta) { range_add(1, 0, n_ - 1, l, r, delta); }
private:
    int n_;
    vector<long long> tree_, lazy_;
    void build(int p, int l, int r, const vector<long long>& a) {
        if (l == r) { tree_[p] = a[l]; return; }
        int m = (l + r) / 2;
        build(p * 2, l, m, a);
        build(p * 2 + 1, m + 1, r, a);
        tree_[p] = tree_[p * 2] + tree_[p * 2 + 1];
    }
    void push(int p, int l, int r) {
        if (!lazy_[p] || l == r) return;
        int m = (l + r) / 2;
        apply(p * 2, l, m, lazy_[p]);
        apply(p * 2 + 1, m + 1, r, lazy_[p]);
        lazy_[p] = 0;
    }
    void apply(int p, int l, int r, long long delta) {
        tree_[p] += delta * (r - l + 1);
        lazy_[p] += delta;
    }
    void range_add(int p, int l, int r, int ql, int qr, long long delta) {
        if (ql <= l && r <= qr) return apply(p, l, r, delta);
        push(p, l, r);
        int m = (l + r) / 2;
        if (ql <= m) range_add(p * 2, l, m, ql, qr, delta);
        if (qr > m) range_add(p * 2 + 1, m + 1, r, ql, qr, delta);
        tree_[p] = tree_[p * 2] + tree_[p * 2 + 1];
    }
    long long query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree_[p];
        push(p, l, r);
        int m = (l + r) / 2;
        long long ans = 0;
        if (ql <= m) ans += query(p * 2, l, m, ql, qr);
        if (qr > m) ans += query(p * 2 + 1, m + 1, r, ql, qr);
        return ans;
    }
};
class SkipList {
public:
    SkipList() : gen_(random_device{}()) { head_ = new Node(INT_MIN, kMaxLevel); }
    bool search(int x) const {
        Node* cur = head_;
        for (int lvl = level_ - 1; lvl >= 0; --lvl) {
            while (cur->next[lvl] && cur->next[lvl]->value < x) cur = cur->next[lvl];
        }
        cur = cur->next[0];
        return cur && cur->value == x;
    }
    void insert(int x) {
        vector<Node*> update(kMaxLevel, nullptr);
        Node* cur = head_;
        for (int lvl = level_ - 1; lvl >= 0; --lvl) {
            while (cur->next[lvl] && cur->next[lvl]->value < x) cur = cur->next[lvl];
            update[lvl] = cur;
        }
        cur = cur->next[0];
        if (cur && cur->value == x) return;
        int lvl = random_level();
        if (lvl > level_) {
            for (int i = level_; i < lvl; ++i) update[i] = head_;
            level_ = lvl;
        }
        Node* node = new Node(x, lvl);
        for (int i = 0; i < lvl; ++i) {
            node->next[i] = update[i]->next[i];
            update[i]->next[i] = node;
        }
    }
    void erase(int x) {
        vector<Node*> update(kMaxLevel, nullptr);
        Node* cur = head_;
        for (int lvl = level_ - 1; lvl >= 0; --lvl) {
            while (cur->next[lvl] && cur->next[lvl]->value < x) cur = cur->next[lvl];
            update[lvl] = cur;
        }
        cur = cur->next[0];
        if (!cur || cur->value != x) return;
        for (int i = 0; i < level_; ++i) {
            if (update[i]->next[i] != cur) break;
            update[i]->next[i] = cur->next[i];
        }
        delete cur;
        while (level_ > 1 && !head_->next[level_ - 1]) --level_;
    }
private:
    static constexpr int kMaxLevel = 16;
    struct Node {
        int value;
        vector<Node*> next;
        Node(int v, int level) : value(v), next(level, nullptr) {}
    };
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
vector<int> suffix_array(string s) {
    s.push_back('$');
    int n = s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    for (int i = 0; i < n; ++i) sa[i] = i, rnk[i] = s[i];
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
            int ra = a + k < n ? rnk[a + k] : -1;
            int rb = b + k < n ? rnk[b + k] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rnk = tmp;
        if (rnk[sa.back()] == n - 1) break;
    }
    sa.erase(sa.begin());
    return sa;
}
vector<int> manacher(const string& s) {
    string t = "^";
    for (char c : s) { t += '#'; t += c; }
    t += "#$";
    vector<int> p(t.size(), 0);
    int center = 0, right = 0;
    for (int i = 1; i + 1 < (int)t.size(); ++i) {
        int mir = 2 * center - i;
        if (i < right) p[i] = min(right - i, p[mir]);
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) ++p[i];
        if (i + p[i] > right) center = i, right = i + p[i];
    }
    return p;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    FenwickTree bit(5);
    for (int i = 0; i < 5; ++i) bit.add(i, i + 1);
    cout << "??????? 1..3 = " << bit.range_sum(1, 3) << '\n';
    SegmentTree seg({1, 2, 3, 4, 5});
    seg.range_add(1, 3, 2);
    cout << "????? 0..4 = " << seg.query(0, 4) << '\n';
    SkipList sk;
    sk.insert(10);
    sk.insert(5);
    sk.insert(20);
    cout << "???? 10: " << sk.search(10) << '\n';
    auto sa = suffix_array("banana");
    cout << "????: "; for (int x : sa) cout << x << ' '; cout << '\n';
    auto p = manacher("abacaba");
    cout << "Manacher ????: " << p.size() << '\n';
    assert(bit.range_sum(0, 4) == 15);
    assert(sk.search(5));
    return 0;
}

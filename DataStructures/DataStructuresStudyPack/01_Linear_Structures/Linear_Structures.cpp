
#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
template <typename T>
class DynamicArray {
public:
    void push_back(const T& value) { data_.push_back(value); }
    void insert(size_t pos, const T& value) { data_.insert(data_.begin() + (long long)pos, value); }
    void erase(size_t pos) { data_.erase(data_.begin() + (long long)pos); }
    size_t size() const { return data_.size(); }
    const T& operator[](size_t i) const { return data_[i]; }
    T& operator[](size_t i) { return data_[i]; }
    int find(const T& value) const {
        for (size_t i = 0; i < data_.size(); ++i) if (data_[i] == value) return (int)i;
        return -1;
    }
    const vector<T>& raw() const { return data_; }
private:
    vector<T> data_;
};
struct SinglyLinkedList {
    struct Node {
        int value;
        Node* next;
        Node(int v = 0, Node* n = nullptr) : value(v), next(n) {}
    };
    Node* dummy = new Node();
    ~SinglyLinkedList() { clear(); delete dummy; }
    void push_front(int x) { dummy->next = new Node(x, dummy->next); }
    void push_back(int x) {
        Node* cur = dummy;
        while (cur->next) cur = cur->next;
        cur->next = new Node(x);
    }
    bool erase_first(int x) {
        Node* cur = dummy;
        while (cur->next && cur->next->value != x) cur = cur->next;
        if (!cur->next) return false;
        Node* del = cur->next;
        cur->next = del->next;
        delete del;
        return true;
    }
    vector<int> to_vector() const {
        vector<int> res;
        for (Node* cur = dummy->next; cur; cur = cur->next) res.push_back(cur->value);
        return res;
    }
    void clear() {
        Node* cur = dummy->next;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        dummy->next = nullptr;
    }
};
class ArrayStack {
public:
    void push(int x) { st_.push_back(x); }
    void pop() { st_.pop_back(); }
    int top() const { return st_.back(); }
    bool empty() const { return st_.empty(); }
private:
    vector<int> st_;
};
class CircularQueue {
public:
    explicit CircularQueue(int capacity) : data_(capacity + 1), head_(0), tail_(0), cap_(capacity + 1) {}
    bool empty() const { return head_ == tail_; }
    bool full() const { return (tail_ + 1) % cap_ == head_; }
    void push(int x) {
        if (full()) throw runtime_error("????");
        data_[tail_] = x;
        tail_ = (tail_ + 1) % cap_;
    }
    void pop() {
        if (empty()) throw runtime_error("????");
        head_ = (head_ + 1) % cap_;
    }
    int front() const { return data_[head_]; }
private:
    vector<int> data_;
    int head_;
    int tail_;
    int cap_;
};
vector<int> build_lps(const string& p) {
    vector<int> lps(p.size(), 0);
    for (size_t i = 1, j = 0; i < p.size(); ++i) {
        while (j > 0 && p[i] != p[j]) j = lps[j - 1];
        if (p[i] == p[j]) ++j;
        lps[i] = (int)j;
    }
    return lps;
}
vector<int> kmp_search(const string& s, const string& p) {
    if (p.empty()) return {};
    vector<int> lps = build_lps(p), pos;
    for (size_t i = 0, j = 0; i < s.size(); ++i) {
        while (j > 0 && s[i] != p[j]) j = lps[j - 1];
        if (s[i] == p[j]) ++j;
        if (j == p.size()) {
            pos.push_back((int)i - (int)p.size() + 1);
            j = lps[j - 1];
        }
    }
    return pos;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(3);
    arr.insert(1, 2);
    arr.erase(0);
    cout << "??????: ";
    for (auto x : arr.raw()) cout << x << ' ';
    cout << '\n';
    SinglyLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    list.erase_first(1);
    cout << "????: ";
    for (int x : list.to_vector()) cout << x << ' ';
    cout << '\n';
    ArrayStack st;
    st.push(10);
    st.push(20);
    cout << "?? = " << st.top() << '\n';
    st.pop();
    CircularQueue q(3);
    q.push(7);
    q.push(8);
    cout << "?? = " << q.front() << '\n';
    q.pop();
    deque<int> dq{1, 2, 3};
    dq.push_front(0);
    dq.push_back(4);
    cout << "??????: " << dq.front() << ' ' << dq.back() << '\n';
    string text = "ababcabcacbab";
    string pattern = "abcac";
    auto pos = kmp_search(text, pattern);
    cout << "KMP ????: ";
    for (int x : pos) cout << x << ' ';
    cout << '\n';
    assert(arr.find(2) == 0);
    assert(!pos.empty());
    return 0;
}

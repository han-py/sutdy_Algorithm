#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class CircularQueue {
public:
    explicit CircularQueue(int cap) : data_(cap + 1), cap_(cap + 1) {}
    bool empty() const { return head_ == tail_; }
    bool full() const { return (tail_ + 1) % cap_ == head_; }
    void push(int x) { data_[tail_] = x; tail_ = (tail_ + 1) % cap_; }
    void pop() { head_ = (head_ + 1) % cap_; }
    int front() const { return data_[head_]; }
private:
    vector<int> data_;
    int head_ = 0, tail_ = 0, cap_;
};
class LinkedQueue {
public:
    void push(int x) { q_.push(x); }
    void pop() { q_.pop(); }
    int front() const { return q_.front(); }
    bool empty() const { return q_.empty(); }
private:
    queue<int> q_;
};
vector<int> monotonic_queue_max(const vector<int>& a, int k) {
    vector<int> ans;
    deque<int> dq;
    for (int i = 0; i < (int)a.size(); ++i) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) ans.push_back(a[dq.front()]);
    }
    return ans;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    CircularQueue cq(3);
    cq.push(1); cq.push(2);
    cout << "CircularQueue front = " << cq.front() << '\n';
    LinkedQueue lq;
    lq.push(10); lq.push(20);
    cout << "LinkedQueue front = " << lq.front() << '\n';
    auto w = monotonic_queue_max({1, 3, -1, -3, 5, 3, 6, 7}, 3);
    cout << "MonotonicQueue size = " << w.size() << '\n';
    assert(!w.empty());
    return 0;
}

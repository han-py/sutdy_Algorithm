#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class MinHeap {
public:
    void push(int x) { a_.push_back(x); push_heap(a_.begin(), a_.end(), greater<int>()); }
    void pop() { pop_heap(a_.begin(), a_.end(), greater<int>()); a_.pop_back(); }
    int top() const { return a_.front(); }
    bool empty() const { return a_.empty(); }
private:
    vector<int> a_;
};
vector<int> top_k(vector<int> a, int k) {
    priority_queue<int> pq;
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();
    }
    vector<int> res;
    while (!pq.empty()) { res.push_back(pq.top()); pq.pop(); }
    reverse(res.begin(), res.end());
    return res;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    MinHeap h;
    h.push(3); h.push(1); h.push(2);
    cout << "MinHeap top = " << h.top() << '\n';
    auto ans = top_k({9, 1, 8, 2, 7, 3}, 3);
    cout << "TopK size = " << ans.size() << '\n';
    assert(h.top() == 1);
    return 0;
}

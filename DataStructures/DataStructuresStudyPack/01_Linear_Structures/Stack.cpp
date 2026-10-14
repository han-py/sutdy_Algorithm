#include <cassert>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
class ArrayStack {
public:
    void push(int x) { st_.push_back(x); }
    void pop() { st_.pop_back(); }
    int top() const { return st_.back(); }
    bool empty() const { return st_.empty(); }
private:
    vector<int> st_;
};
class MinStack {
public:
    void push(int x) {
        data_.push_back(x);
        if (mins_.empty() || x <= mins_.back()) mins_.push_back(x);
    }
    void pop() {
        if (data_.back() == mins_.back()) mins_.pop_back();
        data_.pop_back();
    }
    int top() const { return data_.back(); }
    int get_min() const { return mins_.back(); }
private:
    vector<int> data_;
    vector<int> mins_;
};
vector<int> monotonic_stack_next_greater(const vector<int>& a) {
    vector<int> ans(a.size(), -1), st;
    for (int i = 0; i < (int)a.size(); ++i) {
        while (!st.empty() && a[st.back()] < a[i]) {
            ans[st.back()] = a[i];
            st.pop_back();
        }
        st.push_back(i);
    }
    return ans;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    ArrayStack st;
    st.push(1); st.push(2); st.push(3);
    cout << "ArrayStack top = " << st.top() << '\n';
    MinStack ms;
    ms.push(3); ms.push(1); ms.push(2);
    cout << "MinStack min = " << ms.get_min() << '\n';
    vector<int> a{2, 1, 2, 4, 3};
    auto next = monotonic_stack_next_greater(a);
    cout << "MonotonicStack size = " << next.size() << '\n';
    assert(ms.get_min() == 1);
    return 0;
}

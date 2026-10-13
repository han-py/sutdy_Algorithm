
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;
long long factorial(int n) {
    return n <= 1 ? 1 : 1LL * n * factorial(n - 1);
}
int binary_search_demo(const vector<int>& a, int target) {
    int l = 0, r = (int)a.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}
int range_sum(const vector<int>& prefix, int l, int r) {
    if (l > r) return 0;
    return prefix[r + 1] - prefix[l];
}
void print_complexity_table() {
    cout << "??????:\n";
    cout << "O(1): ?????????\n";
    cout << "O(log n): ??????????????????\n";
    cout << "O(n): ??????????\n";
    cout << "O(n log n): ??????????????\n";
    cout << "O(n^2): ???????????\n";
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    print_complexity_table();
    vector<int> a{1, 3, 5, 7, 9, 11};
    vector<int> prefix(a.size() + 1, 0);
    for (size_t i = 0; i < a.size(); ++i) prefix[i + 1] = prefix[i] + a[i];
    cout << "factorial(5) = " << factorial(5) << '\n';
    cout << "binary_search_demo(7) = " << binary_search_demo(a, 7) << '\n';
    cout << "range_sum(1, 4) = " << range_sum(prefix, 1, 4) << '\n';
    cout << "recursive_sum demo = " << accumulate(a.begin(), a.end(), 0) << '\n';
    assert(binary_search_demo(a, 11) == 5);
    assert(range_sum(prefix, 0, 2) == 9);
    return 0;
}

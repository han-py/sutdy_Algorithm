#include <iostream>
#include <algorithm>
using namespace std;

int maxSubArray(const int A[], int n) {
    if (n <= 0) return 0;
    int cur_max = A[0];
    int global_max = A[0];
    for (int i = 1; i < n; ++i) {
        cur_max = max(A[i], cur_max + A[i]);
        global_max = max(global_max, cur_max);
    }
    return global_max;
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    const int A[] = {1, -2, 3, 5, -3, 4};
    const int n = sizeof(A) / sizeof(A[0]);
    cout << maxSubArray(A, n) << endl; // 输出：9
    return 0;
}
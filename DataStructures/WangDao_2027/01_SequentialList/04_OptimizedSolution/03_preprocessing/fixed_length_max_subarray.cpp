#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/**
 * 例题2-6：求解 res 数组
 * res[i] 表示长度为 i+1 的连续子数组的元素和最大值
 * 前缀和优化解法：将暴力 O(n³) 优化为 O(n²)
 */
void ans(int A[], int n) {
    // 初始化结果数组，全部置为最小值
    vector<int> res(n, INT_MIN);

    // 构建前缀和数组 sum[0]=0，sum[i] = A[0]+A[1]+...+A[i-1]
    vector<int> sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + A[i - 1];
    }

    // 枚举所有连续子数组 [i, j]
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            // O(1) 计算子数组和
            int temp = sum[j + 1] - sum[i];
            // 子数组长度为 j-i+1，对应 res 下标为 j-i
            if (temp > res[j - i]) {
                res[j - i] = temp;
            }
        }
    }

    // 输出结果数组
    for (int k = 0; k < n; ++k) {
        cout << res[k] << " ";
    }
    cout << endl;
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    int A[] = {1, -2, 3, 5};
    int n = 4;
    ans(A, n); // 输出：5 8 6 7
    return 0;
}

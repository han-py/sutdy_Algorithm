/**
* 模板一：等值判断模板
 * 适用：查找确切值，数组元素无重复
 * 循环条件 while(L <= R)
 */
#include <iostream>
#include <vector>
using namespace std;

// 折半查找，找到返回下标，找不到返回 -1
int B_Search(vector<int>& A, int L, int R, int x)
{
    int mid;
    while (L <= R)
    {
        mid = L + (R - L) / 2;  // 防止 (L+R) 溢出，等价于 (L+R)/2
        if (A[mid] == x)
        {
            return mid;         // 查找成功，返回下标
        }
        else if (A[mid] > x)
        {
            R = mid - 1;        // x 在左半区间 [L, mid‑1]
        }
        else
        {
            L = mid + 1;        // x 在右半区间 [mid+1, R]
        }
    }
    return -1;                  // 查找失败
}

int main()
{
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    vector<int> arr = {1,3,5,7,9,11,13};
    int target = 7;
    int idx = B_Search(arr, 0, (int)arr.size()-1, target);
    if(idx != -1)
        cout << "找到 " << target << "，下标 = " << idx << endl;
    else
        cout << "未找到" << endl;
    return 0;
}
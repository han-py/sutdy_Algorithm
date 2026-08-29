/**
* 模板二：区间收敛模板
 * 适用：查找第一个/最后一个满足条件元素，允许数组重复元素
 * 循环条件 while(L < R)
 * 返回L，返回后需要额外判断是否命中目标
 */
#include <iostream>
#include <vector>
using namespace std;

// 查找第一个 >= x 的元素下标（第一个等于x的下标）
int B_Search_First(vector<int>& A, int L, int R, int x)
{
    int mid;
    while (L < R)                     // 收敛到区间只剩1个元素时退出
    {
        mid = L + (R - L) / 2;        // 防溢出
        if (A[mid] >= x)
        {
            R = mid;                  // 目标在 [L, mid]
        }
        else
        {
            L = mid + 1;              // 目标在 [mid+1, R]
        }
    }
    return L;                         // 返回边界，需要外部校验A[L]是否等于x
}

int main()
{
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    vector<int> arr = {1,2,2,2,3,4,5};
    int target = 2;
    int pos = B_Search_First(arr, 0, (int)arr.size()-1, target);

    // ⚠️必须额外判断查找是否成功
    if(pos < arr.size() && arr[pos] == target)
    {
        cout << "第一个等于 " << target << " 的下标：" << pos << endl;
    }
    else
    {
        cout << "元素不存在" << endl;
    }
    return 0;
}
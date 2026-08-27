#include <iostream>
#include <vector>

using namespace std;

// 划分函数：返回基准元素最终下标
int partition(vector<int>& arr, int left, int right)
{
    // 选最右侧元素作为基准
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; ++j)
    {
        if (arr[j] <= pivot)
        {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    // 将基准放到正确位置
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

// 快速排序递归函数
void quickSort(vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1);   // 排左半部分
        quickSort(arr, pivotIndex + 1, right);  // 排右半部分
    }
}

// 对外接口
void quickSort(vector<int>& arr)
{
    if (!arr.empty())
    {
        quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
    }
}

int main()
{
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    vector<int> data = {8, 3, 6, 2, 9, 1, 5, 7, 4};

    cout << "排序前：";
    for (int num : data) cout << num << " ";
    cout << "\n";

    quickSort(data);

    cout << "排序后：";
    for (int num : data) cout << num << " ";
    cout << "\n";

    return 0;
}
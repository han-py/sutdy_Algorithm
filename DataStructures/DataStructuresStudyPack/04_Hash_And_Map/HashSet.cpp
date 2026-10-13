#include <cassert>
#include <iostream>
#include <unordered_set>
using namespace std;
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    unordered_set<int> s;
    for (int x : {1, 2, 3, 2, 1}) s.insert(x);
    cout << "HashSet size = " << s.size() << '\n';
    cout << "Contains 2 = " << (s.count(2) != 0) << '\n';
    assert(s.size() == 3);
    return 0;
}

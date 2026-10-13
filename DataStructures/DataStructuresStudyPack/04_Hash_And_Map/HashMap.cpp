#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    unordered_map<string, int> cnt;
    for (string s : {"a", "b", "a", "c"}) ++cnt[s];
    cout << "HashMap a = " << cnt["a"] << '\n';
    cout << "HashMap size = " << cnt.size() << '\n';
    assert(cnt["a"] == 2);
    return 0;
}

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> suffix_array(string s) {
    s.push_back('$');
    int n = s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    for (int i = 0; i < n; ++i) sa[i] = i, rnk[i] = s[i];
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
            int ra = a + k < n ? rnk[a + k] : -1;
            int rb = b + k < n ? rnk[b + k] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rnk = tmp;
        if (rnk[sa.back()] == n - 1) break;
    }
    sa.erase(sa.begin());
    return sa;
}
vector<int> manacher(const string& s) {
    string t = "^";
    for (char c : s) { t += '#'; t += c; }
    t += "#$";
    vector<int> p(t.size(), 0);
    int center = 0, right = 0;
    for (int i = 1; i + 1 < (int)t.size(); ++i) {
        int mir = 2 * center - i;
        if (i < right) p[i] = min(right - i, p[mir]);
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) ++p[i];
        if (i + p[i] > right) center = i, right = i + p[i];
    }
    return p;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    auto sa = suffix_array("banana");
    auto p = manacher("abacaba");
    cout << "Suffix array size = " << sa.size() << '\n';
    cout << "Manacher size = " << p.size() << '\n';
    assert(!sa.empty());
    return 0;
}

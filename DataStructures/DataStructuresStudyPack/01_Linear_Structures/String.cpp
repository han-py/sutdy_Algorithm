#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<int> build_lps(const string& p) {
    vector<int> lps(p.size(), 0);
    for (size_t i = 1, j = 0; i < p.size(); ++i) {
        while (j > 0 && p[i] != p[j]) j = lps[j - 1];
        if (p[i] == p[j]) ++j;
        lps[i] = (int)j;
    }
    return lps;
}
vector<int> kmp_search(const string& s, const string& p) {
    vector<int> pos;
    if (p.empty()) return pos;
    auto lps = build_lps(p);
    for (size_t i = 0, j = 0; i < s.size(); ++i) {
        while (j > 0 && s[i] != p[j]) j = lps[j - 1];
        if (s[i] == p[j]) ++j;
        if (j == p.size()) {
            pos.push_back((int)i - (int)p.size() + 1);
            j = lps[j - 1];
        }
    }
    return pos;
}
bool is_palindrome(const string& s) {
    for (int l = 0, r = (int)s.size() - 1; l < r; ++l, --r) {
        if (s[l] != s[r]) return false;
    }
    return true;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    string s = "ababcabcacbab";
    string p = "abcac";
    auto pos = kmp_search(s, p);
    cout << "KMP matches = " << pos.size() << '\n';
    cout << "Palindrome aba = " << is_palindrome("aba") << '\n';
    assert(!pos.empty());
    return 0;
}

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class BloomFilter {
public:
    explicit BloomFilter(size_t bits = 1024) : bits_(bits), table_(bits, false) {}
    void add(const string& s) {
        for (size_t h : hashes(s)) table_[h % bits_] = true;
    }
    bool may_contain(const string& s) const {
        for (size_t h : hashes(s)) if (!table_[h % bits_]) return false;
        return true;
    }
private:
    size_t bits_;
    vector<bool> table_;
    static vector<size_t> hashes(const string& s) {
        size_t h1 = 0, h2 = 131, h3 = 233;
        for (unsigned char c : s) {
            h1 = h1 * 131 + c;
            h2 = h2 * 13331 + c;
            h3 = h3 * 239 + c;
        }
        return {h1, h2, h3};
    }
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    BloomFilter bf;
    bf.add("apple");
    bf.add("banana");
    cout << "Bloom apple = " << bf.may_contain("apple") << '\n';
    cout << "Bloom orange = " << bf.may_contain("orange") << '\n';
    assert(bf.may_contain("apple"));
    return 0;
}

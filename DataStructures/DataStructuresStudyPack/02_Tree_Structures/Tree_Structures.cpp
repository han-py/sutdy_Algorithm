
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int v) : val(v) {}
};
void preorder(TreeNode* root, vector<int>& out) {
    if (!root) return;
    out.push_back(root->val);
    preorder(root->left, out);
    preorder(root->right, out);
}
void inorder(TreeNode* root, vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}
void postorder(TreeNode* root, vector<int>& out) {
    if (!root) return;
    postorder(root->left, out);
    postorder(root->right, out);
    out.push_back(root->val);
}
vector<int> levelorder(TreeNode* root) {
    vector<int> out;
    if (!root) return out;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        auto* cur = q.front(); q.pop();
        out.push_back(cur->val);
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return out;
}
class BST {
public:
    void insert(int x) { root_ = insert(root_, x); }
    bool search(int x) const { return search(root_, x); }
    void erase(int x) { root_ = erase(root_, x); }
    vector<int> inorder_values() const {
        vector<int> out;
        inorder(root_, out);
        return out;
    }
private:
    TreeNode* root_ = nullptr;
    static TreeNode* insert(TreeNode* node, int x) {
        if (!node) return new TreeNode(x);
        if (x < node->val) node->left = insert(node->left, x);
        else if (x > node->val) node->right = insert(node->right, x);
        return node;
    }
    static bool search(TreeNode* node, int x) {
        if (!node) return false;
        if (node->val == x) return true;
        return x < node->val ? search(node->left, x) : search(node->right, x);
    }
    static TreeNode* minimum(TreeNode* node) {
        while (node && node->left) node = node->left;
        return node;
    }
    static TreeNode* erase(TreeNode* node, int x) {
        if (!node) return nullptr;
        if (x < node->val) node->left = erase(node->left, x);
        else if (x > node->val) node->right = erase(node->right, x);
        else {
            if (!node->left) {
                TreeNode* r = node->right;
                delete node;
                return r;
            }
            if (!node->right) {
                TreeNode* l = node->left;
                delete node;
                return l;
            }
            TreeNode* succ = minimum(node->right);
            node->val = succ->val;
            node->right = erase(node->right, succ->val);
        }
        return node;
    }
};
struct AVLNode {
    int val;
    int height = 1;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    explicit AVLNode(int v) : val(v) {}
};
class AVLTree {
public:
    void insert(int x) { root_ = insert(root_, x); }
    bool search(int x) const { return search(root_, x); }
private:
    AVLNode* root_ = nullptr;
    static int h(AVLNode* n) { return n ? n->height : 0; }
    static int balance(AVLNode* n) { return n ? h(n->left) - h(n->right) : 0; }
    static AVLNode* rotate_right(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* t2 = x->right;
        x->right = y;
        y->left = t2;
        y->height = max(h(y->left), h(y->right)) + 1;
        x->height = max(h(x->left), h(x->right)) + 1;
        return x;
    }
    static AVLNode* rotate_left(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* t2 = y->left;
        y->left = x;
        x->right = t2;
        x->height = max(h(x->left), h(x->right)) + 1;
        y->height = max(h(y->left), h(y->right)) + 1;
        return y;
    }
    static AVLNode* insert(AVLNode* node, int x) {
        if (!node) return new AVLNode(x);
        if (x < node->val) node->left = insert(node->left, x);
        else if (x > node->val) node->right = insert(node->right, x);
        else return node;
        node->height = max(h(node->left), h(node->right)) + 1;
        int bf = balance(node);
        if (bf > 1 && x < node->left->val) return rotate_right(node);
        if (bf < -1 && x > node->right->val) return rotate_left(node);
        if (bf > 1 && x > node->left->val) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        if (bf < -1 && x < node->right->val) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        return node;
    }
    static bool search(AVLNode* node, int x) {
        if (!node) return false;
        if (node->val == x) return true;
        return x < node->val ? search(node->left, x) : search(node->right, x);
    }
};
template <typename T>
class MinHeap {
public:
    void push(const T& x) {
        data_.push_back(x);
        sift_up(data_.size() - 1);
    }
    void pop() {
        swap(data_.front(), data_.back());
        data_.pop_back();
        if (!data_.empty()) sift_down(0);
    }
    const T& top() const { return data_.front(); }
    bool empty() const { return data_.empty(); }
private:
    vector<T> data_;
    void sift_up(size_t i) {
        while (i > 0) {
            size_t p = (i - 1) / 2;
            if (data_[p] <= data_[i]) break;
            swap(data_[p], data_[i]);
            i = p;
        }
    }
    void sift_down(size_t i) {
        while (true) {
            size_t l = i * 2 + 1, r = i * 2 + 2, s = i;
            if (l < data_.size() && data_[l] < data_[s]) s = l;
            if (r < data_.size() && data_[r] < data_[s]) s = r;
            if (s == i) break;
            swap(data_[s], data_[i]);
            i = s;
        }
    }
};
class Trie {
public:
    void insert(const string& s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!next_[u][c]) {
                next_[u][c] = (int)cnt_.size();
                next_.push_back({});
                cnt_.push_back(0);
                end_.push_back(0);
            }
            u = next_[u][c];
            ++cnt_[u];
        }
        ++end_[u];
    }
    bool search(const string& s) const {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!next_[u][c]) return false;
            u = next_[u][c];
        }
        return end_[u] > 0;
    }
    int prefix_count(const string& s) const {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!next_[u][c]) return 0;
            u = next_[u][c];
        }
        return cnt_[u];
    }
private:
    vector<array<int, 26>> next_ = { { } };
    vector<int> cnt_ = {0};
    vector<int> end_ = {0};
};
class DSU {
public:
    explicit DSU(int n) : parent_(n), size_(n, 1) {
        iota(parent_.begin(), parent_.end(), 0);
    }
    int find(int x) {
        return parent_[x] == x ? x : parent_[x] = find(parent_[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size_[a] < size_[b]) swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
        return true;
    }
private:
    vector<int> parent_;
    vector<int> size_;
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    vector<int> pre, in, post;
    preorder(root, pre);
    inorder(root, in);
    postorder(root, post);
    auto lev = levelorder(root);
    cout << "??: "; for (int x : pre) cout << x << ' '; cout << '\n';
    cout << "??: "; for (int x : in) cout << x << ' '; cout << '\n';
    cout << "??: "; for (int x : post) cout << x << ' '; cout << '\n';
    cout << "??: "; for (int x : lev) cout << x << ' '; cout << '\n';
    BST bst;
    for (int x : {5, 3, 7, 2, 4, 6, 8}) bst.insert(x);
    bst.erase(7);
    cout << "BST ??: "; for (int x : bst.inorder_values()) cout << x << ' '; cout << '\n';
    AVLTree avl;
    for (int x : {10, 20, 30, 40, 50, 25}) avl.insert(x);
    cout << "AVL ?? 25: " << avl.search(25) << '\n';
    MinHeap<int> heap;
    heap.push(3);
    heap.push(1);
    heap.push(2);
    cout << "??: " << heap.top() << '\n';
    Trie trie;
    trie.insert("tree");
    trie.insert("trie");
    trie.insert("trip");
    cout << "Trie ???? trie: " << trie.search("trie") << '\n';
    cout << "Trie ?? tri ???: " << trie.prefix_count("tri") << '\n';
    DSU dsu(5);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    cout << "??? 1 ? 2 ????: " << (dsu.find(1) == dsu.find(2)) << '\n';
    assert(bst.search(6));
    assert(!bst.search(7));
    assert(trie.search("tree"));
    return 0;
}

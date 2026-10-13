#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
using namespace std;
struct AVLNode {
    int val, h = 1;
    AVLNode *l = nullptr, *r = nullptr;
    explicit AVLNode(int v) : val(v) {}
};
int height(AVLNode* n) { return n ? n->h : 0; }
int balance(AVLNode* n) { return n ? height(n->l) - height(n->r) : 0; }
AVLNode* rotate_left(AVLNode* x) {
    AVLNode* y = x->r; AVLNode* t = y->l; y->l = x; x->r = t;
    x->h = max(height(x->l), height(x->r)) + 1;
    y->h = max(height(y->l), height(y->r)) + 1;
    return y;
}
AVLNode* rotate_right(AVLNode* y) {
    AVLNode* x = y->l; AVLNode* t = x->r; x->r = y; y->l = t;
    y->h = max(height(y->l), height(y->r)) + 1;
    x->h = max(height(x->l), height(x->r)) + 1;
    return x;
}
AVLNode* insert(AVLNode* node, int x) {
    if (!node) return new AVLNode(x);
    if (x < node->val) node->l = insert(node->l, x);
    else if (x > node->val) node->r = insert(node->r, x);
    else return node;
    node->h = max(height(node->l), height(node->r)) + 1;
    int bf = balance(node);
    if (bf > 1 && x < node->l->val) return rotate_right(node);
    if (bf < -1 && x > node->r->val) return rotate_left(node);
    if (bf > 1 && x > node->l->val) { node->l = rotate_left(node->l); return rotate_right(node); }
    if (bf < -1 && x < node->r->val) { node->r = rotate_right(node->r); return rotate_left(node); }
    return node;
}
struct TreapNode {
    int val, pri;
    TreapNode *l = nullptr, *r = nullptr;
    TreapNode(int v, int p) : val(v), pri(p) {}
};
TreapNode* rotate_left(TreapNode* x) { TreapNode* y = x->r; x->r = y->l; y->l = x; return y; }
TreapNode* rotate_right(TreapNode* y) { TreapNode* x = y->l; y->l = x->r; x->r = y; return x; }
TreapNode* treap_insert(TreapNode* root, int x, int pri) {
    if (!root) return new TreapNode(x, pri);
    if (x < root->val) {
        root->l = treap_insert(root->l, x, pri);
        if (root->l->pri > root->pri) root = rotate_right(root);
    } else if (x > root->val) {
        root->r = treap_insert(root->r, x, pri);
        if (root->r->pri > root->pri) root = rotate_left(root);
    }
    return root;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    AVLNode* avl = nullptr;
    for (int x : {10, 20, 30, 40, 50, 25}) avl = insert(avl, x);
    cout << "AVL height = " << height(avl) << '\n';
    mt19937 rng(123);
    TreapNode* treap = nullptr;
    for (int x : {5, 2, 8, 1, 4}) treap = treap_insert(treap, x, (int)rng());
    cout << "Treap root = " << treap->val << '\n';
    assert(height(avl) > 0);
    return 0;
}

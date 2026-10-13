#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
struct Node {
    int val;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int v) : val(v) {}
};
Node* insert(Node* root, int x) {
    if (!root) return new Node(x);
    if (x < root->val) root->left = insert(root->left, x);
    else if (x > root->val) root->right = insert(root->right, x);
    return root;
}
bool search(Node* root, int x) {
    if (!root) return false;
    if (root->val == x) return true;
    return x < root->val ? search(root->left, x) : search(root->right, x);
}
Node* minimum(Node* root) { while (root && root->left) root = root->left; return root; }
Node* erase(Node* root, int x) {
    if (!root) return nullptr;
    if (x < root->val) root->left = erase(root->left, x);
    else if (x > root->val) root->right = erase(root->right, x);
    else {
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        Node* s = minimum(root->right);
        root->val = s->val;
        root->right = erase(root->right, s->val);
    }
    return root;
}
void inorder(Node* root, vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    Node* root = nullptr;
    for (int x : {5, 3, 7, 2, 4, 6, 8}) root = insert(root, x);
    root = erase(root, 7);
    vector<int> in; inorder(root, in);
    cout << "BST size = " << in.size() << '\n';
    cout << "BST search 6 = " << search(root, 6) << '\n';
    assert(search(root, 4));
    return 0;
}

#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Node {
    int val;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int v) : val(v) {}
};
void preorder(Node* root, vector<int>& out) {
    if (!root) return;
    out.push_back(root->val);
    preorder(root->left, out);
    preorder(root->right, out);
}
void inorder(Node* root, vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}
void postorder(Node* root, vector<int>& out) {
    if (!root) return;
    postorder(root->left, out);
    postorder(root->right, out);
    out.push_back(root->val);
}
vector<int> levelorder(Node* root) {
    vector<int> out;
    if (!root) return out;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        out.push_back(cur->val);
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return out;
}
int height(Node* root) { return root ? 1 + max(height(root->left), height(root->right)) : 0; }
int count_nodes(Node* root) { return root ? 1 + count_nodes(root->left) + count_nodes(root->right) : 0; }
bool is_symmetric(Node* a, Node* b) {
    if (!a || !b) return a == b;
    return a->val == b->val && is_symmetric(a->left, b->right) && is_symmetric(a->right, b->left);
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(2);
    root->left->left = new Node(3);
    root->right->right = new Node(3);
    vector<int> p; preorder(root, p);
    cout << "BinaryTree nodes = " << count_nodes(root) << '\n';
    cout << "BinaryTree height = " << height(root) << '\n';
    cout << "BinaryTree symmetric = " << is_symmetric(root->left, root->right) << '\n';
    assert(!levelorder(root).empty());
    return 0;
}

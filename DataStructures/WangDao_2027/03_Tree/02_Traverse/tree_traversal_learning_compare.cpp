#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

// =========================================================
// 目标：把图片中的递归遍历，和常见的非递归写法放在一起对照学习
// 重点内容：
// 1. 二叉树先序 / 中序 / 后序：递归版 + 非递归版
// 2. 树和森林：递归版（孩子兄弟表示法）
// =========================================================

struct BTNode {
    char data;
    BTNode* lchild;
    BTNode* rchild;

    explicit BTNode(char d) : data(d), lchild(nullptr), rchild(nullptr) {}
};

struct TNode {
    char data;
    TNode* firstchild;
    TNode* nextbro;

    explicit TNode(char d) : data(d), firstchild(nullptr), nextbro(nullptr) {}
};

BTNode* NewBTNode(char data) {
    return new BTNode(data);
}

TNode* NewTNode(char data) {
    return new TNode(data);
}

void Visit(char x) {
    cout << x << ' ';
}

// =========================
// 一、二叉树：递归遍历
// =========================
void PreOrderRec(BTNode* p) {
    if (p == nullptr) {
        return;
    }
    Visit(p->data);
    PreOrderRec(p->lchild);
    PreOrderRec(p->rchild);
}

void InOrderRec(BTNode* p) {
    if (p == nullptr) {
        return;
    }
    InOrderRec(p->lchild);
    Visit(p->data);
    InOrderRec(p->rchild);
}

void PostOrderRec(BTNode* p) {
    if (p == nullptr) {
        return;
    }
    PostOrderRec(p->lchild);
    PostOrderRec(p->rchild);
    Visit(p->data);
}

// =========================
// 二、二叉树：非递归遍历
// =========================
// 先序：根 -> 左 -> 右
void PreOrderNonRec(BTNode* root) {
    if (root == nullptr) {
        return;
    }

    stack<BTNode*> st;
    st.push(root);

    while (!st.empty()) {
        BTNode* p = st.top();
        st.pop();
        Visit(p->data);

        // 栈是后进先出，所以先压右，再压左
        if (p->rchild != nullptr) {
            st.push(p->rchild);
        }
        if (p->lchild != nullptr) {
            st.push(p->lchild);
        }
    }
}

// 中序：左 -> 根 -> 右
void InOrderNonRec(BTNode* root) {
    stack<BTNode*> st;
    BTNode* p = root;

    while (p != nullptr || !st.empty()) {
        // 一直向左走，把路径上的结点依次压栈
        while (p != nullptr) {
            st.push(p);
            p = p->lchild;
        }

        p = st.top();
        st.pop();
        Visit(p->data);

        // 转向右子树
        p = p->rchild;
    }
}

// 后序：左 -> 右 -> 根
// 常见做法：两个栈
void PostOrderNonRec(BTNode* root) {
    if (root == nullptr) {
        return;
    }

    stack<BTNode*> s1;
    stack<BTNode*> s2;
    s1.push(root);

    while (!s1.empty()) {
        BTNode* p = s1.top();
        s1.pop();
        s2.push(p);

        // 先压左，再压右，最后从 s2 中逆序输出
        if (p->lchild != nullptr) {
            s1.push(p->lchild);
        }
        if (p->rchild != nullptr) {
            s1.push(p->rchild);
        }
    }

    while (!s2.empty()) {
        Visit(s2.top()->data);
        s2.pop();
    }
}

// =========================
// 三、树和森林：递归遍历（孩子兄弟表示法）
// =========================
void TreePreorder(TNode* T) {
    if (T == nullptr) {
        return;
    }
    Visit(T->data);
    TreePreorder(T->firstchild);
    TreePreorder(T->nextbro);
}

void TreePostorder(TNode* T) {
    if (T == nullptr) {
        return;
    }
    TreePostorder(T->firstchild);
    Visit(T->data);
    TreePostorder(T->nextbro);
}

// =========================
// 四、构造演示数据
// =========================
// 二叉树：
//         A
//       /   \
//      B     C
//     / \     \
//    D   E     F
BTNode* BuildBinaryDemo() {
    BTNode* A = NewBTNode('A');
    BTNode* B = NewBTNode('B');
    BTNode* C = NewBTNode('C');
    BTNode* D = NewBTNode('D');
    BTNode* E = NewBTNode('E');
    BTNode* F = NewBTNode('F');

    A->lchild = B;
    A->rchild = C;
    B->lchild = D;
    B->rchild = E;
    C->rchild = F;

    return A;
}

// 树/森林示例（孩子兄弟表示法）
// 森林由三棵树组成：A、D、F
// A 的孩子：B、C
// D 的孩子：E
TNode* BuildForestDemo() {
    TNode* A = NewTNode('A');
    TNode* B = NewTNode('B');
    TNode* C = NewTNode('C');
    TNode* D = NewTNode('D');
    TNode* E = NewTNode('E');
    TNode* F = NewTNode('F');

    A->firstchild = B;
    B->nextbro = C;

    D->firstchild = E;

    A->nextbro = D;
    D->nextbro = F;

    return A;
}

void DestroyBinary(BTNode*& p) {
    if (p == nullptr) {
        return;
    }
    DestroyBinary(p->lchild);
    DestroyBinary(p->rchild);
    delete p;
    p = nullptr;
}

void DestroyForest(TNode*& T) {
    if (T == nullptr) {
        return;
    }
    DestroyForest(T->firstchild);
    DestroyForest(T->nextbro);
    delete T;
    T = nullptr;
}

// =========================
// 五、主函数：递归与非递归对照输出
// =========================
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cout << "==================================================\n";
    cout << "二叉树与树/森林遍历学习文件（递归 vs 非递归对照）\n";
    cout << "==================================================\n\n";

    BTNode* binaryRoot = BuildBinaryDemo();

    cout << "【一】二叉树先序遍历\n";
    cout << "递归版   ：";
    PreOrderRec(binaryRoot);
    cout << "\n非递归版 ：";
    PreOrderNonRec(binaryRoot);
    cout << "\n\n";

    cout << "【二】二叉树中序遍历\n";
    cout << "递归版   ：";
    InOrderRec(binaryRoot);
    cout << "\n非递归版 ：";
    InOrderNonRec(binaryRoot);
    cout << "\n\n";

    cout << "【三】二叉树后序遍历\n";
    cout << "递归版   ：";
    PostOrderRec(binaryRoot);
    cout << "\n非递归版 ：";
    PostOrderNonRec(binaryRoot);
    cout << "\n\n";

    cout << "【四】树和森林的递归遍历（孩子兄弟表示法）\n";
    TNode* forestRoot = BuildForestDemo();

    cout << "先根遍历（递归） ：";
    TreePreorder(forestRoot);
    cout << "\n";

    cout << "后根遍历（递归） ：";
    TreePostorder(forestRoot);
    cout << "\n\n";

    cout << "【五】对照记忆口诀\n";
    cout << "1. 先序：先访问自己，再左，再右。\n";
    cout << "2. 中序：先左，再自己，最后右。\n";
    cout << "3. 后序：先左，再右，最后自己。\n";
    cout << "4. 树/森林转孩子兄弟表示法后，可类比成二叉树来理解。\n";
    cout << "5. 非递归版的核心是：用栈模拟递归过程。\n";

    DestroyBinary(binaryRoot);
    DestroyForest(forestRoot);

    return 0;
}



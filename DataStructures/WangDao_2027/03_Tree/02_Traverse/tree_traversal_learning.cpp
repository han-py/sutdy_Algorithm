#include <cstdio>
#include <iostream>

using namespace std;

// =========================
// 一、二叉树结点定义
// =========================
struct BTNode {
    char data;
    BTNode* lchild;
    BTNode* rchild;

    explicit BTNode(char d) : data(d), lchild(nullptr), rchild(nullptr) {}
};

// =========================
// 二、树（孩子兄弟表示法）结点定义
// firstchild：第一个孩子
// nextbro：下一个兄弟
// =========================
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

// 访问结点：这里用中文提示，方便对照图片里的 visit(p)
void Visit(char x) {
    cout << x << ' ';
}

// =========================
// 三、二叉树的三种递归遍历
// 对应图片中的：
// 1. PreOrder(p)
// 2. InOrder(p)
// 3. PostOrder(p)
// =========================
void PreOrder(BTNode* p) {
    if (p == nullptr) {
        return;
    }
    // 先访问自己，再遍历左子树，最后遍历右子树
    Visit(p->data);
    PreOrder(p->lchild);
    PreOrder(p->rchild);
}

void InOrder(BTNode* p) {
    if (p == nullptr) {
        return;
    }
    // 先遍历左子树，再访问自己，最后遍历右子树
    InOrder(p->lchild);
    Visit(p->data);
    InOrder(p->rchild);
}

void PostOrder(BTNode* p) {
    if (p == nullptr) {
        return;
    }
    // 先遍历左子树，再遍历右子树，最后访问自己
    PostOrder(p->lchild);
    PostOrder(p->rchild);
    Visit(p->data);
}

// =========================
// 四、树和森林的递归遍历
// 这里使用“孩子兄弟表示法”
// 逻辑上可以看成：
// firstchild 相当于左子树
// nextbro    相当于右子树
// =========================
void TreePreorder(TNode* T) {
    if (T == nullptr) {
        return;
    }
    // 先访问当前结点，再遍历第一个孩子，最后遍历下一个兄弟
    Visit(T->data);
    TreePreorder(T->firstchild);
    TreePreorder(T->nextbro);
}

void TreePostorder(TNode* T) {
    if (T == nullptr) {
        return;
    }
    // 先遍历所有孩子，再访问当前结点，最后遍历兄弟
    TreePostorder(T->firstchild);
    Visit(T->data);
    TreePostorder(T->nextbro);
}

// =========================
// 五、构造示例数据
// 二叉树示例：
//         A
//       /   \
//      B     C
//     / \     \
//    D   E     F
// =========================
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

// 树/森林示例：
// 森林有三棵树：
// 1) A 的孩子：B、C
// 2) D 的孩子：E
// 3) F 单独成树
// 孩子兄弟表示法下：
// A -> nextbro -> D -> nextbro -> F
// A -> firstchild -> B -> nextbro -> C
// D -> firstchild -> E
TNode* BuildForestDemo() {
    TNode* A = NewTNode('A');
    TNode* B = NewTNode('B');
    TNode* C = NewTNode('C');
    TNode* D = NewTNode('D');
    TNode* E = NewTNode('E');
    TNode* F = NewTNode('F');

    // 第一棵树
    A->firstchild = B;
    B->nextbro = C;

    // 第二棵树
    D->firstchild = E;

    // 森林中的“树根串起来”
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

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cout << "==============================\n";
    cout << "二叉树递归遍历学习示例\n";
    cout << "==============================\n\n";

    BTNode* binaryRoot = BuildBinaryDemo();

    cout << "【1】二叉树的先序遍历：访问自己 -> 左子树 -> 右子树\n";
    cout << "结果：";
    PreOrder(binaryRoot);
    cout << "\n\n";

    cout << "【2】二叉树的中序遍历：左子树 -> 访问自己 -> 右子树\n";
    cout << "结果：";
    InOrder(binaryRoot);
    cout << "\n\n";

    cout << "【3】二叉树的后序遍历：左子树 -> 右子树 -> 访问自己\n";
    cout << "结果：";
    PostOrder(binaryRoot);
    cout << "\n\n";

    cout << "==============================\n";
    cout << "树和森林的递归遍历学习示例\n";
    cout << "==============================\n\n";

    TNode* forestRoot = BuildForestDemo();

    cout << "【4】树/森林的先根遍历：访问自己 -> 遍历第一个孩子 -> 遍历下一个兄弟\n";
    cout << "结果：";
    TreePreorder(forestRoot);
    cout << "\n\n";

    cout << "【5】树/森林的后根遍历：遍历所有孩子 -> 访问自己 -> 遍历下一个兄弟\n";
    cout << "结果：";
    TreePostorder(forestRoot);
    cout << "\n\n";

    cout << "==============================\n";
    cout << "学习提示\n";
    cout << "==============================\n";
    cout << "1. 二叉树的三种遍历，只是“访问自己”的时机不同。\n";
    cout << "2. 树/森林用孩子兄弟表示法后，可以自然转成递归代码。\n";
    cout << "3. 看到 firstchild 和 nextbro，就可以联想到“左孩子、右兄弟”。\n";

    // 这里把演示结点释放掉，方便学习“递归销毁”的写法。
    DestroyBinary(binaryRoot);
    DestroyForest(forestRoot);

    return 0;
}







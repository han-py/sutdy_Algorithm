#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;

    explicit Node(int d = 0, Node* n = nullptr) : data(d), next(n) {}
};

Node* NewNode(int value = 0) {
    return new Node(value);
}

void PrintList(Node* L, const string& title) {
    cout << title << "\n";
    cout << "L -> ";

    Node* p = L->next;
    if (p == nullptr) {
        cout << "NULL\n\n";
        return;
    }

    while (p != nullptr) {
        cout << p->data;
        p = p->next;
        if (p != nullptr) {
            cout << " -> ";
        }
    }
    cout << " -> NULL\n\n";
}

void HeadInsert(Node* L, Node* p) {
    // 先让 p 指向原来的第一个结点，再让头结点指向 p
    p->next = L->next;
    L->next = p;
}

void InsertAfter(Node* pre, Node* p) {
    // 先改 p->next，再改 pre->next，避免断链
    p->next = pre->next;
    pre->next = p;
}

void DeleteAfter(Node* pre) {
    // 删除 pre 后面的结点，注意先保存要删的结点
    if (pre == nullptr || pre->next == nullptr) {
        return;
    }

    Node* p = pre->next;
    pre->next = p->next;
    delete p;
}

void TailInsert(Node* L, const vector<int>& values) {
    // 找到尾指针 tail
    Node* tail = L;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    for (int value : values) {
        Node* p = NewNode(value);
        tail->next = p;
        tail = p;
    }
}

void DestroyList(Node*& L) {
    if (L == nullptr) {
        return;
    }

    Node* p = L;
    while (p != nullptr) {
        Node* next = p->next;
        delete p;
        p = next;
    }
    L = nullptr;
}

Node* CreateHeadNode() {
    return NewNode(); // 带头结点，头结点本身不存数据
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cout << "===== 1) Tail insertion: build the list in 1,2,3 order =====\n";
    Node* L1 = CreateHeadNode();
    TailInsert(L1, {1, 2, 3});
    PrintList(L1, "List after tail insertion:");

    cout << "===== 2) Head insertion: insert 1,2,3 and get 3,2,1 =====\n";
    Node* L2 = CreateHeadNode();
    for (int x : {1, 2, 3}) {
        HeadInsert(L2, NewNode(x));
    }
    PrintList(L2, "List after head insertion:");

    cout << "===== 3) Insert p after pre: set p->next first, then pre->next =====\n";
    Node* L3 = CreateHeadNode();
    TailInsert(L3, {1, 3});
    PrintList(L3, "Before insertion:");

    Node* pre = L3->next; // points to node 1
    Node* p = NewNode(2); // node 2 to insert
    InsertAfter(pre, p);
    PrintList(L3, "After inserting 2 after 1:");

    cout << "===== 4) Delete p: update the predecessor first, then free the node =====\n";
    Node* L4 = CreateHeadNode();
    TailInsert(L4, {1, 2, 3});
    PrintList(L4, "Before deletion:");

    DeleteAfter(L4->next); // delete node 2
    PrintList(L4, "After deleting 2:");

    cout << "===== 5) Traverse the list from L->next =====\n";
    Node* L5 = CreateHeadNode();
    TailInsert(L5, {10, 20, 30, 40});
    cout << "Traversal result: ";
    for (Node* q = L5->next; q != nullptr; q = q->next) {
        cout << q->data;
        if (q->next != nullptr) {
            cout << " ";
        }
    }
    cout << "\n\n";

    DestroyList(L1);
    DestroyList(L2);
    DestroyList(L3);
    DestroyList(L4);
    DestroyList(L5);

    return 0;
}


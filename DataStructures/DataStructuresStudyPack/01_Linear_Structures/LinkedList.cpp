#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
struct SinglyList {
    struct Node {
        int val;
        Node* next;
        Node(int v = 0, Node* n = nullptr) : val(v), next(n) {}
    };
    Node* dummy = new Node();
    ~SinglyList() { clear(); delete dummy; }
    void push_front(int x) { dummy->next = new Node(x, dummy->next); }
    void push_back(int x) {
        Node* cur = dummy;
        while (cur->next) cur = cur->next;
        cur->next = new Node(x);
    }
    bool erase_first(int x) {
        Node* cur = dummy;
        while (cur->next && cur->next->val != x) cur = cur->next;
        if (!cur->next) return false;
        Node* del = cur->next;
        cur->next = del->next;
        delete del;
        return true;
    }
    void reverse() {
        Node* prev = nullptr;
        Node* cur = dummy->next;
        while (cur) {
            Node* nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }
        dummy->next = prev;
    }
    vector<int> to_vector() const {
        vector<int> res;
        for (Node* cur = dummy->next; cur; cur = cur->next) res.push_back(cur->val);
        return res;
    }
    void clear() {
        Node* cur = dummy->next;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        dummy->next = nullptr;
    }
};
struct DoublyList {
    struct Node {
        int val;
        Node* prev;
        Node* next;
        Node(int v = 0) : val(v), prev(nullptr), next(nullptr) {}
    };
    Node* head = new Node();
    Node* tail = new Node();
    DoublyList() { head->next = tail; tail->prev = head; }
    ~DoublyList() { clear(); delete head; delete tail; }
    void push_back(int x) {
        Node* node = new Node(x);
        Node* p = tail->prev;
        p->next = node;
        node->prev = p;
        node->next = tail;
        tail->prev = node;
    }
    bool erase_first(int x) {
        for (Node* cur = head->next; cur != tail; cur = cur->next) {
            if (cur->val == x) {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                delete cur;
                return true;
            }
        }
        return false;
    }
    vector<int> to_vector() const {
        vector<int> res;
        for (Node* cur = head->next; cur != tail; cur = cur->next) res.push_back(cur->val);
        return res;
    }
    void clear() {
        Node* cur = head->next;
        while (cur != tail) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head->next = tail;
        tail->prev = head;
    }
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    SinglyList s;
    s.push_back(1);
    s.push_back(2);
    s.push_front(0);
    s.erase_first(1);
    s.reverse();
    cout << "SinglyList size = " << s.to_vector().size() << '\n';
    DoublyList d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.erase_first(20);
    cout << "DoublyList first = " << d.to_vector().front() << '\n';
    assert(!d.to_vector().empty());
    return 0;
}

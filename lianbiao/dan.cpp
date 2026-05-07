#include<bits/stdc++.h>
using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int x) : val(x), next(NULL) {}
};


//增
void insertHead(Node *head, int x){
    Node *p=new Node(x);
    p->val=x;
    p->next=head->next;
    head->next=p;
}

//删
void deleteNode(Node *head, int x){
    Node *p=head;
    while(p->next!=NULL){
        if(p->next->val==x){
            Node *tmp=p->next;
            p->next=p->next->next;
            delete tmp;
            return;
        }
        p=p->next;
    }
}

//改
void updateNode(Node *head,int x,int y){
    Node *p=head;
    while(p->next!=NULL){
        if(p->next->val==x){
            p->next->val=y;
            return;
        }
        p=p->next;
    }
}

//查
Node* searchNode(Node *head, int x){
    Node *p=head;
    while(p->next!=NULL){
        if(p->next->val==x){
            return p->next;
        }
        p=p->next;
    }
    return NULL;
}

//遍历输出
void input(Node *head){
    Node *p = head->next;  // 跳过哨兵节点
    while(p != NULL){
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

int main(){
    Node *head = new Node(0);
    head->next = NULL;

    // ========== 测试插入 ==========
    insertHead(head, 1);
    insertHead(head, 2);
    insertHead(head, 3);
    // 链表应为 3 -> 2 -> 1

    Node *p = head->next;
    assert(p->val == 3); p = p->next;
    assert(p->val == 2); p = p->next;
    assert(p->val == 1); p = p->next;
    assert(p == NULL);
    input(head);
    cout << "插入测试通过" << endl;

    // ========== 测试查找 ==========
    assert(searchNode(head, 2) != NULL);
    assert(searchNode(head, 2)->val == 2);
    assert(searchNode(head, 99) == NULL);  // 不存在的值
    input(head);
    cout << "查找测试通过" << endl;

    // ========== 测试修改 ==========
    updateNode(head, 2, 20);
    assert(searchNode(head, 2) == NULL);   // 旧值消失
    assert(searchNode(head, 20) != NULL);  // 新值存在
    input(head);
    cout << "修改测试通过" << endl;

    // ========== 测试删除 ==========
    deleteNode(head, 20);
    assert(searchNode(head, 20) == NULL);

    // 删除不存在的值（不应崩溃）
    deleteNode(head, 999);

    // 剩余链表应为 3 -> 1
    p = head->next;
    assert(p->val == 3); p = p->next;
    assert(p->val == 1); p = p->next;
    assert(p == NULL);
    input(head);
    cout << "删除测试通过" << endl;

    cout << "所有测试通过！" << endl;
    return 0;
}
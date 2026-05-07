#include<bits/stdc++.h>
using namespace std;

struct Node{
    int val;
    Node *prev;
    Node *next;
    Node(int x) : val(x),prev(NULL),next(NULL){}
};


//增
void insert(Node *head,int x){
    Node *p=new Node(x);
    p->next=head->next;
    p->prev=head;
    if(head->next!=NULL){
        head->next->prev=p;
    }
    head->next=p;

}

//删
void deleteNode(Node *head,int x){
    Node *p=head->next;
    while(p!=NULL){
        if(p->val==x){
            p->prev->next=p->next;
            if(p->next!=NULL){
                p->next->prev=p->prev;
            }
            delete p;
            return;
        }
        p=p->next;
    }
}

//改
void update(Node *head,int x,int y){
    Node *p=head->next;
    while(p!=NULL){
            if(p->val==x){
                p->val=y;
                return;
            }
            p=p->next;
    }
}

//查
Node* check(Node *head,int x){
    Node *p=head->next;
    while(p!=NULL){
        if(p->val==x){
            return p;
        }
        p=p->next;
    }
    return NULL;
}

//遍历输出
void output(Node *head){
    Node *p=head->next;
    while(p!=NULL){
        printf("%d ",p->val);
        p=p->next;
    }
    printf("\n");
}

int main(){
    Node *head = new Node(0);

    // 测试插入
    insert(head, 1);
    insert(head, 2);
    insert(head, 3);
    output(head);  // 3 2 1

    // 测试查找
    Node *res = check(head, 2);
    assert(res != NULL && res->val == 2);
    assert(check(head, 99) == NULL);
    cout << "查找测试通过" << endl;

    // 测试修改
    update(head, 2, 20);
    assert(check(head, 2) == NULL);
    assert(check(head, 20) != NULL);
    output(head);  // 3 20 1
    cout << "修改测试通过" << endl;

    // 测试删除
    deleteNode(head, 20);
    assert(check(head, 20) == NULL);
    deleteNode(head, 999);  // 删不存在的值，不应崩溃
    output(head);  // 3 1
    cout << "删除测试通过" << endl;

    cout << "所有测试通过！" << endl;
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

#define maxn 1000

typedef struct Node {
    char data;
    struct Node *firstchild;
    struct Node *nextsibling;
} Node;

// 新建节点
Node *NewNode(char x) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = x;
    p->firstchild = NULL;
    p->nextsibling = NULL;
    return p;
}

void AddEdge_ChildSibling(Node *u, Node *v) {
    v->nextsibling = u->firstchild;
    u->firstchild = v;
}


// 1. 先序遍历 - 递归 (根 -> 孩子 -> 兄弟)
void PreOrderRec(Node *root) {
    if (!root) return;
    printf("%c ", root->data);
    PreOrderRec(root->firstchild);
    PreOrderRec(root->nextsibling);
}

// 2. 后序遍历 - 递归 (孩子 -> 根 -> 兄弟) 
void PostOrderRec(Node *root) {
    if (!root) return;
    PostOrderRec(root->firstchild);
    printf("%c ", root->data);
    PostOrderRec(root->nextsibling);
}


// 3. 先序遍历 - 循环 
void PreOrder2(Node *t) {
    Node *st[maxn];
    int top = 0;
    
    if (t) st[top++] = t;
    
    while (top) {
        t = st[--top];
        printf("%c ", t->data);
        
        // 注意入栈顺序：先右兄弟，后左孩子 (因为栈是后进先出)
        if (t->nextsibling) st[top++] = t->nextsibling;
        if (t->firstchild) st[top++] = t->firstchild;
    }
}

// 4. 后序遍历 - 循环 
void PostOrder2(Node *t) {
    Node *st[maxn];
    int top = 0;
    
    while (t || top) {
        while (t) {
            // 先把当前节点和它的左儿子都入栈
            st[top++] = t;
            t = t->firstchild; // 一直向左孩子走到底
        }
        if (top) {
            t = st[--top];
            printf("%c ", t->data);
            t = t->nextsibling; // 转向右兄弟
        }
    }
}

// 5. 层级遍历 - 循环 
void LevelOrder(Node *t) {
    if (!t) return;
    Node *q[maxn];
    int front = 0, rear = 0;
    
    q[rear++] = t;
    while (front < rear) {
        Node *curr = q[front++];
        printf("%c ", curr->data);
        
        // 把当前节点的所有亲生孩子全部入队
        Node *child = curr->firstchild;
        while (child) {
            q[rear++] = child;
            child = child->nextsibling;
        }
    }
}

int main() {
    // 构造测试树：根 R, 孩子 A B, A 有孩子 D E
    Node *R = NewNode('R');
    Node *A = NewNode('A');
    Node *B = NewNode('B');
    Node *D = NewNode('D');
    Node *E = NewNode('E');

    AddEdge_ChildSibling(R, B); // 先插 B
    AddEdge_ChildSibling(R, A); // 再插 A，A 成为 firstchild，B 成为 A 的 nextsibling
    AddEdge_ChildSibling(A, E);
    AddEdge_ChildSibling(A, D);

    printf("递归先序: "); PreOrderRec(R); printf("\n");
    printf("循环先序: "); PreOrder2(R);   printf("\n");
    
    printf("递归后序: "); PostOrderRec(R); printf("\n");
    printf("循环后序: "); PostOrder2(R);   printf("\n");
    
    printf("循环层序: "); LevelOrder(R);   printf("\n");

    return 0;
}
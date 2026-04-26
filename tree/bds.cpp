#include<bits/stdc++.h>
using namespace std;

#define maxleng 1000

typedef struct ExprNode {
    int is_op;               // 标志位：1 表示是运算符，0 表示是纯数字
    int val;                 // 如果是数字，存具体的数值
    char op;                 // 如果是运算符，存 '+', '-', '*', '/'
    struct ExprNode *left;   // 左子树
    struct ExprNode *right;  // 右子树
} ExprNode;

// 创建一个数字节点 (叶子节点)
ExprNode* NewNumNode(int val) {
    ExprNode *p = (ExprNode*)malloc(sizeof(ExprNode));
    p->is_op = 0;
    p->val = val;
    p->left = NULL;
    p->right = NULL;
    return p;
}

// 创建一个运算符节点 (内部节点)
ExprNode* NewOpNode(char op, ExprNode *lchild, ExprNode *rchild) {
    ExprNode *p = (ExprNode*)malloc(sizeof(ExprNode));
    p->is_op = 1;
    p->op = op;
    p->left = lchild;
    p->right = rchild;
    return p;
}


// 从后缀表达式字符串构建
ExprNode* BuildExprTreeFromPostfix(const char *postfix) {
    // 注意：现在的栈里存的是 树节点的指针，而不是数字！
    ExprNode* st[maxleng]; 
    int top = 0;
    int i = 0;

    while (postfix[i] != '\0') {
        if (postfix[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            // 遇到数字：直接建一个叶子节点，压入树栈
            st[top++] = NewNumNode(num);
        } else {
            // 遇到运算符：从栈里弹出两棵现成的子树
            ExprNode *rightNode = st[--top];
            ExprNode *leftNode = st[--top];
            
            char op = postfix[i++];
            
            // 用当前运算符当根，把两棵子树“拼”起来，形成一棵更大的树
            ExprNode *newRoot = NewOpNode(op, leftNode, rightNode);
            
            // 把拼好的新树重新压回栈中
            st[top++] = newRoot;
        }
    }
    
    // 循环结束后，栈里只会剩下唯一一个节点，这就是整棵表达式树的树根！
    return st[0];
}

//对这棵树进行【后序遍历】来求出最终结果

int EvaluateExprTree(ExprNode *root) {
    if (root == NULL) return 0;

    // 递归边界：如果是叶子节点（纯数字），直接返回它的值
    if (root->is_op == 0) {
        return root->val;
    }

    // 后序遍历核心：分治法，自底向上！
    // 1. 先算出左子树的结果
    int left_val = EvaluateExprTree(root->left);
    
    // 2. 再算出右子树的结果
    int right_val = EvaluateExprTree(root->right);
    
    // 3. 最后在根节点进行合并计算
    if (root->op == '+') return left_val + right_val;
    if (root->op == '-') return left_val - right_val;
    if (root->op == '*') return left_val * right_val;
    if (root->op == '/') return left_val / right_val;

    return 0;
}

int main() {
    // 我们用上一步转换好的后缀表达式："8 3 2 6 * + 5 / - 14 +"
    // 它对应的中缀是 "8 - (3 + 2 * 6) / 5 + 14"
    const char *postfix = "8 3 2 6 * + 5 / - 14 +";
    
    printf("输入的后缀表达式: %s\n", postfix);
    
    // 1. 真正在内存中建树！拿到这棵树的树根
    ExprNode *root = BuildExprTreeFromPostfix(postfix);
    printf("表达式二叉树已在内存中物理构建完毕！\n");
    
    // 2. 利用后序遍历，自底向上求出答案
    int result = EvaluateExprTree(root);
    printf("对树进行后序遍历求得的最终结果: %d\n", result);
    
    return 0;
}
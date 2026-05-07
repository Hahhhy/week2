#include<bits/stdc++.h>
using namespace std;

struct Node{
    string val;
    Node* ls;
    Node*rs;
};

Node* newNode(string v){
    Node* p=new Node;
    p->val=v;
    p->ls=p->rs=nullptr;
    return p;
}

int getPriority(char op){
    if(op=='+'||op=='-') return 1;
    if(op=='*'||op=='/') return 2;
    return 0;
}

vector<string> infixToPosfix(string infix){
    vector<string> posfix;
    stack<char> ops;
    int n=infix.length();

    for(int i=0;i<n;++i){
        if(infix[i]==' ') continue;

        if(isdigit(infix[i])){
            string num="";
            while(i<n&&isdigit(infix[i])){
                num+=infix[i];
                ++i;
            }
            i--;
            posfix.push_back(num);
        }
        else if(infix[i]=='('){
            ops.push('(');
        }
        else if(infix[i]==')'){
            while(!ops.empty()&&ops.top()!='('){
                posfix.push_back(string(1,ops.top()));
                ops.pop();
            }
            if(!ops.empty()) ops.pop();
        }
        else{
            while(!ops.empty()&&getPriority(ops.top())>=getPriority(infix[i])){
                posfix.push_back(string(1,ops.top()));
                ops.pop();
            }
            ops.push(infix[i]);
        }
    }

    while(!ops.empty()){
        posfix.push_back(string(1,ops.top()));
        ops.pop();
    }
    return posfix;
}

Node* buildTree(vector<string>& posfix){
    stack<Node*> st;
    for(string s:posfix){
        if(s=="+"||s == "-" || s == "*" || s == "/"){
            Node* root=newNode(s);
            root->rs=st.top();
            st.pop();
            root->ls=st.top();
            st.pop();
            st.push(root);
        }else{
            st.push(newNode(s));
        }
    }
    return st.empty()?nullptr:st.top();
}


void preOrder(Node* root){
    if(!root) return;
    cout<<root->val<<" ";
    preOrder(root->ls);
    preOrder(root->rs);
}

void inOrder(Node* root){
    if(!root) return;
    inOrder(root->ls);
    cout<<root->val<<" ";
    inOrder(root->rs);
}

void posOrder(Node* root){
    if(!root) return;
    posOrder(root->ls);
    posOrder(root->rs);
    cout<<root->val<<" ";
}

void levelOrder(Node* root){
    if(!root) return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* curr=q.front();
        q.pop();
        cout<<curr->val<<" ";
        if(curr->ls) q.push(curr->ls);
        if(curr->rs) q.push(curr->rs);
    }
}


long long evaluateTree(Node* root){
    if(!root) return 0;

    if(!root->ls&&!root->rs){
        return stoll(root->val);
    }

    long long leftVal=evaluateTree(root->ls);
    long long rightVal=evaluateTree(root->rs);

    if(root->val=="+") return leftVal+rightVal;
    if(root->val=="-") return leftVal-rightVal;
    if(root->val=="*") return leftVal*rightVal;
    if(root->val=="/") return leftVal/rightVal;

    return 0;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string infix;

    cout<<"请输入中缀表达式"<<endl;
    getline(cin,infix);
    if(infix.empty()) return 0;
    vector<string> posfix=infixToPosfix(infix);
    Node* root=buildTree(posfix);
    cout << "\n--- 树的遍历测试 ---\n";
    cout << "先序遍历: "; preOrder(root); cout << "\n";
    cout << "中序遍历: "; inOrder(root); cout << "\n";
    cout << "后序遍历: "; posOrder(root); cout << "\n";
    cout << "层序遍历: "; levelOrder(root); cout << "\n";
    
    // 4. 求值
    cout << "\n--- 计算结果 ---\n";
    long long ans = evaluateTree(root);
    cout << "表达式的值为: " << ans << "\n";
    
    return 0;
}
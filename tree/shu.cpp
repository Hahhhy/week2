#include<bits/stdc++.h>
using namespace std;

struct Node{
    string val;
    Node* ls;
    Node* rs;
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

long long evaluateTree(Node* root){
    if(!root) return 0;

    if(!root->ls && !root->rs){
        return stoll(root->val) % 10000;
    }

    long long leftVal = evaluateTree(root->ls) % 10000;
    long long rightVal = evaluateTree(root->rs) % 10000;

    if(root->val=="+") return (leftVal + rightVal) % 10000;
    if(root->val=="-") return (leftVal - rightVal + 10000) % 10000; 
    if(root->val=="*") return (leftVal * rightVal) % 10000;
    if(root->val=="/") return (leftVal / rightVal) % 10000;

    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string infix;
    if(cin >> infix) {
        if(infix.empty()) return 0;
        
        vector<string> posfix = infixToPosfix(infix);
        Node* root = buildTree(posfix);

        cout << evaluateTree(root) << "\n";
    }
    
    return 0;
}
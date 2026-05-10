//https://www.luogu.com.cn/problem/B3642

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000005; 
int lc[MAXN]; 
int rc[MAXN];
int in_degree[MAXN]; 


// 先序遍历：根 -> 左 -> 右

void pre_iter(int root){
    if(!root) return;
    stack<int> st;
    st.push(root);
    while(!st.empty()){
        int u = st.top();
        st.pop();
        cout << u << " ";
        if(rc[u]) st.push(rc[u]);
        if(lc[u]) st.push(lc[u]);
    }
}


// 中序遍历：左 -> 根 -> 右

void in_iter(int root){
    stack<int> st;
    int curr = root;
    while(curr != 0 || !st.empty()){
        if(curr != 0){
            st.push(curr);     
            curr = lc[curr];
        } else {
            curr = st.top();   
            st.pop();
            cout << curr << " ";
            curr = rc[curr];   
        }
    }
}

//后序遍历：左 -> 右 -> 根
void post_iter(int root){
    stack<int> st;
    int curr = root;
    int last_visited = 0; 
    
    while(curr != 0 || !st.empty()){
        if(curr != 0){
            st.push(curr);
            curr = lc[curr];
        } else {
            int peek = st.top();
            if(rc[peek] != 0 && last_visited != rc[peek]){
                curr = rc[peek];
            } else {
                cout << peek << " ";
                last_visited = peek;
                st.pop();
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    if(!(cin >> n)) return 0;
    
    for(int i = 1; i <= n; i++){
        cin >> lc[i] >> rc[i];
        if(lc[i]) in_degree[lc[i]]++;
        if(rc[i]) in_degree[rc[i]]++;
    }
    
    int root = 1;
    for(int i = 1; i <= n; i++){
        if(in_degree[i] == 0){
            root = i;
            break;
        }
    }
    
    pre_iter(root);
    cout << "\n";
    
    in_iter(root);
    cout << "\n";
    
    post_iter(root);
    cout << "\n";

    return 0;
}
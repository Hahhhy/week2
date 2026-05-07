#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e6+5;

int val[MAXN];
vector<int> son[MAXN];

vector<int> level_nodes[MAXN];
int max_depth=0;
//先序，递归
void pre_rec(int u){
    if(!u) return;
    cout<<val[u]<<" ";
    for(int v : son[u]) {
        pre_rec(v);
    }
}
//先序，非递归
void pre_iter(int root){
    if(!root) return;
    stack<int> st;
    st.push(root);
    while(!st.empty()){
        int u=st.top();
        st.pop();
        cout<<val[u]<<" ";
        //逆向压栈，保证出栈的时候是从左到右遍历子节点
        for(int i=(int)son[u].size()-1;i>=0;--i){
        st.push(son[u][i]);
        }
    }
}

//后序遍历递归
void post_rec(int u){
    if(!u) return;
    for(int v : son[u]){
        post_rec(v);
    }
    cout<<val[u]<<" ";
}
//后序，非递归
void post_iter(int root){

    if(!root) return;

    stack<pair<int,int>> st;

    st.push({root,0});

    while(!st.empty()){

        int u=st.top().first;

        int idx=st.top().second;

        st.pop();

        if(idx<son[u].size()){

            st.push({u,idx+1});

            st.push({son[u][idx],0});

        }else{

            cout<<val[u]<<" ";

        }

    }

}

//中序遍历，递归
void in_rec(int u){
    if (!u) return;
    if (son[u].empty()) {
        cout<<val[u]<<" ";
        return;
    }
    in_rec(son[u][0]);
    cout<<val[u]<<" ";
    for(int i=1;i<son[u].size();i++){
        in_rec(son[u][i]);
    }
}

//中序遍历-非递归
void in_iter(int root){
    if(!root) return;
    stack<pair<int,int>> st;
    st.push({root,0});
    while(!st.empty()){
        int u=st.top().first;
        int idx=st.top().second;
        st.pop();
        if(son[u].empty()){
            if(idx==0) cout<<val[u]<<" ";
        }else if(idx==1){
            if(son[u].size()>1){
                st.push({u,2});
                st.push({son[u][1],0});
            }
        }else{
            if(idx<son[u].size()){
                st.push({u,idx+1});
                st.push({son[u][idx],0});
            }
        }
    }
}

//层级遍历
void level_rec_dfs(int u,int depth){
    if(!u) return;
    max_depth=max(max_depth,depth);
    level_nodes[depth].push_back(u);
    for(int v:son[u]){
        level_rec_dfs(v,depth+1);
    }
}

void level_rec(int root){
    for(int i=0;i<=max_depth;++i){
        level_nodes[i].clear();
    }
    max_depth=0;
    level_rec_dfs(root,0);
    for(int i=0;i<=max_depth;i++){
        for(int u:level_nodes[i]){
            cout<<val[u]<<" ";
        }
    }
}

void level_iter(int root){
    if(!root) return;
    queue<int> q;
    q.push(root);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cout<<val[u]<<" ";
        for(int v:son[u]){
            q.push(v);
        }
    }
    }
    
    

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int root=1;
    for(int i=0;i<=7;++i){
        val[i]=i;
    }
    son[1].push_back(2);
    son[1].push_back(3);
    son[1].push_back(4);
    son[2].push_back(5);
    son[2].push_back(6);
    son[4].push_back(7);
    //遍历
    cout << "--- 先序遍历 ---" << '\n';
    cout << "递归:   "; pre_rec(root); cout << '\n';
    cout << "非递归: "; pre_iter(root); cout << '\n';

    cout << "\n--- 中序遍历 ---" << '\n';
    cout << "递归:   "; in_rec(root); cout << '\n';
    cout << "非递归: "; in_iter(root); cout << '\n';

    cout << "\n--- 后序遍历 ---" << '\n';
    cout << "递归:   "; post_rec(root); cout << '\n';
    cout << "非递归: "; post_iter(root); cout << '\n';

    cout << "\n--- 层序遍历 ---" << '\n';
    cout << "递归:   "; level_rec(root); cout << '\n';
    cout << "非递归: "; level_iter(root); cout << '\n';

    return 0;
    
}
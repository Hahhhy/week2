#include<bits/stdc++.h>
using namespace std;

const int N=1000;
struct edge{
    int v,w;
    bool operator < (const edge &a) const{
        return w>a.w;
    }
};

vector<edge> e[N];

std::priority_queue<edge> q;

int dis[N];
int pre[N];
bool vis[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,s;
    cin>>n>>m>>s;
    for(int i=0;i<m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        e[u].push_back({v,w});
        e[v].push_back({u,w});
    }
    for(int i=0;i<n;++i){
        if(i==s) dis[i]=0;
        else dis[i]=INT_MAX;
    }
    q.push({s,0});
    while(!q.empty()){
        struct edge u=q.top();
        q.pop();        
        if(vis[u.v]) continue;
        vis[u.v]=true;
        for(auto i:e[u.v]){
            if(!vis[i.v]&&dis[i.v]>i.w){
                dis[i.v]=i.w;
                pre[i.v]=u.v;
                q.push({i.v,i.w});
            }
        }
    }

    for(int i=0;i<n;++i){
        cout<<i<<" ";
        cout<<pre[i]<<" ";
        cout<<dis[i]<<" ";
    }

    return 0;

}
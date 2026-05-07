#include<bits/stdc++.h>
using namespace std;


//声明距离数组
const int N=1e5+10;
int dist[N];

//边的结构体
struct Edge{
    int u,v,w;
} edges[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,s;
    cin>>n>>m>>s;
    //初始化距离数组
    for(int i=0;i<N;++i){
        dist[i]=1e9;
    }
    dist[s]=0;
    //边的输入
    for(int i=0;i<m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        edges[i]={u,v,w};
    }
    //Bellman-Ford算法
    for(int i=0;i<n-1;++i){
        for(int j=0;j<m;++j){
            int u=edges[j].u;
            int v=edges[j].v;
            int w=edges[j].w;
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
            }
        }
    }
    //第n次循环检查是否存在负权回路
    for(int j=0;j<m;++j){
        int u=edges[j].u;
        int v=edges[j].v;
        int w=edges[j].w;
        if(dist[u]+w<dist[v]){
            cout<<"Negative weight cycle detected!"<<endl;
            return 0;
        }
    }
    //输出结果
    for(int i=1;i<=n;++i){
        if(dist[i]==1e9){
            cout<<"INF"<<endl;
        }else{
            cout<<dist[i]<<endl;
        }
    }
    return 0;

}
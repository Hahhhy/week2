#include<bits/stdc++.h>
using namespace std;    


//声明距离矩阵
const int MAXN=1000;
int dist[MAXN][MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;

    //初始化距离矩阵
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) dist[i][j]=0;
            else dist[i][j]=INT_MAX;
        }
    }

    //输入边的信息
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dist[u][v]=w;
    }

    //Floyd-Warshall算法
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dist[i][k]!=INT_MAX && dist[k][j]!=INT_MAX){
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }   
            }
        }
    }
    //输出结果
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(dist[i][j]==INT_MAX) cout<<"INF ";
            else cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}

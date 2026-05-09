//AC代码：https://www.luogu.com.cn/problem/P3371  https://www.luogu.com.cn/problem/P4779

#include<bits/stdc++.h>
using namespace std;

const int max_node = 10005;  
const int max_edge = 500005;

struct Edge {
    int to, weight, next;
};

int head[max_node];
struct Edge e[max_edge]; 
int edgeCount = 0;

int dist[max_node];

struct node {
    int id, dist;
    bool operator<(const node& other) const {
        return dist > other.dist; 
    }
};
std::priority_queue<node> q;

bool vis[max_node];

void Dijkstra(int start, int n){
    for(int i = 1; i <= n; ++i){
        dist[i] = INT_MAX; 
    }
    dist[start] = 0; 
    q.push({start, 0}); 

    while(!q.empty()){
        node current = q.top();
        q.pop();
        int u = current.id;
        
        if(vis[u]) continue;
        vis[u] = true;   
        
        for(int i = head[u]; i > 0; i = e[i].next){
            int v = e[i].to;
            int w = e[i].weight;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                q.push({v, dist[v]});
            }
        }
    }
}

int main(){
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    
    int u, v, w;
    for(int i = 0; i < m; ++i){
        scanf("%d %d %d", &u, &v, &w);
        edgeCount++;
        e[edgeCount].to = v;
        e[edgeCount].weight = w;
        e[edgeCount].next = head[u];        
        head[u] = edgeCount;
    }

    Dijkstra(s, n); 

    for(int i = 1; i <= n; ++i){
        printf("%d ", dist[i]); 
    }
    
    return 0;
}
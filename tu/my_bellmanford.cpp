//AC代码https://www.luogu.com.cn/problem/P3385

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const int MAXM = 6005; 
const int INF = 1e9;

struct Edge {
    int u, v, w;
} edges[MAXM];

void solve() {
    int n, m;
    cin >> n >> m;
    
    int edgeCount = 0;
    for(int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[edgeCount++] = {u, v, w}; 
        if(w >= 0) {
            edges[edgeCount++] = {v, u, w};
        }
    }
    
    int dist[MAXN];
    for(int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[1] = 0;
    
    for(int i = 0; i < n - 1; ++i) {
        bool relaxed = false;
        for(int j = 0; j < edgeCount; ++j) { 
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            
            if(dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                relaxed = true;
            }
        }
        if(!relaxed) break;
    }
    
    bool has_negative_cycle = false;
    for(int j = 0; j < edgeCount; ++j) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if(dist[u] != INF && dist[u] + w < dist[v]) {
            has_negative_cycle = true;
            break;
        }
    }
    
    if(has_negative_cycle) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t; 
    while(t--) {
        solve(); 
    }
    
    return 0;
}
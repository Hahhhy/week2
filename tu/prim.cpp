//https://www.luogu.com.cn/problem/P3366

#include<bits/stdc++.h>
using namespace std;

const int N = 5005; 
const int INF = 10e9;

struct edge {
    int v, w;
    bool operator < (const edge &a) const {
        return w > a.w;
    }
};

vector<edge> e[N];
std::priority_queue<edge> q;

int dis[N];
bool vis[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w}); 
    }
    
    for (int i = 1; i <= n; ++i) {
        dis[i] = INF;
        vis[i] = false;
    }
    
    dis[1] = 0;
    q.push({1, 0});
    
    int ans = 0; 
    int cnt = 0;
    
    while (!q.empty()) {
        struct edge u = q.top();
        q.pop();        
        
        if (vis[u.v]) continue;
        vis[u.v] = true;
        
        ans += u.w; 
        cnt++;      
        
        for (auto i : e[u.v]) {
            if (!vis[i.v] && dis[i.v] > i.w) {
                dis[i.v] = i.w;
                q.push({i.v, i.w});
            }
        }
    }

    if (cnt == n) {
        cout << ans << "\n";
    } else {
        cout << "orz\n"; 
    }

    return 0;
}
//https://www.luogu.com.cn/problem/P3366

#include<bits/stdc++.h>
using namespace std;

const int N = 5005;      
const int E = 200005;    

struct Edge{
    int u, v, w;
};

Edge e[E];

bool cmp(Edge a, Edge b){
    return a.w < b.w; 
}

int fa[N];

int find(int x){
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]); 
}


bool join(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx == fy) return 0; 
    fa[fx] = fy;          
    return 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    if(!(cin >> n >> m)) return 0;
    
    for(int i = 0; i < m; ++i){
        cin >> e[i].u >> e[i].v >> e[i].w;
    }

  
    for(int i = 1; i <= n; ++i) fa[i] = i;

    sort(e, e + m, cmp);

    int cnt = 0; 
    int ans = 0; 

    for(int i = 0; i < m; ++i){
        if(join(e[i].u, e[i].v)){ 
            ans += e[i].w;        
            cnt++;                
            if(cnt == n - 1) break; 
        }
    }

    if(cnt == n - 1) {
        cout << ans << "\n";
    } else {
        cout << "orz\n"; 
    }

    return 0;
}
//AC代码：https://www.luogu.com.cn/problem/P7771

#include <bits/stdc++.h>
using namespace std;

const int MAX = 100010;
int n, m, u, v, del[MAX];
int du[MAX][2]; 
stack<int> st;
vector<int> G[MAX];

void dfs(int now) {
    for (int i = del[now]; i < G[now].size(); i = del[now]) {
        del[now] = i + 1;
        dfs(G[now][i]);
    }
    st.push(now);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m)) return 0;
    
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        du[u][1]++; 
        du[v][0]++; 
    }

    for (int i = 1; i <= n; i++) {
        sort(G[i].begin(), G[i].end());
    }
    
    int S = 1, cnt[2] = {0, 0}; 
    bool flag = 1; 
    
    for (int i = 1; i <= n; i++) {
        if (du[i][1] != du[i][0]) {
            flag = 0;
            if (du[i][1] - du[i][0] == 1) cnt[1]++, S = i;
            else if (du[i][0] - du[i][1] == 1) cnt[0]++;
            else {
                cout << "No\n";
                return 0;
            }
        }
    }
    
    if ((!flag) && !(cnt[0] == cnt[1] && cnt[0] == 1)) {
        cout << "No\n";
        return 0;
    }
    if (flag) {
        for (int i = 1; i <= n; i++) {
            if (du[i][1] > 0) {
                S = i;
                break;
            }
        }
    }
    dfs(S);
    if (st.size() != m + 1) {
        cout << "No\n";
        return 0;
    }
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    
    return 0; 
}
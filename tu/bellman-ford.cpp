#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f; // 极大值
int T,n,m,q,dis[2005],cnt[2005]; // cnt 记录最短路径经过边数
bool in_q[2005];
struct node{
	long long v,w;
}; vector <node> adj[2005];

bool spfa(int s){
	memset(cnt,0,sizeof(cnt)); // 初始化计数数组
	queue <int> q;
	q.push(s),in_q[s] = 1,dis[s] = 0; // 初始化起点
	while(!q.empty()){
		int h = q.front();
		q.pop(),in_q[h] = 0;
		if(cnt[h] > n) // 判断最短路边数是否大于 n，通常会因为添加超级源点写为 > 而并非 >=
            return 1; // 有负环
		for(node x : adj[h])
			if(dis[x.v] > dis[h] + x.w){ // 可以松弛
				dis[x.v] = dis[h] + x.w; // 进行松弛
				cnt[x.v] = cnt[h]+1; // 边数为对它松弛的点的边数+1
                if(!in_q[x.v]) // 不在队中
                    in_q[x.v] = 1,q.push(x.v); // 入队
			}
	}
	return 0; // 成功计算出最短路，故没有负环
}

int main(){
	cin >> T;
	while(T--){
		memset(adj,0,sizeof(adj));
		memset(in_q,0,sizeof(in_q));
		memset(dis,INF,sizeof(dis));
    // 多测时包括图也要初始化！！！
		cin >> n >> m;
		while(m--){  // 建图
			int u,v,w;
			cin >> u >> v >> w;
			if(w >= 0)
				adj[u].push_back({v,w}),adj[v].push_back({u,w});
			else
				adj[u].push_back({v,w});
		}
		cout << (spfa(1)?"YES\n":"NO\n");
	}
	return 0;
}

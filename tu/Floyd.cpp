//在一个带权重的图中（无论是无向图还是有向图），Floyd算法可以计算出任意两个节点之间的最短路径
//B3647 【模板】Floydhttps://www.luogu.com.cn/problem/B3647
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 10e9; 
const int MAXN = 105; 

int d[MAXN][MAXN];

int main() {
    // 优化输入输出速度
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    //初始化距离矩阵
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                d[i][j] = 0; // 自己到自己的距离为 0
            } else {
                d[i][j] = INF; // 初始时，其他点对之间的距离为无穷大
            }
        }
    }

    // 2. 读入边的数据 (如果是有向图则只赋值一次)
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // 如果输入中给出了多条连接相同两个点的边，保留权重最小的一条
        d[u][v] = min(d[u][v], w);
        d[v][u] = min(d[v][u], w); 
    }

    // 3. Floyd 核心算法 (动态规划思想)
    //最外层循环要是中间节点 k！？挖人shell
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // 如果 i 到 k 和 k 到 j 都有连通路径，才尝试进行松弛操作
                if (d[i][k] != INF && d[k][j] != INF) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    // 4. 输出结果
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << d[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
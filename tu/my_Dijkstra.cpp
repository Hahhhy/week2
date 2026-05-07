#include<bits/stdc++.h>
using namespace std;


//链式前向星存图
const int maxn = 1000; //假设最大节点数为1000
struct Edge {
    int to, weight, next;
};

//每个节点不止一条边，那么就需要一个head数组来存储这个点最近scanf进来的边的编号
int head[maxn];

//用e数组来存储边的信息，每一条边有他们独特的编号，然后我们要记录每条边的to、weight和next
struct Edge e[maxn * 2];
//边的编号，从0开始
int edgeCount = 0;

//声明距离数组
//因为是一个点，所以是一维数组
int dist[maxn];

//声明一个优先队列
//这个优先队列要存储的是这个节点的编号和距离，所以我们需要一个结构体来存储这些信息
//因为想要重构一下这个优先队列，所以我们需要一个结构体来存储节点的信息
struct node {
    int id, dist;
    //重载小于号，使得优先队列能够按照距离来排序
    bool operator<(const node& other) const {
        return dist > other.dist; //距离小的优先
    }
};
std::priority_queue<node> q;

//vis数组用来标记这个节点是否已经被访问过了
bool vis[maxn];

void Dijkstra(int start, int n){
    //初始化我们的目标，就是把距离数组填好
    for(int i=0;i<n;++i){
        dist[i] = INT_MAX; //初始距离为无穷大
    }
    dist[start] = 0; //起点到自己的距离为0
    //然后开始进行Dijkstra算法
    q.push({start, 0}); //把起点加入优先队列

    while(!q.empty()){
        node current = q.top();
        q.pop();
        int u = current.id;
        //如果这个节点已经被访问过了，那么就跳过
        if(vis[u]) continue;
        vis[u] = true; //标记这个节点已经被访问过了    
        for(int i=head[u];i>0;i=e[i].next){
            int v = e[i].to;
            int w = e[i].weight;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                //这个加入优先队列，如果之前加入过了
                q.push({v, dist[v]});
            }
        }
    }
}


int main(){
    //scanf three numbers: n, m
    int n, m;
    scanf("%d %d", &n, &m);
    //m edges;need for
    int u, v, w;
    for(int i=0;i<m;++i){
        //scanf three numbers: u, v, w
        //用链式前向星存图
        edgeCount++;
        scanf("%d %d %d",&u, &v, &w);
        e[edgeCount].to = v;
        e[edgeCount].weight = w;
        e[edgeCount].next = head[u];        
        head[u] = edgeCount;
    }
    //dijkstra
    Dijkstra(0, n); //假设起点是0
    //输出距离数组
    for(int i=0;i<n;++i){
        if(dist[i] == INT_MAX){
            printf("INF\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }
    return 0;
}
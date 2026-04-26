//B3644 【模板】拓扑排序 
#include<bits/stdc++.h>
using namespace std;
int n,in[110];
vector<int>g[110];
queue<int>q;
void tp()
{
	while(!q.empty())
	{
		int k=q.front();//取队头
		q.pop();//弹出
		cout<<k<<" ";//可以直接输出
		for(auto i:g[k])//遍历可以到达的所有点
		{
			in[i]--;//将下一个点的入度减一，意味着删除当前节点
			if(in[i]==0)//当下一个节点入度为零
			{
				q.push(i);//可以入队，因为他的祖宗都没了
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		while(x!=0)//没有结束
		{
			g[i].push_back(x);//加边
			in[x]++;//累加入度
			cin>>x;//继续输入
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(in[i]==0)//先从入度为零的点开始搜索
		{
			q.push(i);
		}
	}
	tp();
	return 0;
}

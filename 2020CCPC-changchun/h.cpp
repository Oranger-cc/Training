#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm> 
using namespace std;
const int N=100010;
const int S = 100005, T = 100006;
vector<int>s[N],w[N],back[N];
int d[N],cur[N],vis[N];
int z, n, m, mx, k, ban[N];
queue<int>q;
const int INF=0x3f3f3f3f;
template <typename Tp>
inline void read(Tp &x)
{
    x = 0;
    int f = 0;
    char ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9'))
        ch = getchar();
    if (ch == '-')
        f = 1, ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    if (f)
        x = -x;
}
void add(int x,int y,int l)
{
	s[x].push_back(y);
	s[y].push_back(x);
	w[x].push_back(l);
	w[y].push_back(0);
	back[x].push_back(s[y].size()-1);
	back[y].push_back(s[x].size()-1); 
}
int bfs(int st,int en)
{
	int c,i,y,x;
	//memset(d,0,sizeof(d));
	//memset(cur,0,sizeof(cur));
	//memset(vis,0,sizeof(vis));

    for (int i = 0; i <= mx;i++)
    {
        d[i] = cur[i] = vis[i] = 0;
    }
    d[S] = cur[S] = vis[S] = d[T] = cur[T] = vis[T] = 0;

    q.push(st),vis[st]=1;
	while(!q.empty())
	{
		x=q.front();
		q.pop();
		if(x==en) continue;
		c=s[x].size();
		for(i=0;i<c;i++)
		{
			y=s[x][i];
			if(!vis[y]&&w[x][i])
			{
				vis[y]=1;
				d[y]=d[x]+1;
				q.push(y);
			}
		}
	}
	return d[en];
}
int dfs(int x,int en,int f)
{
	int tmp,c,i,y,ans=0;
	if(x==en) return f;
	c=s[x].size();
	for(i=cur[x];i<c;i++)
	{
		cur[x]=i;
		y=s[x][i];
		if(d[y]!=d[x]+1||w[x][i]==0)
			continue;
		tmp=dfs(y,en,min(f-ans,w[x][i]));
		w[x][i]-=tmp;
		w[y][back[x][i]]+=tmp;
		ans+=tmp;
		if(f==ans) return ans;
	}
	d[x]=-1;
	return ans;
}
int dinic(int st,int en)
{
	int ans=0;
	while(bfs(st,en))
		ans+=dfs(st,en,INF);
	return ans;
}
void input()
{
    int u;
    read(m);
    read(n);
    read(k);
    if(m==1)
        mx = 9;
    else if(m==2)
        mx = 99;
    else if(m==3)
        mx = 999;
    else if(m==4)
        mx = 9999;
    else
        mx = 99999;

    //memset(ban, 0, sizeof(ban));
    for (int i = 0;i<=mx;i++)
    {
        ban[i] = 0;
    }
    ban[S] = ban[T] = 0;

    for (int i = 1; i <= n;i++)
    {
        read(u);
        ban[u] = 1;
    }
}
const int pw[6] = {1, 10, 100, 1000, 10000, 100000};
void build()
{
    for (int i = 0; i <= mx;i++)
    {
        s[i].clear();
        w[i].clear();
        back[i].clear();
    }

    s[S].clear();
    s[T].clear();
    w[S].clear();
    w[T].clear();
    back[S].clear();
    back[T].clear();

    int now[10], cur, nxt, sum;
    for (int i = 0; i <= mx;i++)
    {
        if(ban[i])
            continue;
        cur = i;
        sum = 0;
        for (int j = 1; j <= m;j++)
        {
            now[j] = cur % 10;
            sum += now[j];
            cur /= 10;
        }
        if(sum&1)
            add(S, i, 1);
        else
        {
            add(i, T, 1);
            continue;
        }
        for (int j = 1; j <= m; j++)
        {
            //pre
            if (now[j])
                nxt = i - pw[j - 1];
            else
                nxt = i + 9 * pw[j - 1];
            if (!ban[nxt])
                add(i, nxt, 1);
            //nxt
            if (now[j] < 9)
                nxt = i + pw[j - 1];
            else
                nxt = i - 9 * pw[j - 1];
            if (!ban[nxt])
                add(i, nxt, 1);
        }
    }
}
int main()
{
    freopen("h.in", "r", stdin);
    read(z);
    int ans1, ans2;
    while(z--)
    {
        input();
        build();
        ans1 = dinic(S,T);
        ban[k] = 1;
        build();
        ans2 = dinic(S,T);
        //printf("%d %d\n", ans1, ans2);
        if(ans1==ans2)
            puts("Bob");
        else
            puts("Alice");
    }
    return 0;
}
#include<bits/stdc++.h>
#define N 300010
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define tep(i,u) for(int i=head[u];~i;i=e[i].nxt)
#define INF 0x3f3f3f3f3f3f3f3f
#define id(i,j) ((i-1)*m+j)
#define pir pair<int,int>
#define mp(i,j) make_pair(i,j)
#define se second
using namespace std;
int n,m,v0,v1,s,head[N],cc,dis[N],ans=INF;
bool vis[N];
struct EDGE{int v,w,nxt;}e[N<<2];
inline void add_edge(int u,int v,int w)
{
	e[++cc]={v,w,head[u]};head[u]=cc;
}
string ch[N];
priority_queue<pir,vector<pir>,greater<pir> >q;
inline bool check(int x,int y)
{
	if(x<1||x>n||y<1||y>m||ch[x][y]=='#') return 0;
	return 1;
}
inline void dij(int s)
{
	rep(i,1,n*m) dis[i]=INF;
	q.push(mp(0,s));
	while(!q.empty())
	{
		int u=q.top().se;q.pop();
		if(vis[u]) continue;vis[u]=1;
		tep(i,u)
		{
			int v=e[i].v,w=e[i].w;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				q.push(mp(dis[v],v));
			}
		}
	}
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	memset(head,-1,sizeof(head));
	cin>>n>>m>>v0>>v1;s=n*m+1;
	rep(i,1,n) cin>>ch[i],ch[i]=' '+ch[i];
	rep(i,1,n) rep(j,1,m)
	{
		if(ch[i][j]=='.') add_edge(s,id(i,j),0);
		if(ch[i][j]=='L')
		{
			if(check(i-1,j+1)) add_edge(id(i-1,j+1),id(i,j),v0);
			if(check(i+1,j+1)) add_edge(id(i+1,j+1),id(i,j),v0);
			if(check(i,j+2)) add_edge(id(i,j+2),id(i,j),v1);
		}
		if(ch[i][j]=='R')
		{
			if(check(i-1,j-1)) add_edge(id(i-1,j-1),id(i,j),v0);
			if(check(i+1,j-1)) add_edge(id(i+1,j-1),id(i,j),v0);
			if(check(i,j-2)) add_edge(id(i,j-2),id(i,j),v1);
		}
		if(ch[i][j]=='U')
		{
			if(check(i+1,j+1)) add_edge(id(i+1,j+1),id(i,j),v0);
			if(check(i+1,j-1)) add_edge(id(i+1,j-1),id(i,j),v0);
			if(check(i+2,j)) add_edge(id(i+2,j),id(i,j),v1);
		}
		if(ch[i][j]=='D')
		{
			if(check(i-1,j+1)) add_edge(id(i-1,j+1),id(i,j),v0);
			if(check(i-1,j-1)) add_edge(id(i-1,j-1),id(i,j),v0);
			if(check(i-2,j)) add_edge(id(i-2,j),id(i,j),v1);
		}
	}
	dij(s);
	rep(i,1,n) rep(j,1,m) if(check(i,j))
	{
		if(check(i+1,j)) ans=min(ans,dis[id(i,j)]+dis[id(i+1,j)]);
		if(check(i,j+1)) ans=min(ans,dis[id(i,j)]+dis[id(i,j+1)]);
	}
	cout<<(ans==INF ? -1:ans)<<'\n';
	return 0;
}
#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
typedef long long LL;
#define F first
#define S second
typedef pair<LL,int> P;
#define MP make_pair

const int N=100100;
const LL inf=LL(0x7fffffff)*LL(0x7fffffff);

struct G {
	struct E { int to,ne; LL dis; } e[N];
	int n,m,la[N];
	
	void add(int x, int y, LL z){
		e[++m]=(E){y,la[x],z}; la[x]=m;
	}
	
	priority_queue < P,vector<P>,greater<P> > q;
	LL d[N],s[N];
	P a[N];
	
	void solve(int u){
		while (!q.empty()) q.pop();
		forto(i,1,n) d[i]=inf;
		d[u]=0; q.push(MP(0,u));
		
		while (!q.empty()){
			P p=q.top(); q.pop();
			while (!q.empty() && d[p.S]!=p.F){
				p=q.top(); q.pop();
			}
			if (d[p.S]!=p.F) break;
			int x=p.S;
			for(int i=la[x]; i; i=e[i].ne){
				int y=e[i].to;
				if (d[x]+e[i].dis < d[y]){
					d[y]=d[x]+e[i].dis;
					q.push(MP(d[y],y));
				}
			}
		}
		
		forto(i,1,n) s[i]=0;
		s[u]=1;
		forto(i,1,n) a[i]=MP(d[i],i);
		sort(a+1,a+n+1);
		forto(t,1,n){
			int x=a[t].S;
			if (d[x]==inf) break;
			for(int i=la[x]; i; i=e[i].ne){
				int y=e[i].to;
				if (d[x]+e[i].dis == d[y]) s[y]+=s[x];
			}
		}
	}
	
} g1,g2;

int xx[N],yy[N];
LL zz[N];

void getans(int x, int y, LL z){
	LL t1 = g1.d[x] + z + g2.d[y];
	if (g1.d[x]!=inf && g2.d[y]!=inf && t1 == g1.d[2]){
		if (g1.s[x]*g2.s[y]==g1.s[2]) printf("SAD\n");
			else printf("SOSO\n");
		return;
	}
	LL t2 = g1.d[y] + z + g2.d[x];
	if (g1.d[y]!=inf && g2.d[x]!=inf && t2 < g1.d[2]) printf("HAPPY\n");
		else printf("SOSO\n");
}

int main(){
	int n,m; scanf("%d%d",&n,&m);
	g1.n = g2.n = n;
	forto(i,1,m){
		int x,y; LL z; scanf("%d%d%lld",&x,&y,&z);
		g1.add(x,y,z); g2.add(y,x,z);
		xx[i]=x; yy[i]=y; zz[i]=z;
	}
	g1.solve(1); g2.solve(2);

	forto(i,1,m) getans(xx[i],yy[i],zz[i]);
	return 0;
}
		
		

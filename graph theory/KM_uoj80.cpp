#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define cmin(a,b) ((b)<(a)?(a)=(b):(a))
#define cmax(a,b) ((b)>(a)?(a)=(b):(a))

typedef long long LL;
const int N=500, inf=0x7fffffff;

int n,fx[N],fy[N],pre[N];
LL w[N][N],lx[N],ly[N],sla[N];
bool vx[N],vy[N],a[N][N];
int q[N],l,r;

bool check(int x, int y){
	if (!fy[y]){
		while (x){
			int t=fx[x];
			fx[x]=y; fy[y]=x;
			y=t; x=pre[y];
		}
		return true;
	}
	vy[y]=true; pre[y]=x;
	vx[q[++r]=fy[y]]=true;
	return false;
}

void bfs(int s){
	forto(i,1,n){ vx[i]=vy[i]=false; sla[i]=inf; }
	vx[q[l=r=1]=s]=true;
	while (true){
		while (l<=r){
			int x=q[l++];
			forto(y,1,n) if (!vy[y]){
				LL t=lx[x]+ly[y]-w[x][y];
				if (t==0 && check(x,y)) return;
				if (t && t<sla[y]){ sla[y]=t; pre[y]=x; }
			}
		}
		int d=inf;
		forto(y,1,n) if (!vy[y]) cmin(d,sla[y]);
		forto(x,1,n) if (vx[x]) lx[x]-=d;
		forto(y,1,n) if (vy[y]) ly[y]+=d; else sla[y]-=d;
		forto(y,1,n) if (!vy[y] && !sla[y] && check(pre[y],y)) return;
	}
}

void KM(){
	forto(x,1,n){
		lx[x]=w[x][1];
		forto(y,2,n) cmax(lx[x],w[x][y]);
	}
	forto(s,1,n) bfs(s);
}

int main(){
	int nl,nr,m;
	scanf("%d%d%d",&nl,&nr,&m);
	while (m--){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		w[x][y]=z; a[x][y]=true;
	}
	n=MAX(nl,nr);
	
	KM();
	LL ans=0;
	forto(i,1,n) ans+=lx[i];
	forto(j,1,n) ans+=ly[j];
	printf("%lld\n",ans);
	forto(i,1,nl) if (a[i][fx[i]]) printf("%d ",fx[i]); else printf("0 ");
	return 0;
}

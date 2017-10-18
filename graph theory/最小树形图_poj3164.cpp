#include<cstdlib>
#include<cstdio>
#include<cmath>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int N=110, M=40000, inf=0x7fffffff;
struct E{ int to,ne; double dis; } e[M];
int n,m,la[N],g[N],e_top;

void add1(int x, int y, double z){
	e[++e_top]=(E){y,g[x],z}; g[x]=e_top;
	e[++e_top]=(E){x,la[y],z}; la[y]=e_top;
}

void add2(int x, int y, double z){
	e[++e_top]=(E){y,la[x],z}; la[x]=e_top;
}

void build_graph(){
	static int x[N],y[N];
	forto(i,1,n) la[i]=g[i]=0;
	e_top=0;
	forto(i,1,n) scanf("%d%d",&x[i],&y[i]);
	forto(i,1,m){
		int a,b; scanf("%d%d",&a,&b);
		add1( a,b,sqrt( (x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]) ) );
	}
}

int q[N],l,r;
bool vis[N];

bool check(){
	forto(i,1,n) vis[i]=false;
	q[l=r=1]=1; vis[1]=true;
	while (l<=r){
		int x=q[l++];
		for(int i=g[x];i;i=e[i].ne){
			int y=e[i].to;
			if (vis[y]==false){
				vis[y]=true;
				q[++r]=y;
			}
		}
	}
	return r==n;
}

int f[N];

int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}

bool ok[N];
int sta[N],top;
double cho[N];

double solve(){
	double ans=0;
	forto(i,1,n) f[i]=i;
	forto(i,1,n) ok[i]=vis[i]=false;
	ok[1]=true;
	
	forto(t,1,n){
		vis[sta[top=1]=find(t)]=true;
		while (ok[sta[top]]==false){
			int x=sta[top], y=0; double z=1e100;
			for(int i=la[x];i;i=e[i].ne)
			if (find(e[i].to)!=x && e[i].dis<z){
				z=e[i].dis;
				y=e[i].to;
			}
			
			y=find(y);
			
			cho[x]=z;
			ans+=z;
			
			if (vis[y]){
				for(int i=la[y];i;i=e[i].ne) e[i].dis-=cho[y];
				while (sta[top]!=y){
					vis[ x=sta[top--] ]=false;
					for(int i=la[x];i;i=e[i].ne) add2(y, e[i].to, e[i].dis-cho[x]);
					f[x]=y;
				}
			} else vis[sta[++top]=y]=true;
		}
		while (top){
			ok[sta[top]]=true;
			vis[sta[top--]]=false;
		}
	}
	return ans;
}
			
int main(){
	while (scanf("%d%d",&n,&m)>0){
		build_graph();	
		if (check()) printf("%.2f\n",solve()); else printf("poor snoopy\n");
	}
	return 0;
}
 










	

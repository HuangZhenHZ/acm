#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=la[x];i;i=e[i].ne)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef long long LL;
const int N=1000000+100;

struct E{ int to,ne; } e[N<<1];
int la[N],e_top;

void add(int x, int y){
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,la[y]}; la[y]=e_top;
}

int a[N];
LL f0[N],f1[N];
bool vis1[N],vis2[N],vis3[N];
int x1,x2;

bool dfs1(int x, int fa){
	//printf("dfs1 %d\n",x);
	vis1[x]=true;
	forE(i,x){
		int y=e[i].to;
		if (y==fa) continue;
		if (vis1[y]){
			x1=x; x2=y;
			return true;
		}
		if (dfs1(y,x)) return true;
	}
	return false;
}
	
void dfs2(int x, bool vis[]){
	vis[x]=true;
	f0[x]=0; f1[x]=a[x];
	forE(i,x){
		int y=e[i].to;
		if (vis[y]) continue;
		dfs2(y,vis);
		f0[x]+=f1[y];
		f1[x]+=f0[y];
	}
	if (f0[x]>f1[x]) f1[x]=f0[x];
}

int main(){
	int n; scanf("%d",&n);
	forto(i,1,n){
		int j; scanf("%d%d",&a[i],&j);
		add(i,j);
	}
	LL ans=0;
	forto(i,1,n) if (vis2[i]==false){
		//printf("%d\n",i);
		dfs1(i,0);
		dfs2(x1,vis2);
		LL t1=f0[x1];
		dfs2(x2,vis3);
		LL t2=f0[x2];
		ans+=MAX(t1,t2);
	}
	printf("%lld",ans);
	return 0;
}
	



#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define MIN(a,b) ((a)<(b)?(a):(b))

const int N=5200, M=12000;

struct E{ int to,ne; } e[M<<1];
int n,m,la[N],e_top;
bool a[N][N];

void add(int x, int y){
	if (a[x][y]==false){
		e[++e_top]=(E){y,la[x]}; la[x]=e_top;
		e[++e_top]=(E){x,la[y]}; la[y]=e_top;
	}
	a[x][y]=true;
}

int dfn[N],low[N],cnt;
int sta[N],top;
int scc[N],scc_cnt;

void dfs(int x, int fa){
	dfn[x]=low[x]=++cnt; sta[++top]=x;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (y!=fa){
			if (low[y]==0){
				dfs(y,x);
				low[x]=MIN(low[x],low[y]);
			} else low[x]=MIN(low[x],dfn[y]);
		}
	}
	if (dfn[x]==low[x]){
		scc_cnt++;
		while (sta[top]!=x) scc[sta[top--]]=scc_cnt;
		scc[sta[top--]]=scc_cnt;
	}	
}


int d[N];

int main(){
	scanf("%d%d",&n,&m);
	forto(i,1,m){
		int x,y; scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,0);
	forto(x,1,n)
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (scc[x]!=scc[y]){
			d[scc[x]]++;
			d[scc[y]]++;
		}
	}
	int leaf=0;
	forto(i,1,n) if (d[i]==2) leaf++;
	printf("%d",(leaf+1)>>1);
	return 0;
}	

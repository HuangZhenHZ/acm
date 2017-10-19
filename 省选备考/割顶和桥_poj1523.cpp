#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int N=1200, M=120000;

struct E{ int to,ne; } e[M<<1];
int r,n,la[N],top;

void add(int x, int y){
	e[++top]=(E){y,la[x]}; la[x]=top;
	e[++top]=(E){x,la[y]}; la[y]=top;
	n=MAX(n,x); n=MAX(n,y);
}

int dfn[N],low[N],cnt,ans[N];

void dfs(int x, int fa){
	dfn[x]=low[x]=++cnt;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (y!=fa && dfn[y]) low[x]=MIN(low[x],dfn[y]);
		if (dfn[y]==0){
			dfs(y,x);
			low[x]=MIN(low[x],low[y]);
			if (low[y]>=dfn[x]) ans[x]++;
		}
	}
}

int main(){
	int x,y,t=0;
	for(scanf("%d",&x); x; scanf("%d",&x)){
		r=x; n=0;
		forto(i,1,1000) la[i]=0;
		top=0;
		
		scanf("%d",&y); add(x,y);
		for(scanf("%d",&x); x; scanf("%d",&x)){
			scanf("%d",&y); add(x,y);
		}
		
		forto(i,1,n) dfn[i]=low[i]=ans[i]=0;
		cnt=0;
		
		dfs(r,0);
		printf("Network #%d\n",++t);
		bool ok=false;
		ans[r]--;
		forto(i,1,n) if (ans[i]){
			printf("  SPF node %d leaves %d subnets\n",i,ans[i]+1);
			ok=true;
		}
		if (ok==false) printf("  No SPF nodes\n");
		printf("\n");
	}
	return 0;
}
	
			
		
	
	
	


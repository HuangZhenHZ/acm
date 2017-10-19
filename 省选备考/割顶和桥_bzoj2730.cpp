#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef long long LL;

const int N=600,M=600;

struct E{ int to,ne; } e[M<<1];
int n,m,r,la[N],e_top;

void add(int x, int y){
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,la[y]}; la[y]=e_top;
}

int dfn[N],low[N],cnt,f[N];

void dfs(int x, int fa){
	dfn[x]=low[x]=++cnt;
	if (fa) f[x]=1;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (dfn[y] && y!=fa) low[x]=MIN(low[x],dfn[y]);
		if (dfn[y]==0){
			dfs(y,x);
			low[x]=MIN(low[x],low[y]);
			if (low[y]>=dfn[x]) f[x]++;
		}
	}
}

bool vis[N];
int sta[N],sta_top;

int getsize(int x){
	//printf("vis %d\n",x);
	vis[x]=true;
	int size=1;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (vis[y]==false){
			if (f[y]<=1) size+=getsize(y);
			if (f[y]>=2) vis[sta[++sta_top]=y]=true;
		}	
	}
	return size;
}

int lis[N],top;

int main(){
	int t=0;
	for(scanf("%d",&m); m; scanf("%d",&m)){
		n=r=e_top=0;
		forto(i,1,550) la[i]=0;
		
		while (m--){
			int x,y; scanf("%d%d",&x,&y);
			n=MAX(n,x); n=MAX(n,y);
			add(x,y);
			if (r==0) r=x;
		}
		
		forto(i,1,n) dfn[i]=low[i]=f[i]=0;
		cnt=0;
		
		dfs(r,0);
		
		//forto(i,1,n) printf("f[%d]=%d\n",i,f[i]);
		
		forto(i,1,n) vis[i]=false;
		top=0;
		forto(i,1,n) if (f[i]<=1 && vis[i]==false){
			lis[++top]=getsize(i);
			if (sta_top!=1) top--;
			//printf("sta_top %d\n",sta_top);
			while (sta_top) vis[sta[sta_top--]]=false;
		}
		
		//forto(i,1,top) printf("lis[%d]=%d\n",i,lis[i]);
		if (top==0) printf("Case %d: 2 %d\n",++t,n*(n-1)/2);
		else {
			LL ans=1;
			forto(i,1,top) ans*=lis[i];
			printf("Case %d: %d %lld\n",++t,top,ans);
		}
	}
	return 0;
}
			
			
		
		
		
		
		
		
		
		
	
	
	


		



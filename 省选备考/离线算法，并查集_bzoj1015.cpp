#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
const int maxn=400100;

struct edge{
	int next,to;
} e[maxn];

int n,m,la[maxn],top;

void addedge(int x, int y){
	e[++top]=(edge){la[x],y}; la[x]=top;
	e[++top]=(edge){la[y],x}; la[y]=top;
}

int f[maxn],ans[maxn],a[maxn],now;
bool b[maxn],vis[maxn];

int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}

void add(int x){
//	printf("add %d\n",x);

	vis[x]=true; now++;
	for(int i=la[x];i;i=e[i].next)
	if (vis[e[i].to]){
		int fx=find(x), fy=find(e[i].to);
		if (fx!=fy){
			f[fy]=fx;
			now--;		
			
//			printf("link %d %d\n",x,e[i].to);
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	while (m--){
		int x,y; scanf("%d%d",&x,&y); x++; y++;
		addedge(x,y);
	}
	
//	forto(i,1,n){
//		printf("%d:",i);
//		for(int j=la[i];j;j=e[j].next) printf(" %d",e[j].to);
//		printf("\n");
//	}
	
	forto(i,1,n) f[i]=i;
	int k; scanf("%d",&k);
	forto(i,1,k){
		scanf("%d",&a[i]); a[i]++;
		b[a[i]]=true;
	}
	forto(i,1,n) if (b[i]==false) add(i);
	
	fordown(i,k,1){
		ans[i]=now;
		add(a[i]);
	}
	printf("%d\n",now);
	forto(i,1,k) printf("%d\n",ans[i]);
	return 0;
}
	
	

#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define inf 0x7fffffff

const int N=300, M=600;
int n,m,la[N],top,dis[N],q[N],cur[N];
struct E{int to,cap,next;}e[M];

void add(int a, int b, int c){
	e[++top]=(E){b,c,la[a]}; la[a]=top;
	e[++top]=(E){a,0,la[b]}; la[b]=top;
}

bool bfs(){
	forto(i,1,n) dis[i]=inf; dis[1]=0;
	int l=1, r=1; q[1]=1;
	while (l<=r){
		int t=q[l++];
		for(int i=la[t];i;i=e[i].next)
		if (e[i].cap && dis[e[i].to]==inf){
			dis[e[i].to]=dis[t]+1;
			q[++r]=e[i].to;
		}
	}
	return dis[n]!=inf;
}

int dinic(int x, int a){
	if (x==n||a==0) return a;
	int flow=0;
	for(int &i=cur[x];i;i=e[i].next){
		if (dis[x]+1!=dis[e[i].to]) continue;
		int t=dinic(e[i].to,MIN(a,e[i].cap));
		flow+=t; a-=t;
		e[i].cap-=t; e[i^1].cap+=t;
		if (a==0) return flow;
	}
	return flow;
}

int maxflow(){
	int flow=0;
	while (bfs()){
		forto(i,1,n) cur[i]=la[i];
		flow+=dinic(1,inf);
	}
	return flow;
}

int main(){
	while (scanf("%d%d",&m,&n)>0){
		forto(i,1,n) la[i]=0; top=1;
		while (m--){
			int a,b,c; scanf("%d%d%d",&a,&b,&c);
			add(a,b,c);
		}
		printf("%d\n",maxflow());
	}
	return 0;
}

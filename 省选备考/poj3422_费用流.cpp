#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x,y,z) for(int i=la[x],y=e[i].to,z=e[i].dis; i; i=e[i].ne,y=e[i].to,z=e[i].dis)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define cmin(a,b) ((b)<(a)?(a)=(b):(a))
#define cmax(a,b) ((b)>(a)?(a)=(b):(a))

const int N=5100, M=8000, inf=0x7fffffff;

struct E{ int to,cap,dis,ne; } e[M<<1];
int n,la[N],e_top;

void add(int x, int y, int cap, int dis){
	e[++e_top]=(E){y,cap,dis,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,0,-dis,la[y]}; la[y]=e_top;
}

int dis[N],q[N],l,r,prex[N],prei[N],low[N];
bool vis[N];

bool spfa(){
	forto(i,1,n){ dis[i]=inf; vis[i]=false; }
	dis[1]=0; vis[1]=true; low[1]=inf;
	q[l=r=1]=1;
	while (l<=r){
		int x=q[l++]; vis[x]=false;
		forE(i,x,y,z) if (e[i].cap && dis[x]+z<dis[y]){
			dis[y]=dis[x]+z;
			prex[y]=x; prei[y]=i; low[y]=MIN(low[x],e[i].cap);
			if (vis[y]==false) vis[q[++r]=y]=true;
		}
	}
	return dis[n]!=inf;
}

int flow,cost;

void mcmf(){
	while (spfa()){
		for(int x=n;x!=1;x=prex[x]){
			int i=prei[x];
			e[i].cap-=low[n];
			e[i^1].cap+=low[n];
		}
		flow+=low[n];
		cost+=low[n]*dis[n];
	}
}

int w[60][60],a,k;

int get(int x, int y, int z){
	return (((x-1)*a+(y-1))<<1)+1+z;
}

int main(){
	scanf("%d%d",&a,&k);
	forto(i,1,a) forto(j,1,a) scanf("%d",&w[i][j]);
	n=a*a*2+2;
	forto(i,1,a) forto(j,1,a){
		add(get(i,j,1),get(i,j,2),1,-w[i][j]);
		add(get(i,j,1),get(i,j,2),k,0);
	}
	forto(i,1,a) forto(j,1,a-1) add(get(i,j,2),get(i,j+1,1),k,0);
	forto(i,1,a-1) forto(j,1,a) add(get(i,j,2),get(i+1,j,1),k,0);
	add(1,get(1,1,1),k,0);
	add(get(a,a,2),n,k,0);
	mcmf();
	printf("%d\n",cost);
	return 0;
}
	
		

				
		
		
		
	





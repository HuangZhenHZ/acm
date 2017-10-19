#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int N=12000, M=42000, inf=0x7fffffff;

struct E{ int to,cap,ne; } e[M<<1];
int n,la[N],e_top;

void add(int x, int y, int z){
	e[++e_top]=(E){y,z,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,z,la[y]}; la[y]=e_top; //warn!!!
}

int q[N],l,r,dis[N],cur[N];

bool bfs(){
	q[l=r=1]=1;
	forto(i,1,n) dis[i]=inf;
	dis[1]=0;
	while (l<=r){
		int x=q[l++];
		for(int i=la[x];i;i=e[i].ne)
		if (e[i].cap && dis[x]+1<dis[e[i].to]){
			dis[e[i].to]=dis[x]+1;
			q[++r]=e[i].to;
		}
	}
	return dis[n]!=inf;
}

int dfs(int x, int a){
	if (x==n || a==0) return a;
	int flow=0;
	for(int &i=cur[x];i&&a;i=e[i].ne) if (dis[x]+1==dis[e[i].to] && e[i].cap){
		int t=dfs(e[i].to,MIN(a,e[i].cap));
		flow+=t; a-=t; e[i].cap-=t; e[i^1].cap+=t;
	}
	return flow;
}

int dinic(){
	int flow=0;
	while (bfs()){
		forto(i,1,n) cur[i]=la[i];
		flow+=dfs(1,inf);
		//printf("%d\n",flow);
	}
	return flow;
}	

const int maxn=120;

int a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
int nn,mm;

#define getnum(i,j) (((i)-1)*mm+(j)+1)

int main(){
	scanf("%d%d",&nn,&mm);
	n=nn*mm+2;
	e_top=1;
	
	forto(i,1,nn) forto(j,1,mm) scanf("%d",&a[i][j]);
	forto(i,1,nn) forto(j,1,mm) scanf("%d",&b[i][j]);
	forto(i,1,nn) forto(j,1,mm) scanf("%d",&c[i][j]);
	
	int sum=0;
	//printf("!!\n");
	//printf("e_top=%d\n",e_top);
	
	forto(i,1,nn) forto(j,1,mm){
		if ((i&1)^(j&1)){
			add(1,getnum(i,j),a[i][j]);
			add(getnum(i,j),n,b[i][j]);
			if (i> 1) add(getnum(i,j),getnum(i-1,j),c[i][j]+c[i-1][j]);
			if (i<nn) add(getnum(i,j),getnum(i+1,j),c[i][j]+c[i+1][j]);
			if (j> 1) add(getnum(i,j),getnum(i,j-1),c[i][j]+c[i][j-1]);
			if (j<mm) add(getnum(i,j),getnum(i,j+1),c[i][j]+c[i][j+1]);
		} else {
			add(1,getnum(i,j),b[i][j]);
			add(getnum(i,j),n,a[i][j]);
		}
		
		sum+=a[i][j]+b[i][j];
		if (i> 1) sum+=c[i][j];
		if (i<nn) sum+=c[i][j];
		if (j> 1) sum+=c[i][j];
		if (j<mm) sum+=c[i][j];
		//printf("e_top=%d\n",e_top);
	}
	//printf("!!\n");
	
	printf("%d",sum-dinic());
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	










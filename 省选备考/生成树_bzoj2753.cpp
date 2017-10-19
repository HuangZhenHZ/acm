#include<cstdlib>
#include<cstdio>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef long long LL;
const int inf=0x7fffffff;

const int N=110000, M=1100000;

struct E{ int to,dis,ne; } e[M<<1];
int la[N],e_top;

void add(int x, int y, int z){
	e[++e_top]=(E){y,z,la[x]}; la[x]=e_top;
}

int n,m,h[N],min[N];
int q[N],l,r;

void bfs(){
	forto(i,2,n) min[i]=inf;
	q[l=r=1]=1;
	while (l<=r){
		int x=q[l++];
		for(int i=la[x];i;i=e[i].ne){
			int y=e[i].to, z=e[i].dis;
			if (z<min[y]){
				if (min[y]==inf) q[++r]=y;
				min[y]=z;
			}
		}
	}
}

struct data{ int x,y,z; } a[M<<1];
int top;

bool comp(const data &a, const data &b){
	if (h[a.y]>h[b.y]) return true;
	if (h[a.y]<h[b.y]) return false;
	return a.z<b.z;
}	

int f[N];

int gf(int x){
	return f[x]==x?x:f[x]=gf(f[x]);
}

int main(){
	scanf("%d%d",&n,&m);
	forto(i,1,n) scanf("%d",&h[i]);
	forto(i,1,m){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if (h[x]>=h[y]) add(x,y,z);
		if (h[y]>=h[x]) add(y,x,z);
	}
	bfs();
	int sum=0;
	forto(i,1,n) if (min[i]!=inf) sum++;
	printf("%d ",sum);
	
	forto(x,1,n) if (min[x]!=inf)
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to, z=e[i].dis;
		if (min[y]!=inf) a[++top]=(data){x,y,z};
	}
	std::sort(a+1,a+top+1,comp);
	
	//forto(i,1,top) printf("%d %d %d\n", a[i].x, a[i].y, a[i].z);
	
	forto(i,1,n) f[i]=i;
	LL ans=0;
	forto(i,1,top){
		int x=a[i].x, y=a[i].y, z=a[i].z;
		int fx=gf(x), fy=gf(y);
		if (fx!=fy){
			ans+=z;
			f[fy]=fx;
		}
	}
	
	printf("%lld",ans);
	return 0;
}

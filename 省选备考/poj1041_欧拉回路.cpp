#include<cstdlib>
#include<cstdio>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define cmax(a,b) ((b)>(a)?(a)=(b):(a))

const int N=50,M=2000;

struct E{ int to,num,ne; } e[M<<1];
int n,m,la[N],e_top,sum[N];

void add(int x, int y, int z){
	e[++e_top]=(E){y,z,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,z,la[y]}; la[y]=e_top;
	sum[x]++; sum[y]++;
}

struct data{ int x,y,z; } a[M];
bool comp(const data &l, const data &r){ return l.z<r.z; }

bool vis[M];
int sta[M],top;

void dfs(int x){
	for(int i=la[x];i;i=e[i].ne)
	if (vis[e[i].num]==false){
		vis[e[i].num]=true;
		dfs(e[i].to);
		sta[++top]=e[i].num;
	}
}

int main(){
	int x,y,z;
	for(scanf("%d%d",&x,&y);x;scanf("%d%d",&x,&y)){
		n=m=e_top=0;
		
		scanf("%d",&z);
		a[++m]=(data){x,y,z};
		cmax(n,x); cmax(n,y);
		int k=MIN(x,y);
		
		for(scanf("%d%d",&x,&y);x;scanf("%d%d",&x,&y)){
			scanf("%d",&z);
			a[++m]=(data){x,y,z};
			cmax(n,x); cmax(n,y);
		}
		
		std::sort(a+1,a+m+1,comp);
		forto(i,1,n) la[i]=sum[i]=0;
		fordown(i,m,1) add(a[i].x,a[i].y,a[i].z);
		
		bool ok=true;
		forto(i,1,n) if (sum[i]&1){ ok=false; break; }
		if (ok==false){
			printf("Round trip does not exist.\n");
			continue;
		}
		
		forto(i,1,m) vis[i]=false;
		top=0;
		dfs(k);
		
		while (top) printf("%d ",sta[top--]);
		printf("\n");
	}
	return 0;
}

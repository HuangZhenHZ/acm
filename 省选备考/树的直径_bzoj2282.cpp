#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int N=310000;
const int inf=0x7fffffff;

struct E{ int to,dis,ne; } e[N<<1];
int n,la[N],e_top;

void add(int x, int y, int z){
	e[++e_top]=(E){y,z,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,z,la[y]}; la[y]=e_top;
}

int dis[N], fa[N], fadis[N], q[N], l,r;

int bfs(int x){
	//forto(i,1,n) dis[i]=-1;
	dis[x]=0;
	q[l=r=1]=x;
	int ans=x;

	while (l<=r){
		x=q[l++];
		for(int i=la[x]; i; i=e[i].ne){
			int y=e[i].to, z=e[i].dis;
			if (dis[y]==-1){
				dis[y]=dis[x]+z;
				if (dis[y]>dis[ans]) ans=y;
				fa[y]=x;
				fadis[y]=z;
				q[++r]=y;
			}
		}
	}
	return ans;
}

int lis[N],d[N],f[N],L[N],R[N],top;

int main(){
	int s; scanf("%d%d",&n,&s);
	forto(i,2,n){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	forto(i,1,n) dis[i]=-1;
	int x=bfs(1);
	forto(i,1,n) dis[i]=-1;
	int y=bfs(x);
	
	while (y!=x){
		lis[++top]=y;
		d[top]=fadis[y];
		y=fa[y];
	}
	lis[++top]=x;
	
	forto(i,1,top){
		forto(j,1,n) dis[j]=-1;
		if (i!=1) dis[lis[i-1]]=0;
		if (i!=top) dis[lis[i+1]]=0;
		int t=bfs(lis[i]);
		f[i]=dis[t];
	}
	
	L[1]=f[1];
	forto(i,2,top) L[i]=MAX(L[i-1]+d[i-1],f[i]);
	R[top]=f[top];
	fordown(i,top-1,1) R[i]=MAX(R[i+1]+d[i],f[i]);
	
	//forto(i,1,top) printf("%d %d %d %d %d\n",lis[i],F[i],L[i],R[i],d[i]);
	
	int ans=inf;
	q[l=r=1]=1;
	int j=1;
	forto(i,1,top){
		while (j!=top && d[j]<=s){
			s-=d[j];
			j++;
			while (l<=r && f[q[r]]<=f[j]) r--;
			q[++r]=j;
		}
		int t=MAX(L[i],R[j]);
		t=MAX(t,f[q[l]]);
		if (t<ans) ans=t;
		if (q[l]==i) l++;
		s+=d[i];
	}
	printf("%d",ans);
	return 0;
}


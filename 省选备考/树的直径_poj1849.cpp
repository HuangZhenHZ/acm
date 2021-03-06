#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)

#define maxn 110000

struct E{ int to,dis,ne; } e[maxn*2];
int la[maxn],top;

void add(int x, int y, int z){
	e[++top]=(E){y,z,la[x]}; la[x]=top;
	e[++top]=(E){x,z,la[y]}; la[y]=top;
}

int n, dis[maxn], q[maxn], l,r;

int bfs(int x){
	q[l=r=1]=x;
	forto(i,1,n) dis[i]=-1;
	dis[x]=0;
	int ans=x;
	while (l<=r){
		x=q[l++];
		for(int i=la[x];i;i=e[i].ne){
			int y=e[i].to;
			if (dis[y]==-1){
				dis[y]=dis[x]+e[i].dis;
				if (dis[y]>dis[ans]) ans=y;
				q[++r]=y;
			}
		}
	}
	return ans;
}

int main(){
	int k; scanf("%d%d",&n,&k);
	int sum=0;
	forto(i,2,n){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if (x>n) n=x;
		if (y>n) n=y;
		add(x,y,z);
		sum+=z;
	}
	int x=bfs(1);
	int y=bfs(x);
	//printf("%d %d\n",sum,dis[y]);
	printf("%d",sum*2-dis[y]);
	return 0;
}
		
		
		
		
		
		
		
	

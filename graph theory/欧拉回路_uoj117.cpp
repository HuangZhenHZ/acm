#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=la[x];i;i=e[i].ne)

const int N=100100, M=200200;

struct E{ int to,ne; } e[M<<1];
int t,n,m,la[N],e_top;
int in[N],out[N];

void add(int x, int y){
	out[x]++; in[y]++;
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
}

int sta[M],top;
bool vis[M<<1];

void dfs(int x){
	for(int i=la[x];i;i=la[x]){
		la[x]=e[i].ne;
		if (!vis[i]){
			if (t==1) vis[i]=vis[i^1]=true; else vis[i]=true;
			la[x]=e[i].ne;
		
			dfs(e[i].to);
		
			if (t==1) sta[++top]=(i&1)?(-(i>>1)):(i>>1);
				else sta[++top]=i;
		}
	}
}

int main(){
	scanf("%d",&t);
	scanf("%d%d",&n,&m);
	if (m==0){
		printf("YES");
		return 0;
	}
	
	if (t==1) e_top=1;
	forto(i,1,m){
		int x,y; scanf("%d%d",&x,&y);
		if (t==1){ add(x,y); add(y,x); }
		if (t==2) add(x,y);
	}
	
	if (t==1)
	forto(i,1,n) if (in[i]&1){
		printf("NO");
		return 0;
	}
	
	if (t==2)
	forto(i,1,n) if (in[i]!=out[i]){
		printf("NO");
		return 0;
	}
	
	if (t==1) dfs(e[2].to); else dfs(e[1].to);
	
	if (top!=m){
		printf("NO");
		return 0;
	}
	
	printf("YES\n");
	fordown(i,top,1) printf("%d ",sta[i]);
	return 0;
}

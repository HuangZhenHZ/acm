#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int N=110, M=11000;

struct E{ int to,ne; } e[M];
int la[N],e_top;

inline void add(int a, int b){
	e[++e_top]=(E){b,la[a]}; la[a]=e_top;
}

int scc[N],cnt,time,low[N],pre[N],sta[N],top;

void dfs(int x){
	low[x]=pre[x]=++time; sta[++top]=x;
	for(int i=la[x]; i; i=e[i].ne){
		int y=e[i].to;
		if (!pre[y]) dfs(y);
		if (!scc[y] && low[y]<low[x]) low[x]=low[y];
	}
	if (low[x]==pre[x]){
		cnt++;
		while (!scc[x]) scc[sta[top--]]=cnt;
	}
}

bool cd[N],rd[N];
int a,b;

int main(){
	int n; scanf("%d",&n);
	forto(i,1,n){
		int j; scanf("%d",&j);
		while (j){
			add(i,j);
			scanf("%d",&j);
		}
	}
	forto(i,1,n) if (!pre[i]) dfs(i);
	if (cnt==1){
		printf("1\n0");
		return 0;
	}
	forto(x,1,n)
	for(int i=la[x]; i; i=e[i].ne){
		int y=e[i].to;
		if (scc[x]!=scc[y]){
			cd[scc[x]]=1;
			rd[scc[y]]=1;
		}
	}
	forto(i,1,cnt){
		if (!cd[i]) a++;
		if (!rd[i]) b++;
	}
	printf("%d\n%d",b,MAX(a,b));
	return 0;
}
	


		



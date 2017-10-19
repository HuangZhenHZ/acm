#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for (int i=(a);i<=(b);i++)
#define fordown(i,a,b) for (int i=(a);i>=(b);i--)
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
const int N=200, M=30000;

int la[N],top;
struct edge{int to,next;} e[M];
void add(int a, int b){
	e[++top]=(edge){b,la[a]}; la[a]=top;
	e[++top]=(edge){a,la[b]}; la[b]=top;
}

int pre[N],low[N],time;
bool cut[N];

void dfs(int x, int fa){
	pre[x]=low[x]=++time;
	int ch=0;
	for (int i=la[x];i;i=e[i].next){
		int y=e[i].to;
		if (!pre[y]){
			ch++; dfs(y,x);
			if (low[y]>=pre[x]) cut[x]=true;
			low[x]=MIN(low[x],low[y]);
		}
		else if (y!=fa) low[x]=MIN(low[x],pre[y]);
	}
	if (fa==0 && ch==1) cut[x]=false;
}

int main(){
	int n;
	for (scanf("%d",&n);n;scanf("%d",&n)){
		forto(i,1,n) la[i]=pre[i]=low[i]=cut[i]=0;
		top=time=0;
		
		int x;
		for (scanf("%d",&x);x;scanf("%d",&x))
		while (getchar()!='\n'){
			int y; scanf("%d",&y);
			add(x,y);
		}
		
		dfs(1,0);
		int ans=0;
		forto(i,1,n) ans+=cut[i];
		printf("%d\n",ans);
	}
	return 0;
}

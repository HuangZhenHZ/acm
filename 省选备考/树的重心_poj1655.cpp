#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int inf=0x7fffffff, N=21000;

struct E{ int to,ne; } e[N<<1];
int n,la[N],e_top;

void add(int x, int y){
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,la[y]}; la[y]=e_top;
}

int size[N],max[N];

void dfs(int x){
	size[x]=1;
	max[x]=0;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (size[y]==0){
			dfs(y);
			size[x]+=size[y];
			max[x]=MAX(max[x],size[y]);
		}
	}
}

int main(){
	int t; scanf("%d",&t);
	while (t--){
		scanf("%d",&n);
		
		e_top=0;
		forto(i,1,n) la[i]=0;
		
		forto(i,2,n){
			int x,y; scanf("%d%d",&x,&y);
			add(x,y);
		}
		
		forto(i,1,n) size[i]=max[i]=0;
		dfs(1);
		
		int ans=0, min=inf;
		forto(i,1,n){
			int bal=MAX(n-size[i],max[i]);
			if (bal<min){
				ans=i;
				min=bal;
			}
		}
		
		//forto(i,1,n) printf("%d %d %d\n",i,size[i],max[i]);
		
		printf("%d %d\n",ans,min);
	}
	return 0;
}
			
		
	
		
		
		



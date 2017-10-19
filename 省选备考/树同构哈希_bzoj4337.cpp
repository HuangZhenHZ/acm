#include<cstdlib>
#include<cstdio>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=100;

struct E{ int to,ne; } e[N<<1];
int n,la[N],e_top;

void add(int x, int y){
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,la[y]}; la[y]=e_top;
}

int f[N];

void dfs(int x){
	int a[N], top=0;
	f[x]=0; a[++top]=1;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (f[y]==-1){
			dfs(y);
			a[++top]=f[y];
		}
	}
	std::sort(a+1,a+top+1);
	forto(i,1,top) f[x]=f[x]*10077+a[i];
}

int lis[N];

int gethash(){
	scanf("%d",&n);
	e_top=0;
	forto(i,1,n) la[i]=0;
	forto(i,1,n){
		int j; scanf("%d",&j);
		if (j) add(i,j);
	}
	forto(k,1,n){
		forto(i,1,n) f[i]=-1;
		dfs(k);
		lis[k]=f[k];
	}
	std::sort(lis+1,lis+n+1);
	int ans=0;
	forto(i,1,n) ans=ans*10007+lis[i];
	return ans;
}

int h[N];

int main(){
	int t; scanf("%d",&t);
	forto(i,1,t) h[i]=gethash();
	forto(i,1,t){
		int j=1; while (h[i]!=h[j]) j++;
		printf("%d\n",j);
	}	
	return 0;
}
	

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MAX(a,b) ((a)>(b)?(a):(b))

int n,f[31];

int main(){
	scanf("%d",&n);
	int ans=0;
	while (n--){
		int x; scanf("%d",&x);
		int t=1;
		forto(i,0,30) if (1<<i&x) t=MAX(t,f[i]+1);
		ans=MAX(ans,t);
		forto(i,0,30) if (1<<i&x) f[i]=MAX(f[i],t);
	}
	printf("%d\n",ans);
}
		

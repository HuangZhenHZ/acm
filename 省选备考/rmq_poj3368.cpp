#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
 
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int maxn=100100;

int n,q,a[maxn],f[maxn][20],r[maxn];

inline void rmq(int n){
	for(int i=0,k=1; k<n; k<<=1,i++)
	forto(j,1,n-k) f[j][i+1]=MAX(f[j][i],f[j+k][i]);
}

inline int getrmq(int l, int r){
	int len=r-l+1, i=0, k=1;
	while (k<<1<=len){ k<<=1; i++; }
	return MAX(f[l][i],f[r-k+1][i]);
}

inline int getans(int x, int y){
	if (r[x]>=y) return y-x+1;
	int t=getrmq(r[x]+1,y);
	return MAX(t,r[x]-x+1);
}

int main(){
	while( scanf("%d%d",&n,&q)==2 ){
		forto(i,1,n) scanf("%d",&a[i]);
		f[1][0]=1;
		forto(i,2,n) f[i][0]= a[i]==a[i-1] ? f[i-1][0]+1 : 1;
		r[n]=n;
		fordown(i,n-1,1) r[i]= a[i]==a[i+1] ? r[i+1] : i;
		rmq(n);
		
		while (q--){
			int x,y; scanf("%d%d",&x,&y);
			printf("%d\n",getans(x,y));
		}
	}
	return 0;
}
		
	
	
	

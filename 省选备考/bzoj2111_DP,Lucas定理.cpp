#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef long long LL;
const int N=1100000;

int n,p;
LL fac[N],inv[N];
LL f[N],size[N];

LL C(int n, int m){
	LL ans=1;
	//printf("C(%d,%d)=",n,m);
	while (n||m){
		int a=n%p, b=m%p;
		n/=p; m/=p;
		if (a<b) return 0;
		ans= ans *fac[a]%p *inv[b]%p *inv[a-b]%p;
	}
	//printf("%d\n",int(ans));
	return ans;
}

int main(){
	scanf("%d%d",&n,&p);
	
	int m=MIN(n,p-1);
	fac[0]=1;
	forto(i,1,m) fac[i]=fac[i-1]*i%p;
	inv[1]=1;
	forto(i,2,m) inv[i]=(p-p/i)*inv[p%i]%p;
	inv[0]=1;
	forto(i,1,m) inv[i]=inv[i-1]*inv[i]%p;
	
	fordown(i,n,1){
		if ((i<<1)>n){ f[i]=size[i]=1; }
		if ((i<<1)==n){
			f[i]=f[i<<1];
			size[i]=size[i<<1]+1;
		}
		if ((i<<1)<n){
			size[i]=size[i<<1]+size[i<<1|1]+1;
			f[i]=C(size[i]-1,size[i<<1]) *f[i<<1]%p *f[i<<1|1]%p;
		}
		//printf("f[%d]=%d\n",i,int(f[i]));
	}
	
	//forto(i,1,n) printf("f[%d]=%d\n",i,int(f[i]));
	
	printf("%d",int(f[1]));
	return 0;
}
		
	
	
	
	
	

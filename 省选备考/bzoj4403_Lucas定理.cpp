#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;

const int MOD=1000003;

LL fac[MOD],inv[MOD];

LL C(int n, int m){
	if (n<m) return 0;
	if (n<MOD&&m<MOD) return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
	return C(n/MOD,m/MOD)*C(n%MOD,m%MOD)%MOD;
}	

int main(){
	fac[0]=1;
	forto(i,1,MOD-1) fac[i]=fac[i-1]*i%MOD;
	inv[1]=1;
	forto(i,2,MOD-1) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	inv[0]=1;
	forto(i,1,MOD-1) inv[i]=inv[i-1]*inv[i]%MOD;
	
	int t; scanf("%d",&t);
	while (t--){
		int n,l,r; scanf("%d%d%d",&n,&l,&r);
		int m=r-l+1;
		printf("%d\n",int(C(n+m,n)-1+MOD)%MOD);
	}
	return 0;
}
		
		
		
		
	
	 

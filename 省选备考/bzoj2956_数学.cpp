#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;

const LL MOD=19940417, inv=3323403;

LL cal(LL n, LL a){
	LL ans=0, i=1;
	while (i<=n){
		LL k=a/i, j=a/k;
		if (j>n) j=n;
		ans+=(i+j)*(j-i+1)/2*k;
		ans%=MOD; if (ans<0) ans+=MOD;
		i=j+1;
		//printf("%lld %lld\n",i,j);
	}
	return ans;
}

LL cal1(LL n, LL a){
	LL ans=(n%MOD)*(a%MOD)%MOD;
	ans-=cal(n,a);
	if (ans<0) ans+=MOD;
	return ans;
}	

LL sum(LL n){ return n*(n+1)%MOD *(2*n+1)%MOD *inv%MOD; }

LL cal2(LL n, LL m){
	if (n>m){ LL t=n; n=m; m=t; }
	LL ans=(n%MOD)* (n%MOD)%MOD *(m%MOD)%MOD;
	ans-=n*cal(n,m)+m*cal(n,n);
	//printf("%I64d\n",ans);
	ans%=MOD; if (ans<0) ans+=MOD;
	LL i=1;
	while (i<=n){
		LL kn=n/i, jn=n/kn;
		LL km=m/i, jm=m/km;
		LL k=kn*km, j=jn<jm?jn:jm;
		if (j>n) j=n;
		LL t=sum(j)-sum(i-1);
		t%=MOD; if (t<0) t+=MOD;
		ans+=t*k%MOD;
		ans%=MOD;
		i=j+1;
	}
	return ans;
}

int main(){
	//printf("%I64d\n",cal2(10,10));
	//printf("%I64d",sum(5));
	LL n,m; scanf("%lld%lld",&n,&m);
	//printf("%I64d\n",cal(n,n)*cal(m,m)%MOD);
	printf("%lld",( cal1(n,n)*cal1(m,m)%MOD - cal2(n,m) + MOD )%MOD );
	return 0;
}
	

#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;
const int N=51000;

int c[N],L[N],R[N],lev[N],q[N],f[N];
LL ans[N];

bool comp(int a, int b){ 
	if (lev[a]<lev[b]) return true;
	if (lev[a]>lev[b]) return false;
	return R[a]>R[b];
}

LL gcd(LL a, LL b){
	while (a&&b){
		if (b&&a>=b) a%=b;
		if (a&&b>=a) b%=a;
	}
	return a?a:b;
}	

int main(){
	int n,m; scanf("%d%d",&n,&m);
	forto(i,1,n) scanf("%d",&c[i]);
	forto(i,1,m) scanf("%d%d",&L[i],&R[i]);
	int de=sqrt(n+0.5);
	forto(i,1,m) lev[i]=(L[i]+1)/de+1;
	forto(i,1,m) q[i]=i;
	std::sort(q+1,q+m+1,comp);
	
	int l=1,r=1; LL sum=0;
	f[c[1]]++;
	forto(i,1,m){
		int t=q[i];
		int nl=L[t], nr=R[t];
		while (l>nl) sum+=f[c[--l]]++;
		//printf("sum=%d\n",sum);
		while (r<nr) sum+=f[c[++r]]++;
		//printf("sum=%d\n",sum);
		while (l<nl) sum-=--f[c[l++]];
		//printf("sum=%d\n",sum);
		while (r>nr) sum-=--f[c[r--]];
		//printf("sum=%d\n",sum);
		ans[t]=sum;
		//printf("ans[%d]=%d\n",t,ans[t]);
	}
	
	forto(i,1,m){
		LL x=ans[i], y=R[i]-L[i]+1;
		y=(y*(y-1))>>1;
		//printf("%I64d\n",y);
		LL g=gcd(x,y);
		//printf("%I64d/%I64d\n",x,y);
		//printf("%I64d\n",g);
		printf("%lld/%lld\n",x/g,y/g);
	}
	return 0;
}
		
	
	
	
	
	
	
	
		
			




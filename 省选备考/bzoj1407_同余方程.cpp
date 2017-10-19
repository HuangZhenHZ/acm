#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)

typedef long long LL;
const int N=20;

void gcd(LL a, LL b, LL &d, LL &x, LL &y){
	if (b==0){ d=a; x=1; y=0; return; }
	gcd(b,a%b,d,y,x); y-=x*(a/b);
}

int n;
LL c[N],p[N],l[N];

bool ij_check(int i, int j, LL m){
	LL a=p[i]-p[j], b=c[j]-c[i];
	a%=m; if (a<0) a+=m;
	b%=m; if (b<0) b+=m;
	LL d,x,y; gcd(a,m,d,x,y);
	if (b%d) return true;
	b/=d; m/=d;
	x%=m; if (x<0) x+=m;
	LL ans=b*x%m;
	return ans>l[i]||ans>l[j];
}

bool check(LL m){
	forto(i,1,n-1) forto(j,i+1,n)
		if (!ij_check(i,j,m)) return false;
	return true;
}

int main(){
	scanf("%d",&n);
	forto(i,1,n) scanf("%lld%lld%lld",&c[i],&p[i],&l[i]);
	LL m=0;
	forto(i,1,n) if (c[i]>m) m=c[i];
	while (!check(m)) m++;
	printf("%lld\n",m);
	return 0;
}
		
	
	
	
	

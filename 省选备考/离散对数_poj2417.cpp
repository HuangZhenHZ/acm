#include<cstdio>
#include<cmath>
#include<vector>
#define HASH 32123
using namespace std;
typedef long long LL;

struct hashmap{
	vector<int> a[HASH],b[HASH];
	int get(int x){
		int h=x%HASH;
		for (int i=0;i<a[h].size();i++)
		if (a[h][i]==x) return b[h][i];
		return -1;
	}
	void set(int x,int y){
		int h=x%HASH;
		for (int i=0;i<a[h].size();i++)
		if (a[h][i]==x) {
			b[h][i]=y;
			return;
		}
		a[h].push_back(x);
		b[h].push_back(y);
	}
	void clear(){
		for (int i=0;i<HASH;i++){
			a[i].clear();
			b[i].clear();
		}
	}
} x;
		
void gcd(LL a,LL b,LL &x,LL &y) {
	if (b==0) {x=1; y=0; return; }
	gcd(b,a%b,y,x);
	y-=x*(a/b);
}

LL pow(LL a,LL b,LL n) {
	if (b==0) return 1;
	LL p=pow(a,b>>1,n);
	p=p*p%n;
	if (b&1) p=p*a%n;
	return p;
}

LL inv(LL a,LL n) {
	LL x,y;
	gcd(a,n,x,y);
	if (x<0) x+=n;
	return x;
}

LL log(LL a,LL b,LL n) {
	LL m=(int)sqrt(n+0.5);
	LL p=pow(a,m,n);
	LL v=inv(p,n);
			
	x.clear();
	
	LL e=1; x.set(e,0);
	for (LL i=1;i<m;i++) {
		e=e * a % n;
		if (x.get(e)==-1) x.set(e,i);
	}
	for (LL i=0;i<n;i+=m) {
		if (x.get(b)!=-1) return i+x.get(b);
		b=b * v % n;
	}
	return -1;
}

int main(){
	LL a,b,n;
	while ( scanf("%I64d %I64d %I64d",&n,&a,&b)>0 ){
		LL ans=log(a,b,n);
		if (ans==-1) printf("no solution\n");
			else printf("%I64d\n",ans);
	}
	return 0;
}

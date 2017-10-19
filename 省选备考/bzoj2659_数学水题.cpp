#include<cstdlib>
#include<cstdio>

typedef long long LL;

int main(){
	LL p,q; scanf("%lld%lld",&p,&q);
	if (p==q) printf("%lld",(p+1)*(p-1)/4);
	else printf("%lld",(p-1)*(q-1)/4);
	return 0;
}

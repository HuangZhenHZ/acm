#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long LL;

LL dx(LL x){
	LL s=0;
	for(LL i=1; i*i<=x; i++) if (x%i==0){
		s++;
		if (i*i!=x) s++;
	}
	return s;
}

LL sdx(LL n){
	LL s=0, i=1;
	while (i<=n){
		LL j=n/(n/i);
		s+=(j-i+1)*(n/i);
		i=j+1;
	}
	return s;
}

LL sx(LL x){
	LL s=0;
	for(LL i=1; i*i<=x; i++) if (x%i==0){
		s+=i;
		if (i*i!=x) s+=x/i;
	}
	return s;
}

LL ssx(LL n){
	LL s=0, i=1;
	while (i<=n){
		LL j=n/(n/i);
		s += (i+j)*(j-i+1)/2 * (n/i);  // (n/i)
		//printf("i=%lld j=%lld s=%lld\n",i,j,s);
		i=j+1;
	}
	return s;
}

const int N=100000;

LL d[N+10],sd1[N+10],sd2[N+10];
LL s[N+10],ss1[N+10],ss2[N+10];

int main(){
	//printf("%lld\n",ssx(3));
	
	forto(i,1,N) d[i]=dx(i);
	forto(i,1,N) sd1[i]=sd1[i-1]+d[i];
	forto(i,1,N) sd2[i]=sdx(i);
	forto(i,1,N) if (sd1[i]!=sd2[i]) printf("!");
	
	forto(i,1,N) s[i]=sx(i);
	forto(i,1,N) ss1[i]=ss1[i-1]+s[i];
	forto(i,1,N) ss2[i]=ssx(i);
	forto(i,1,N) if (ss1[i]!=ss2[i]) printf("!");
	putchar('\n');
	
	//forto(i,1,N) printf("%d %lld %lld %lld\n",i,s[i],ss1[i],ss2[i]);
	
	return 0;
}
		
		
	
	

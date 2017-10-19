#include<cstdlib>
#include<cstdio>
#include<cmath>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;
const int N=50000;

int a[N],top,f[N],mo[N];
bool b[N];

void getprime(){
	mo[1]=1;
	forto(i,2,N-1){
		if (b[i]==false){
			a[++top]=i;
			f[i]=top;
			mo[i]=-1;
		}
		forto(j,1,f[i]){
			int t=i*a[j];
			if (t>=N) break;
			b[t]=true;
			f[t]=j;
			if (mo[i] && j!=f[i])
				mo[t]=-mo[i];
		}
	}
}

LL get(LL x){
	LL ans=0; int t=sqrt(x+0.5);
	forto(i,1,t) if (mo[i])
		ans+= x/(i*i)*mo[i];
	return ans;
}

LL getans(int k){
	LL l=1, r=LL(N)*LL(N);
	while (l<r){
		LL m=(l+r)>>1;
		LL t=get(m);
		if (t==k) r=m;
		if (t<k) l=m+1;
		if (t>k) r=m-1;
	}
	return l;
}

int main(){
	getprime();
	int t; scanf("%d",&t);
	while (t--){
		int k; scanf("%d",&k);
		printf("%lld\n",getans(k));
	}
	return 0;
}
	
			
		

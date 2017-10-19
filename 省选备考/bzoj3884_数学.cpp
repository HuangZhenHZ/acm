#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;

int phi(int x){
	int ans=x;
	for(int i=2;i*i<=x;i++)
	if (x%i==0){
		ans=ans/i*(i-1);
		while (x%i==0) x/=i;
	}
	if (x!=1){ ans=ans/x*(x-1); }
	return ans;
}

int pow(int b, int n){
	if (b==0) return 1%n;
	int p=pow(b>>1,n);
	p=LL(p)*LL(p)%n;
	if (b&1) p=LL(p)*LL(2)%n;
	return p;
}

int solve(int p){
	if (p==1) return 0;
	//printf("%d\n",p);
	int k=0;
	while ((p&1)==0){
		p>>=1;
		k++;
		//printf("!!");
	}
	int ph=phi(p);
	int z=solve(ph)-k;
	z%=ph; if (z<0) z+=ph;
	//printf("p=%d\n",p);
	int t=pow(z,p);
	return t<<k;
}

int main(){
	//printf("%d\n",phi(1));
	int t; scanf("%d",&t);
	while (t--){
		int p; scanf("%d",&p);
		printf("%d\n",solve(p));
	}
	return 0;
}

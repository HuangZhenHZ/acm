#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
typedef long long LL;

const int N=2050;

int n,g,k;
LL a[N],s1[N],s2[N];

LL get(int l, int r){
	if (k==1){
		int m=(l+r)>>1;
		LL t1 = a[m]*(m-l) - (s1[m-1]-s1[l-1]);
		LL t2 = (s1[r]-s1[m]) - a[m]*(r-m);
		return t1+t2;
	}
	LL n = r-l+1;
	LL sum1 = s1[r]-s1[l-1];
	LL sum2 = s2[r]-s2[l-1];
	
	LL v = sum1/n;
	LL t1 = n*v*v - 2*sum1*v + sum2;
	v++;
	LL t2 = n*v*v - 2*sum1*v + sum2;
	return min(t1,t2);
}

LL c[N][N],f[N][N];
LL pre[N][N];

void dfs(int t, int l, int r, int mn, int mx){
	int i=(l+r)>>1;
	int p1=max(mn,t-1);
	int p2=min(mx,i-1);
	
	int mj=p1;
	LL ans=f[t-1][mj]+c[mj+1][i];
		
	forto(j,p1+1,p2){
		LL d=f[t-1][j]+c[j+1][i];
		if (d<=ans){
			ans=d;
			mj=j;
		}
	}
	pre[t][i]=mj;
	f[t][i]=ans;
	if (l<i) dfs(t,l,i-1,mn,min(mx,mj));
	if (i<r) dfs(t,i+1,r,max(mn,mj),mx);
}

int main(){
	scanf("%d%d%d",&n,&g,&k);
	forto(i,1,n) scanf("%lld",&a[i]);
	forto(i,1,n) s1[i]=s1[i-1]+a[i];
	forto(i,1,n) s2[i]=s2[i-1]+a[i]*a[i];
	forto(l,1,n) forto(r,l,n) c[l][r]=get(l,r);
	
	forto(i,1,n) f[1][i]=c[1][i];
	forto(t,2,g) dfs(t,t,n,t-1,n-1);
	
	//forto(t,2,g){
	//	int j=t-1;
	//	forto(i,t,n){
	//		while (j+1<i && f[t-1][j]+c[j+1][i] >= f[t-1][j+1]+c[j+2][i]) j++;
	//		f[t][i] = f[t-1][j]+get(j+1,i);
	//	}
	//}
	
	printf("%lld\n",f[g][n]);
	return 0;
}
	


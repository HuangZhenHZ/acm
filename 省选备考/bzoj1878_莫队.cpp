#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=51000,M=210000;

int a[N],L[M],R[M],lev[M],q[M],f[1100000],ans[M];

bool comp(int x, int y){
	if (lev[x]<lev[y]) return true;
	if (lev[x]>lev[y]) return false;
	return R[x]<R[y];
}

int main(){
	int n; scanf("%d",&n);
	forto(i,1,n) scanf("%d",&a[i]);
	int m; scanf("%d",&m);
	int de=sqrt(n+0.5);
	forto(i,1,m){
		scanf("%d%d",&L[i],&R[i]);
		lev[i]=(L[i]-1)/de+1;
		q[i]=i;
	}
	std::sort(q+1,q+m+1,comp);
	
	int l=1,r=1,sum=1;
	f[a[1]]++;
	forto(i,1,m){
		int t=q[i];
		int nl=L[t],nr=R[t];
		while (l>nl) if (f[a[--l]]++==0) sum++;
		while (r<nr) if (f[a[++r]]++==0) sum++;
		while (l<nl) if (--f[a[l++]]==0) sum--;
		while (r>nr) if (--f[a[r--]]==0) sum--;
		ans[t]=sum;
	}
	forto(i,1,m) printf("%d\n",ans[i]);
	
	return 0;
}
		
	
	

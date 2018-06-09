#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;

const int N=1550;

int n,m;
bitset<N> a[N];

bool solve(){
	int i=1, j=1;
	
	while (i<=n && j<=m){
		int k=i;
		while (k<=n && !a[k][j]) k++;
		if (k>n) { j++; continue; }
		if (k!=i) swap(a[i],a[k]);
		
		if (j==m) return false;
		forto(t,1,n) if (t!=i && a[t][j]) a[t]^=a[i];
		i++; j++;
	}
	return true;
}

int main(){
	scanf("%d%d",&n,&m);
	forto(i,1,n){
		forto(j,1,m){
			int x; scanf("%d",&x);
			a[j][i]=x&1;
		}
		a[m+1][i]=1;
	}
	swap(n,m);
	a[++n][++m]=1;
	
	printf(!solve()?"Yes\n":"No\n");
	return 0;
}

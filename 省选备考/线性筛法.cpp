#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
const int maxn=100000;

bool b[maxn+100];
int a[maxn+100],cnt;
int m[maxn+100],phi[maxn+100];

void getprime(){
	forto(i,2,maxn) b[i]=true;
	forto(i,2,maxn){
		if (b[i]){
			a[++cnt]=i;
			m[i]=cnt; phi[i]=i-1;
		}
		for(int j=1;j<=m[i]&&i*a[j]<=maxn;j++){
			int k=i*a[j];
			b[k]=false; m[k]=j;
			phi[k]= j==m[i] ? phi[i]*a[j] : phi[i]*(a[j]-1);
		}
	}
}

int main(){
	getprime();
	forto(i,1,30) printf("%d\n",phi[i]);
	return 0;
}


#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define ABS(a) ((a)>=0?(a):-(a))
const int maxn=20;

double s[maxn][maxn];
double a[maxn][maxn];
int n;

void gauss(){
	forto(i,1,n){
		int k=i;
		forto(j,i+1,n) if (ABS(a[j][i])>ABS(a[k][i])) k=j;
		if (i!=k) forto(j,1,n+1) { double t=a[i][j]; a[i][j]=a[k][j]; a[k][j]=t; }
		
		forto(j,1,n) if (j!=i){
			double t=a[j][i]/a[i][i];
			forto(k,1,n+1) a[j][k]-=a[i][k]*t;
		}
	}
}
	
int main(){
	scanf("%d",&n);
	forto(i,1,n+1) forto(j,1,n) scanf("%lf",&s[i][j]);
	
	forto(i,1,n)
	forto(j,1,n){
		a[i][n+1]-=s[i][j]*s[i][j];
		a[i][n+1]+=s[i+1][j]*s[i+1][j];
		a[i][j]-=2*s[i][j];
		a[i][j]+=2*s[i+1][j];
	}
	
//	forto(i,1,n){
//		forto(j,1,n+1) printf("%lf ",a[i][j]);
//		printf("\n");
//	}
	
	gauss();
	forto(i,1,n-1) printf("%0.3lf ",a[i][n+1]/a[i][i]);
	printf("%0.3lf",a[n][n+1]/a[n][n]);
	return 0;
}

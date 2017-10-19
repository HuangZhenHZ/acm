#include<cstdlib>
#include<cstdio>
#include<cmath>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
const int maxn=200100;
const double pi=acos(-1);

struct P{double x,y;};
P operator+ (const P&a, const P&b){ return (P){a.x+b.x, a.y+b.y}; }
P operator- (const P&a, const P&b){ return (P){a.x-b.x, a.y-b.y}; }
P operator* (const P&a, const P&b){ return (P){a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x}; }

int rev[maxn];
P w1[maxn],w2[maxn];

void initfft(int n){
	int k=0,nn=n>>1;
	while (nn){ nn>>=1; k++; }
	double t=pi*2/n;
	forto(i,0,n-1){
		rev[i]=(rev[i>>1]>>1)+((i&1)<<(k-1));
		w1[i]=w2[n-i]=(P){cos(t*i),sin(t*i)};
	}
}
	
void fft(int n, P a[], P w[]){
	forto(i,0,n-1)
	if (i>rev[i]){
		P t=a[i]; a[i]=a[rev[i]]; a[rev[i]]=t;
	}
	for (int k=1;k<n;k++)
	for (int i=0;i<n;i+=k<<1)
	for (int j=0;j<k;j++){
		P t=a[i+j]*w[n/(k<<1)*j];
		a[i+j]=a[i+j]+t;
		a[i+j+k]=a[i+j+k]-t;
	}
}	

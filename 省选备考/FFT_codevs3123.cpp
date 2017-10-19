#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
const int maxn=300000;
const double pi=acos(-1);

struct P{ double x,y; };
P operator+ (const P &a, const P &b) { return (P){a.x+b.x, a.y+b.y}; }
P operator- (const P &a, const P &b) { return (P){a.x-b.x, a.y-b.y}; }
P operator* (const P &a, const P &b) { return (P){a.x*b.x-a.y*b.y, a.x*b.y+b.x*a.y}; }

P w1[maxn],w2[maxn];
int rev[maxn];

//void initfft(int n){
//	int k=0; for(int i=1;i<n;i<<=1) k++;
//	double p=pi*2/n;
//	forto(i,0,n-1) rev[i]=(rev[i>>1]>>1)+((i&1)<<k);
//	forto(i,0,n<<=1){
//		double c=cos(p*i), s=sin(p*i);
//		w1[i]=(P){c,s}; w2[i]=(P){c,-s};
//	}
//}

void initfft(int n){
	int k=0,nn=n>>1;
	while (nn){ nn>>=1; k++; }
	double t=pi*2/n;
	forto(i,0,n-1){
		rev[i]=(rev[i>>1]>>1)+((i&1)<<(k-1));
		w1[i]=w2[(n-i)%n]=(P){cos(t*i),sin(t*i)};
	}
}

void fft(int n, P a[], P w[]){
	forto(i,0,n-1) if (i<rev[i]) { P t=a[i]; a[i]=a[rev[i]]; a[rev[i]]=t; }
	for(int k=1;k<n;k<<=1)
	for(int i=0;i<n;i+=k<<1)
	for(int j=0;j<k;j++){
		P t1=a[i+j], t2=a[i+j+k]*w[n/(k<<1)*j];
		a[i+j]=t1+t2; a[i+j+k]=t1-t2;
	}
}

char sa[maxn],sb[maxn];
P a[maxn],b[maxn];
int c[maxn];

int main(){
	scanf("%s",sa);
	scanf("%s",sb);
	int la=strlen(sa), lb=strlen(sb);
	forto(i,0,la-1) a[i].x=double(sa[la-1-i]-'0');
	forto(i,0,lb-1) b[i].x=double(sb[lb-1-i]-'0');
	
	int n=1;
	while (n<la || n<lb) n<<=1;
	n<<=1;
	
	initfft(n);	
	fft(n,a,w1);
	fft(n,b,w1);
	forto(i,0,n-1) a[i]=a[i]*b[i];
	
	fft(n,a,w2);
	forto(i,0,n-1) c[i]=round(a[i].x/n);
	
//	printf("%d\n",n);
//	forto(i,0,n-1) printf("%d ",c[i]);
//	printf("\n");
	
	n=la+lb-1;
	forto(i,0,n-1){
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	if (c[n]) n++;
	
//	forto(i,0,n-1) printf("%d ",c[i]);
//	printf("\n");
	
	fordown(i,n-1,0) printf("%d",c[i]);
	return 0;
}

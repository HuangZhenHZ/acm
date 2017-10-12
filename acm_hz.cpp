#include <bits/stdc++.h>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<=(b)?(a):(b))
#define MAX(a,b) ((a)>=(b)?(a):(b))

#define cmin(a,b) ((a)<=(b)?(a):(a)=(b))
#define cmax(a,b) ((a)>=(b)?(a):(a)=(b))

#define ABS(x) ((x)>=0?(x):-(x))

#define IL inline
#define OP operator

typedef long long LL;
typedef double D;

// Fast getchar
char B[1<<20],*S=B,*T=B;
#define getchar() (S==T&&(T=(S=B)+fread(B,1,1<<20,stdin),S==T)?0:*S++)

// Fast putchar
char U[1<<20|1],*O=U,*W=U+(1<<20);
#define putchar(c) (O==W?fwrite(U,1,1<<20,stdout),O=U,1:1,*O++=(c))
#define clear_buffer() fwrite(U,1,O-U,stdout)

// Fast Input
#define isd(c) ((c)>='0'&&(c)<='9')
IL char read(int &x){
	static char c; static bool f;
	x=0; c=getchar(); f=false;
	while (!isd(c) && c!='-') c=getchar();
	if (c=='-') { f=true; c=getchar(); }
	while (isd(c)) { x=x*10+c-'0'; c=getchar(); }
	if (f) x=-x;
	return c;
}

IL char read(D &x){
	static char c; static bool f;
	x=0; c=getchar(); f=false;
	while (!isd(c) && c!='-' && c!='.') c=getchar();
	if (c=='-') { f=true; c=getchar(); }
	while (isd(c)) { x=x*10+c-'0'; c=getchar(); }
	if (c=='.') {
		static D t; t=1; c=getchar();
		while (isd(c)) { x+=(t/=10)*(c-'0'); c=getchar(); }
	}
	if (f) x=-x;
	return c;
}

IL void read(char s[]){
	s++; *s=getchar();
	while (*s==' '||*s=='\n') *s=getchar();
	while (*s!=' '&&*s!='\n') *++s=getchar();
	*++s=0;
}

// Fast Output
IL void write(int x){
	if (x<0) { putchar('-'); x=-x; }
	if (!x) { putchar('0'); return; }
	static char c[20]; static int top; top=0;
	while (x) { c[++top]='0'+x%10; x/=10; }
	while (top) putchar(c[top--]);
}

IL void write(D x){
	static LL t; t=int(x*1e6+(x>=0?0.5:-0.5));
	if (t<0) { putchar('-'); t=-t; }
	static char c[20]; static int top; top=0;
	while (t) { c[++top]='0'+t%10; t/=10; }
	while (top<=6) c[++top]='0';
	while (top>6) putchar(c[top--]);
	putchar('.');
	while (top) putchar(c[top--]);
}

IL void write(char s[]){
	s++; while (*s) putchar(*s++);
}


const int H=(1<<20)-1;
struct hash_map{
	int la[1<<20],top;
	struct E { LL key; int da,ne; } e[int(1e6)];
	IL void clear(){
		memset(la,0,sizeof(la)); top=0;
	}
	IL bool count(LL k){
		static int i; i=la[k&H];
		while (i&&e[i].key!=k) i=e[i].ne;
		return i;
	}
	IL int& OP[] (LL k){
		static int h,i; i=la[h=k&H];
		while (i&&e[i].key!=k) i=e[i].ne;
		if (!i){ e[i=++top]=(E){k,0,la[h]}; la[h]=top; }
		return e[i].da;
	}
};


IL int pow(int a, LL b, int n){  //a^b mod n
    static int p; p=1;
    for(;b;b>>=1,a=LL(a)*a%n)
		if (b&1) p=LL(p)*a%n;
    return p;
}

IL LL gcd(LL a, LL b){
	static LL c;
	while (b) { c=a%b; a=b; b=c; }
	return a;
}

IL LL lcm(LL a, LL b) { return a/gcd(a,b)*b; } 

void gcd(LL a, LL b, LL &d, LL &x, LL &y){
	if (!b){ d=a; x=1; y=0; return; }
	gcd(b,a%b,d,y,x); y-=x*(a/b);
}

IL void sim(LL &a, LL n){ a%=n; if (a<0) a+=n; }

IL LL solve(LL a, LL b, LL n){  // a*x==b (mod n)
	sim(a,n); sim(b,n);  // optional
	static LL d,x,y; gcd(a,n,d,x,y);
	if (b%d) return -1;
	b/=d; n/=d;
	if (x<0) x+=n;
	return b*x%n;
}

// x==a1 (mod n1); x==a2 (mod n2);
void merge(LL a1, LL n1, LL a2, LL n2, LL &x, LL &n){
	n=n1/gcd(n1,n2)*n2;
	LL k=solve(n1,a2-a1,n2);	
	if (k==-1){ x=-1; return; }
	sim(x=n1*k+a1,n);
}

// Linear sieve method
const int N=100000;
bool b[N+10];
int a[N+10],cnt,mx[N+10],phi[N+10],mu[N+10];

void getprime(){
	forto(i,2,N) b[i]=true;
	mu[1]=1;
	forto(i,2,N){
		if (b[i]){
			a[++cnt]=i;
			mx[i]=cnt; phi[i]=i-1; mu[i]=-1;
		}
		for(int j=1; j<=mx[i]&&i*a[j]<=N; j++){
			int k=i*a[j];
			b[k]=false; mx[k]=j;
			phi[k]= j==mx[i] ? phi[i]*a[j] : phi[i]*(a[j]-1);
			mu[k]= j==mx[i] ? 0 : -mu[i];
		}
	}
}


int main(){
	return 0;
}








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
char U[1<<20],*O=U,*W=U+(1<<20);
#define putchar(c) (O==W?fwrite(U,1,1<<20,stdout),O=U,1:1,*O++=(c))
#define clr_buf() (fwrite(U,1,O-U,stdout),O=U)
// remember to clr_buf() before return 0 in the end

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
	*s=0;
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

// hash_map ( hash_table )
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

// Math Basics
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

// getinv , gcd(a,n) must be 1
IL LL getinv(LL a, LL n){
	static LL d,x,y;
	gcd(a,n,d,x,y);
	// if (d!=1) return -1;
	return x<0?x+n:x;
}

// BSGS , a^x==b (mod n) , n is a prime
LL bsgs(LL a, LL b, LL n){
	LL m=(int)sqrt(n+0.5);
	LL p=pow(a,m,n); LL v=getinv(p,n);
	static hash_map x;
	x.clear();
	LL e=1; x[e]=0;
	for(LL i=1;i<=m;i++){
		e=e*a%n;
		if (!x.count(e)) x[e]=i;
	}
	for(LL i=0;i<n;i+=m){
		if (x.count(b)) return i+x[b];
		b=b*v%n;
	}
	return -1;
}

// Lucas
const int MOD=2333;
LL fac[MOD],inv[MOD];

void init_Lucas(){
	fac[0]=1; forto(i,1,MOD-1) fac[i]=fac[i-1]*i%MOD;
	inv[1]=1; forto(i,2,MOD-1) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	inv[0]=1; forto(i,1,MOD-1) inv[i]=inv[i-1]*inv[i]%MOD;
}

IL LL C(int n, int m){
	LL ans=1;
	while (n||m){
		int a=n%MOD, b=m%MOD;
		n/=MOD; m/=MOD;
		if (a<b) return 0;
		ans= ans *fac[a]%MOD *inv[b]%MOD *inv[a-b]%MOD;
	}
	return ans;
}

// next[1]=0; kmp(s+1, next+1, s, next);
void kmp(char s1[], int next1[], char s2[], int next2[]){
	for(int i=1,j=0; s1[i]; i++){
        while (j && s1[i]!=s2[j+1]) j=next2[j];
        if (s1[i]==s2[j+1]) j++;
        next1[i]=j;
    }
}

// extkmp(s+1, ext+1, s, ext);
void extkmp(char s1[], int ext1[], char s2[], int ext2[]){
	int len1=strlen(s1+1), len2=strlen(s2+1);
	int k=1, j=0;
	while (s1[j+1]==s2[j+1]&&j<len1) j++;
	ext1[1]=j;
	for (int i=2;i<=len1;i++){
		int len=ext2[i-k+1];
		if (i+len-1<j) ext1[i]=len;
		else {
			len=j-i+1;
			if (len<0) len=0;
			while (s1[i+len]==s2[len+1]&& len<len2) len++;
			ext1[i]=len;
			k=i; j=i+len-1;
		}
	}
}

// suffix_array
int n,sa[N],rk[N<<1],c[N],x[N],h[N];
void suffix_array(int s[]){
	forto(i,1,n){ sa[i]=i; rk[i]=s[i]; }
	for(int m=300,k=0; k<n; k?k<<=1:k++){
		forto(i,1,m) c[i]=0;
		forto(i,1,n) c[rk[i]]++;
		forto(i,2,m) c[i]+=c[i-1];
		int p=0;
		forto(i,n-k+1,n) x[++p]=i;
		forto(i,1,n) if (sa[i]>k) x[++p]=sa[i]-k;
		fordown(i,n,1) sa[c[rk[x[i]]]--]=x[i];
		m=1; x[sa[1]]=1;
		forto(i,2,n) x[sa[i]]= rk[sa[i]]==rk[sa[i-1]] && rk[sa[i]+k]==rk[sa[i-1]+k] ?m:++m;
		forto(i,1,n) rk[i]=x[i];
		if (m==n) break;
	}
	forto(i,1,n) if (rk[i]!=n){
		int j=sa[rk[i]+1];
		h[i]=h[i-1]?h[i-1]-1:0;
		while (s[i+h[i]]==s[j+h[i]]) h[i]++;
	}
}

int main(){
	char s[1000];
	int next[1000];
	read(s);
	//for(int i=1; s[i]; i++) printf("%d ",s[i]);
	//printf("\n");
	//printf("%s\n",s+1);
	extkmp(s+1,next+1,s,next);
	for(int i=1; s[i]; i++) printf("%d ",next[i]);
	//clr_buf();
	return 0;
}








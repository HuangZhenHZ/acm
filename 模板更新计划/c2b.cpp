#include <bits/stdc++.h>
#define ft(i,a,b) for(int i=(a); i<=(b); ++i)
#define fd(i,a,b) for(int i=(a); i>=(b); --i)
#define fe(i,x) for(int i=la[x]; i; i=e[i].ne)
#define fv(i,v) for(size_t i=0; i<(v).size(); ++i)
#define TT template <class T>
#define IL inline
TT IL T &cmin(T &x, T y) { return x>y?x=y:x; }
TT IL T &cmax(T &x, T y) { return x<y?x=y:x; }
#define OP operator
#define PB push_back
#define MP make_pair
#define F first
#define S second
typedef long long LL;
typedef double D;
const D pi=acos(-1), eps=1e-8;
int dcmp(D x) { return x>-eps ? x>eps : -1; }
int dcmp(D x, D y) { return dcmp(x-y); }
// relative error : (x-y)/max(1,max(x,y))
using namespace std;
typedef map<int,int>::iterator IT;
#define RI(x) scanf("%d",&(x))
#define RL(x) scanf("%lld",&(x))
#define RD(x) scanf("%lf",&(x))
#define PI(x) printf("%d",(x))
#define PL(x) printf("%lld",(x))
#define PD(x) printf("%lf",(x))
#define PC putchar
#define PS PC(' ')
#define PN PC('\n')

//#define hz_debug
#ifdef hz_debug
	#define DB(s,x) cout<<"DB "<<(s)<<' '<<(x)<<endl
#else
	#define DB(s,x) {}
#endif
// begin

const int N=200050;

vector<int> g[N];
bool del[N];
int sz[N],mxsz[N];
int sta[N],top;

void getsz(int x, int f){
	sz[x]=1; mxsz[x]=0;
	sta[++top]=x;
	fv(i,g[x]){
		int y=g[x][i];
		if (del[y]||y==f) continue;
		getsz(y,x);
		sz[x]+=sz[y];
		cmax(mxsz[x],sz[y]);
	}
}

int getroot(int x){
	top=0; getsz(x,0);
	int n=sz[x], bx=mxsz[x];
	ft(i,1,top){
		int y=sta[i];
		int by=max(mxsz[y],n-sz[y]);
		if (by<bx) bx=by, x=y;
	}
	return x;
}

int fa[N];

void solve(int x, int f){
	x=getroot(x);
	del[x]=true;
	fa[x]=f;
	fv(i,g[x]){
		int y=g[x][i];
		if (del[y]) continue;
		solve(y,x);
	}
}	

int main(){
	//freopen("input.txt","r",stdin);
	int n; RI(n);
	DB("n",n);
	ft(i,2,n){
		int x,y; RI(x); RI(y);
		g[x].PB(y);
		g[y].PB(x);
	}
	solve(1,0);
	ft(i,1,n){
		PI(fa[i]);
		if (i==n) PN; else PS;
	}
	return 0;
}


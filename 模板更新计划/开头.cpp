#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a); i<=(b); ++i)
#define fordown(i,a,b) for(int i=(a); i>=(b); --i)
#define forE(i,x) for(int i=la[x]; i; i=e[i].ne)
#define forv(i,v) for(size_t i=0; i<(v).size(); ++i)
template <class T> T &cmin(T &x, T y) { return x>y?x=y:x; }
template <class T> T &cmax(T &x, T y) { return x<y?x=y:x; }
#define IL inline
#define OP operator
#define MP make_pair
#define PB push_back
#define F first
#define S second
typedef long long LL;
typedef double D;
const D pi=acos(-1), eps=1e-8;
int dcmp(D x) { return x>-eps ? x>eps : -1; }
int dcmp(D x, D y) { return dcmp(x-y); }
// relative error : (x-y)/max(1,max(x,y))
typedef map<int,int>::iterator IT;
using namespace std;

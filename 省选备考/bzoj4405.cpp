#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=200, M=200;

struct E{ int to,ne; } e[M<<1];
int la[N],e_top;

void add(int x, int y){
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,la[y]}; la[y]=e_top;
}

int fa[N];
void gf(int x){ return fa[x]==x?x:fa[x]=find(fa[x]); }

int f[N],vis[N],sta[N],top;

void 



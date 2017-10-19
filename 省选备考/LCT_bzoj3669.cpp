#include<cstdlib>
#include<cstdio>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=150000+100, M=100000+100, inf=0x7fffffff;

int fa[N],ch[N][2],w[N],mx[N];
bool rev[N];

bool ir(int x){ return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x; }
bool nt(int x){ return ch[fa[x]][1]==x; }

void pd(int x){
	if (rev[x]){
		rev[x]=false;
		rev[ch[x][0]]^=1; rev[ch[x][1]]^=1;
		int t=ch[x][0]; ch[x][0]=ch[x][1]; ch[x][1]=t;
	}
}

void ud(int x){
	mx[x]=x;
	if (w[mx[ch[x][0]]]>w[mx[x]]) mx[x]=mx[ch[x][0]];
	if (w[mx[ch[x][1]]]>w[mx[x]]) mx[x]=mx[ch[x][1]];
}

void rtt(int x){
	int y=fa[x], z=fa[y]; bool p=nt(x);
	if (!ir(y)) ch[z][nt(y)]=x;
	fa[ch[x][!p]]=y; fa[y]=x; fa[x]=z;
	ch[y][p]=ch[x][!p]; ch[x][!p]=y; 
	ud(y);
}

void splay(int x){
	static int sta[N],top,y;
	sta[top=1]=y=x;
	while (!ir(y)) sta[++top]=y=fa[y];
	while (top) pd(sta[top--]);
	while (!ir(x)){
		int y=fa[x];
		if (!ir(y)) rtt(nt(x)^nt(y)?x:y);
		rtt(x);
	}
	ud(x);
}

void access(int x){
	int t=0,y=x;
	while (x){
		splay(x);
		ch[x][1]=t; ud(x);
		t=x; x=fa[x];
	}
	splay(y);
}

void makeroot(int x){
	access(x);
	rev[x]^=1;
}

void link(int x, int y){
	makeroot(x);
	fa[x]=y;
	//printf("link(%d,%d)\n",x,y);
}

void cut(int x, int y){
	makeroot(x);
	access(y);
	ch[y][0]=fa[x]=0;
	//printf("cut(%d,%d)\n",x,y);
}

bool check(int x, int y){
	makeroot(x);
	makeroot(y);
	return fa[x];
}

int query(int x, int y){
	makeroot(x);
	access(y);
	return mx[y];
}

struct E{ int x,y,a,b; } e[M];
int s[M];
bool comp(int l, int r){ return e[l].a<e[r].a; }

int main(){
	int n,m; scanf("%d%d",&n,&m);
	forto(i,1,m) scanf("%d%d%d%d",&e[i].x,&e[i].y,&e[i].a,&e[i].b);
	forto(i,1,m) s[i]=i;
	std::sort(s+1,s+m+1,comp);
	
	//printf("!!\n");
	
	int ans=inf;
	forto(i,1,m){
		int t=s[i], x=e[t].x, y=e[t].y, a=e[t].a, b=e[t].b;
		if (x==y) continue;
		
		//printf("i=%d t=%d\n",i,t);
		
		w[n+t]=b; mx[n+t]=n+t;
		if (check(x,y)){
			int q=query(x,y);
			if (b<w[q]){
				
				//printf("w[%d]=%d\n",q,w[q]);
				
				cut(q,e[q-n].x);
				cut(q,e[q-n].y);
				link(n+t,x);
				link(n+t,y);
			}
		} else {
			link(n+t,x);
			link(n+t,y);
		}
		
		if (check(1,n)){
			int q=query(1,n);
			if (a+w[q]<ans) ans=a+w[q];
			//printf("a=%d w[%d]=%d\n",a,q,w[q]);
			//forto(i,1,n+m) printf("fa[%d]=%d nt[%d]=%d ir[%d]=%d\n",i,fa[i],i,nt(i),i,ir(i));
		}
		
		//printf("ans=%d\n\n",ans);
	}
	
	//printf("!!\n");
	printf("%d",ans!=inf?ans:-1);
	return 0;
}
	
	
	
	




	



		
		
		
	
	





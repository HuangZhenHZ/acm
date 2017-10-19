#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=10000000;

int lc[N],rc[N],f[N],top;

int get(int x, int l, int r, int t){
	if (l==r) return f[x];
	int m=(l+r)>>1;
	if (t<=m) return get(lc[x],l,m,t);
	return get(rc[x],m+1,r,t);
}

int change(int x, int l, int r, int t, int d){
	if (l==r){
		f[++top]=d;
		return top;
	}
	int y=++top; lc[y]=lc[x]; rc[y]=rc[x];
	int m=(l+r)>>1;
	if (t<=m) lc[y]=change(lc[y],l,m,t,d);
		else rc[y]=change(rc[y],m+1,r,t,d);
	return y;
}

void build(int x, int l, int r){
	if (l==r){ f[x]=l; return; }
	int m=(l+r)>>1;
	build(lc[x]=++top,l,m);
	build(rc[x]=++top,m+1,r);
}
	
int a[200100],n,m;

int find(int i, int x){
	int fx=get(a[i],1,n,x);
	if (x==fx) return x;
	fx=find(i,fx);
	a[i]=change(a[i],1,n,x,fx);
	return fx;
}

int main(){
	scanf("%d%d",&n,&m);
	build(++top,1,n);
	a[0]=1;
	int lastans=0;
	
	//forto(i,1,top) printf("rc[%d]=%d\n",i,rc[i]);
	//forto(i,1,n) printf("get(%d)=%d\n",i,get(a[0],1,n,i));
	//printf("%d\n",m);
	
	forto(i,1,m){
		int t; scanf("%d",&t);
		if (t==1||t==3){
			int x,y; scanf("%d%d",&x,&y);
			x^=lastans; y^=lastans;
			a[i]=a[i-1];
			x=find(i,x); y=find(i,y);
	
			if (t==1) a[i]=change(a[i],1,n,x,y);
			if (t==3){
				int lastans=(x==y);
				printf("%d\n",lastans);
			}
		}
		if (t==2){
			int k; scanf("%d",&k); k^=lastans;
			a[i]=a[k];
		}
		//printf("a[%d]=%d\n",i,a[i]);
	}
	return 0;
}
	
	
	
		


	







#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=la[x];i;i=e[i].ne)
#define add(x,y) { e[++e_top]=(E){y,la[x]}; la[x]=e_top; }

const int N=550;

struct E{ int to,ne; } e[N*N];
int n,m,la[N],e_top;

int f[N];
int find(int x){ return f[x]==x?x:f[x]=find(f[x]); }

int mat[N],pre[N],cond[N],q[N],l,r;

int vis[N],vt;
int lca(int x, int y){
	vt++; x=find(x); y=find(y);
	while (vis[x]!=vt){
		if (x){ vis[x]=vt; x=find(pre[mat[x]]); }
		int z=x; x=y; y=z;
	}
	return x;
}

void blossom(int x, int y, int g){
	while (find(x)!=g){
		pre[x]=y;
		if (cond[mat[x]]==1) cond[q[++r]=mat[x]]=0;
		if (f[x]==x) f[x]=g;
		if (f[mat[x]]==mat[x]) f[mat[x]]=g;
		y=mat[x]; x=pre[y];
	}
}

int match(int s){
	forto(i,1,n){ cond[i]=-1; pre[i]=0; f[i]=i; }
	cond[q[l=r=1]=s]=0;
	while (l<=r){
		int x=q[l++];
		forE(i,x){
			int y=e[i].to;
			if (cond[y]==-1){
				if (mat[y]==0){
					while (x){
						int t=mat[x];
						mat[x]=y; mat[y]=x;
						y=t; x=pre[y];
					}
					return true;
				}
				cond[y]=1; pre[y]=x;
				cond[q[++r]=mat[y]]=0;
			} else if (find(x)!=find(y) && cond[y]==0){
				int g=lca(x,y); blossom(x,y,g); blossom(y,x,g);
			}
		}
	}
	return false;
}

int main(){
	scanf("%d%d",&n,&m);
	int ans=0;
	while (m--){
		int x,y; scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	forto(i,1,n) if (!mat[i]&&match(i)) ans++;
	printf("%d\n",ans);
	forto(i,1,n) printf("%d ",mat[i]);
	return 0;
}

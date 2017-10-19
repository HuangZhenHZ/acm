#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x,y) for(int i=la[x],y=e[i].to; i; i=e[i].ne,y=e[i].to)

#define get(i,j) (((i)-1)*mm+(j))

const int N=2600,M=11000;

struct E{ int to,ne; } e[M<<1];
int n,la[N],e_top;
char s[60][60];
int nn,mm,r,c;

void add(int i1, int j1, int i2, int j2){
	if (s[i1][j1]=='x'||s[i2][j2]=='x') return;
	int x=get(i1,j1), y=get(i2,j2);
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
}

int f[N];
int vis[N],vt;

bool dfs(int x){
	forE(i,x,y) if (vis[y]!=vt){
		vis[y]=vt;
		if (f[y]==0||dfs(f[y])){
			f[y]=x;
			return true;
		}
	}
	return false;
}

int main(){
	scanf("%d%d%d%d",&nn,&mm,&r,&c);
	n=nn*mm;
	forto(i,1,nn) scanf("%s",s[i]+1);
	//forto(i,1,nn) printf("%s\n",s[i]+1);
	
	forto(i,1,nn-r) forto(j,1,mm-c) add(i,j,i+r,j+c);
	forto(i,1,nn-r) forto(j,c+1,mm) add(i,j,i+r,j-c);
	forto(i,1,nn-c) forto(j,1,mm-r) add(i,j,i+c,j+r);
	forto(i,1,nn-c) forto(j,r+1,mm) add(i,j,i+c,j-r);
	
	int sum=0, ans=0;
	forto(i,1,nn) forto(j,1,mm) if (s[i][j]=='.') sum++;
	
	forto(i,1,n){
		vt++;
		if (dfs(i)) ans++;
	}
	
//	forto(x,1,n){
//		forE(i,x,y) printf("%d ",y);
//		printf("\n");
//	}
	//forto(i,1,n) printf("f[%d]=%d\n",i,f[i]);
	
	//printf("%d %d\n",sum,ans);
	
	printf("%d\n",sum-ans);
	return 0;
}


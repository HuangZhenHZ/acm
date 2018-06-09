#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;

const int N=1050;

char s[N][N];
int a[N*N][4];

int get(int x, int y, int z){
	int i=0;
	while (a[y][i]!=x) i++;
	return a[y][(i+z)%4];
}

void move(int &x, int &y, int z){
	z=get(x,y,z);
	x=y; y=z;
}

void change(int x1, int y1, int y2){
	int i=0;
	while (a[x1][i]!=y1) i++;
	a[x1][i]=y2;
}

int in[4][N],out[4][N];
int ans[N][N];

int main(){
	int n,q; scanf("%d%d",&n,&q);
	forto(i,1,n) scanf("%s",s[i]+1);
	n+=2;
	forto(i,1,n*n){
		if (i>n) a[i][0]=i-n;
		if (i%n) a[i][1]=i+1;
		if (i+n<=n*n) a[i][2]=i+n;
		if (i%n!=1) a[i][3]=i-1;
	}
	while (q--){
		int I,J,S; scanf("%d%d%d",&I,&J,&S);
		int x=1, y=2;
		forto(i,2,J) move(x,y,2);
		move(x,y,3);
		forto(i,2,I) move(x,y,2);
		
		forto(k,0,3){
			in[k][1]=y;
			out[k][1]=get(x,y,3);
			forto(i,2,S){
				move(x,y,2);
				in[k][i]=y;
				out[k][i]=get(x,y,3);
			}
			move(x,y,3);
			swap(x,y);
		}
		forto(i,0,3) forto(j,1,S){
			change(in[i][j],out[i][j],out[(i+1)&3][j]);
			change(out[i][j],in[i][j],in[(i+3)&3][j]);
		}
	}
	
	n-=2;
	forto(j,1,n){
		int x=1, y=2;
		forto(jj,2,j) move(x,y,2);
		move(x,y,3);
		ans[1][j]=y;
		forto(i,2,n){
			move(x,y,2);
			ans[i][j]=y;
		}
	}
	
	forto(i,1,n) forto(j,1,n){
		int t=ans[i][j]-1;
		putchar(s[t/(n+2)][t%(n+2)]);
		if (j==n) putchar('\n');
	}
	return 0;
}
	
		
		
		
		
		
		
		
		

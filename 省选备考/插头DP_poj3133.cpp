#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int inf=0x7fffffff;

int n,m;
int a[10][10];
int f[2][1<<20];
int lis[1<<20],top;

void genlis(int i, int k){
	//printf("genlis i=%d k=%d\n",i,k);
	if (i==m+1){
		lis[++top]=k;
		return;
	}
	forto(j,0,2) genlis(i+1,(k<<2)|j);
}

int get(int k, int i){
	k>>=(i-1)<<1;
	return k&3;
}

int set(int k, int i, int j){
	//printf("set %d %d %d  ",k,i,j);
	k^=get(k,i)<<( (i-1)<<1 );
	//printf("%d  ",k);
	k|=   j<< ( (i-1)<<1 );
	//printf("%d\n",k);
	return k;
}

void push(int b, int k, int j, int d, int r, int t){
	//if (t==0) printf("t=0 k=%d d=%d r=%d\n",k,d,r);
	
	int nk=set(k,j,d);
	nk=set(nk,j+1,r);
	if (j==m){
		if (r) return;
		nk<<=2;
	}
	f[!b][nk]=MIN(f[!b][nk],f[b][k]+t);
}

void pk(int k){
	forto(i,1,m+1){
		printf("%d",k&3);
		k>>=2;
	}
}	

int main(){
	for( scanf("%d%d",&n,&m); n; scanf("%d%d",&n,&m) ){
	
	forto(i,1,n) forto(j,1,m) scanf("%d",&a[i][j]);
	
	//printf("!!\n");
	
	top=0;
	genlis(0,0);
	
	//forto(i,1,top) printf("lis %d\n",lis[i]);
	//printf("!!\n");
	
	bool b=0;
	forto(li,1,top) f[0][lis[li]]=inf;
	f[0][0]=0;
	
	forto(i,1,n)
	forto(j,1,m){
		//printf("\n");
		//printf("i=%d j=%d f[b][0]=%d\n",i,j,f[b][0]);
		
		forto(li,1,top) f[!b][lis[li]]=inf;
		
		forto(li,1,top)
		if (f[b][lis[li]]!=inf){
			int k=lis[li];
			int l=get(k,j);
			int u=get(k,j+1);
			
			//printf("i=%d j=%d k=%d l=%d u=%d ",i,j,k,l,u);
			//pk(k); printf("\n");
			
			if (a[i][j]==0){
				if (l && u && l==u) push(b,k,j,0,0,1);
				if (!l && u){
					//printf("!!\n");
					push(b,k,j,u,0,1);
					push(b,k,j,0,u,1);
				}
				if (!u && l){
					//printf("!!\n");
					push(b,k,j,l,0,1);
					push(b,k,j,0,l,1);
				}
				if (!u && !l){
					//printf("!!\n");
					push(b,k,j,0,0,0);
					push(b,k,j,1,1,1);
					push(b,k,j,2,2,1);
				}
			}
			
			if (a[i][j]==1){
				if (!l && !u) push(b,k,j,0,0,0);
			}
			
			if (a[i][j]==2||a[i][j]==3){
				//printf("l=%d u=%d\n",l,u);
				int t=a[i][j]-1;
				if (!l && !u){
					push(b,k,j,t,0,0);
					push(b,k,j,0,t,0);
				}
				if (!l && u==t) push(b,k,j,0,0,0);
				if (!u && l==t) push(b,k,j,0,0,0);
			}
		}
		
		b=!b;
	}
	if (f[b][0]==inf) printf("0\n"); else printf("%d\n",f[b][0]+2);
	
	}
	return 0;
}
				
				
					
					
				
						
					
					
				
				
				
				
				

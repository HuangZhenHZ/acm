#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i<=(b);i++)

const int N=12000;

int f[N],max[N];
bool ok[N];
int gf(int x){ return f[x]==x?x:(f[x]=gf(f[x])); }

int main(){
	forto(i,1,N-1) f[i]=max[i]=i;
	int n; scanf("%d",&n);
	
	while (n--){
		int x,y; scanf("%d%d",&x,&y);
		x=gf(x); y=gf(y);
		if (x==y) ok[x]=true;
		if (x!=y){
			f[y]=x;
			if (ok[y]) ok[x]=true;
			if (max[y]>max[x]) max[x]=max[y];
		}
	}
	
	int i=1;
	while (ok[gf(i)]||max[gf(i)]!=i) i++;
	printf("%d\n",i-1);
	return 0;
}





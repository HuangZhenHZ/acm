#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
const int maxn=500000;

int n,m,d,t;
int f[maxn];
char s[10];

void set(int x, int l, int r, int i, int k){
	//printf("set %d %d %d %d %d\n",x,l,r,i,k);
	if (k>f[x]) f[x]=k;
	if (l==r) return;
	int m=(l+r)>>1;
	if (i<=m) set(x<<1,l,m,i,k);
	if (i>m) set(x<<1|1,m+1,r,i,k);
}

int get(int x, int l, int r, int ll, int rr){
	//printf("get %d %d %d %d %d\n",x,l,r,ll,rr);
	if (ll<=l && r<=rr) return f[x];
	int m=(l+r)>>1;
	int ans=0;
	if (ll<=m){
		int temp=get(x<<1,l,m,ll,rr);
		if (temp>ans) ans=temp;
	}
	if (rr>m){
		int temp=get(x<<1|1,m+1,r,ll,rr);
		if (temp>ans) ans=temp;
	}
	return ans;
}

int main(){
	scanf("%d%d",&m,&d);
	forto(i,1,m){
		int k;
		scanf("%s%d",s,&k);
		if (s[0]=='Q'){
			//printf("!!\n");
			printf("%d\n",t=get(1,1,m,n-k+1,n));
		}
		if (s[0]=='A'){
			k+=t; k%=d; n++;
			set(1,1,m,n,k);
		}
	}
	return 0;
}	

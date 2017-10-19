#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=60000;

int n;
int a[N];
struct rd{ int num,da; } d[N];
bool comp1(const rd &l, const rd &r){ return l.da<r.da; }

int f[N];

void add(int x){
	while (x<=n){ f[x]++; x+=x&(-x); }
}
void dec(int x){
	while (x<=n){ f[x]--; x+=x&(-x); }
}
int get(int x){
	int sum=0;
	while (x){ sum+=f[x]; x-=x&(-x); }
	return sum;
}

struct Q{ int num,l,r; } que[N];
int q,lev[N];

bool comp2(const Q &a, const Q &b){
	if (lev[a.num]<lev[b.num]) return true;
	if (lev[a.num]>lev[b.num]) return false;
	return a.r>b.r;
}

int ans[N];

int main(){
	scanf("%d",&n);
	forto(i,1,n){
		d[i].num=i;
		scanf("%d",&d[i].da);
	}
	
	std::sort(d+1,d+n+1,comp1);
	int p=1; a[d[1].num]=1;
	forto(i,2,n) a[d[i].num]= d[i].da==d[i-1].da?p:++p;
	
	scanf("%d",&q);
	forto(i,1,q){
		que[i].num=i;
		scanf("%d%d",&que[i].l,&que[i].r);
	}
	int de=sqrt(n+0.5);
	forto(i,1,q) lev[i]=(que[i].l-1)/de+1;
	std::sort(que+1,que+q+1,comp2);
	
	int l=1,r=1,sum=0;
	add(a[1]);
	forto(i,1,q){
		int nl=que[i].l, nr=que[i].r;
		
		while (r<nr){
			sum+=(r-l+1)-get(a[r+1]);
			add(a[++r]);
			//printf("1: %d\n",sum);
		}
		while (l>nl){
			sum+=get(a[l-1]-1);
			add(a[--l]);
			//printf("2: %d\n",sum);
		}
		while (r>nr){
			sum-=(r-l+1)-get(a[r]);
			dec(a[r--]);
			//printf("3: %d\n",sum);
		}
		while (l<nl){
			sum-=get(a[l]-1);
			dec(a[l++]);
			//printf("4: %d\n",sum);
		}
		
		ans[que[i].num]=sum;
	}
	
	forto(i,1,q) printf("%d\n",ans[i]);
	return 0;
}
	
	
	
	




#include<cstdlib>
#include<cstdio>
#include<algorithm>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int maxn=50100;

struct line{ double a,b; int num; };

bool comp(const line &l, const line &r){
	return (l.a<r.a)||(l.a==r.a && l.b>r.b);
}

bool check(line i, line j, line k){
	return (j.b-i.b)*(j.a-k.a) >= (k.b-j.b)*(i.a-j.a);
}

int n;
line s[maxn];
int f[maxn],top;
int ans[maxn];

int main(){
	scanf("%d",&n);
	forto(i,1,n){
		scanf("%lf%lf", &(s[i].a), &(s[i].b));
		s[i].num=i;
	}
	sort(s+1,s+n+1,comp);
	
	f[++top]=1;
	forto(i,2,n)
	if (s[i].a > s[f[top]].a){
		while (top>=2 && check(s[f[top-1]],s[f[top]],s[i])) top--;
		f[++top]=i;
	}
	
	forto(i,1,top) ans[i]=s[f[i]].num;
	sort(ans+1,ans+top+1);
	forto(i,1,top) printf("%d ",ans[i]);
	return 0;
}

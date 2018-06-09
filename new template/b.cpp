#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define MAX(a,b) ((a)>=(b)?(a):(b))
#define MIN(a,b) ((a)<=(b)?(a):(b))
#define ABS(x) ((x)>=0?(x):-(x))
using namespace std;

int w,h;

bool check(int a, int b, int c){
	
	int t1=a+b+a+b, t2=c+a+a;
	
	if (t1<=w && t2<=h) return true;
	if (t1<=h && t2<=w) return true;
	
	t1=a+b+c+b, t2=c+a+c;
	
	if (t1<=w && t2<=h) return true;
	if (t1<=h && t2<=w) return true;

	t1=a+b+c+b, t2=c+a+b;
	
	if (t1<=w && t2<=h) return true;
	if (t1<=h && t2<=w) return true;

	t1=a+b+a+c+a, t2=c+b;
	
	if (t1<=w && t2<=h) return true;
	if (t1<=h && t2<=w) return true;
	
	t1=a+b+c, t2=a+b+a+c;
	
	if (t1<=w && t2<=h) return true;
	if (t1<=h && t2<=w) return true;
	
	t1=a+b+a, t2=b+c+a+c;
	
	if (t1<=w && t2<=h) return true;
	if (t1<=h && t2<=w) return true;
	
	return false;
}

int a,b,c;

bool solve(){
	if (check(a,b,c)) return true;
	if (check(a,c,b)) return true;
	if (check(b,a,c)) return true;
	if (check(b,c,a)) return true;
	if (check(c,a,b)) return true;
	if (check(c,b,a)) return true;
	return false;
}

int main(){
	scanf("%d%d%d",&a,&b,&c);
	scanf("%d%d",&w,&h);
	printf(solve()?"Yes\n":"No\n");
	return 0;
}



Problem1000

var
  a,b,c:longint;
begin
  readln(a,b);
  c:=a+b;
  writeln(c);
end.
Problem1001

var
  a,dis:array[1..2000000]of longint;
  min:array[1..5000000]of longint;
  ne,da,long:array[1..6000000]of longint;
  n,m,s,t:longint;

function get(i,j:longint;k:boolean):longint;
begin
  get:=(i-1)*(m-1)*2 + j*2;
  if k then inc(get);
end;

procedure xb(i,j:longint);
var k:longint;
begin
  read(k);
  inc(t); ne[t]:=a[i]; da[t]:=j; long[t]:=k; a[i]:=t;
  inc(t); ne[t]:=a[j]; da[t]:=i; long[t]:=k; a[j]:=t;
end;

procedure change(x,l,r,a,b:longint);
var m:longint;
begin
  if l=r then begin min[x]:=b; exit; end;
  m:=(l+r)shr 1;
  if a<=m then change(x shl 1,l,m,a,b)
  else change(x shl 1+1,m+1,r,a,b);
  if min[x shl 1] <= min[x shl 1+1]
    then min[x]:=min[x shl 1]
    else min[x]:=min[x shl 1+1];
end;

function getmin(x,l,r:longint):longint;
var m:longint;
begin
  if l=r then exit(l);
  m:=(l+r)shr 1;
  if min[x shl 1] <= min[x shl 1+1]
    then getmin:=getmin(x shl 1,l,m)
    else getmin:=getmin(x shl 1+1,m+1,r);
end;

procedure readandjm;
var i,j,k:longint;
begin
  readln(n,m);

  if (n=1)or(m=1) then
  begin
    j:=maxlongint;
    while not(seekeof) do
    begin
      read(i);
      if i<j then j:=i;
    end;
    writeln(j);
    halt;
  end;


  s:=(n-1)*(m-1)*2+2;

  //read 1
  for i:=1 to m-1 do
    xb( get(1,i,true) ,s);

  for i:=2 to n-1 do
  for j:=1 to m-1 do
    xb( get(i-1,j,false) , get(i,j,true) );

  for i:=1 to m-1 do
    xb(1, get(n-1,i,false) );

  //read 2
  for i:=1 to n-1 do
  begin
    xb(1, get(i,1,false) );

    for j:=2 to m-1 do
      xb( get(i,j-1,true) , get(i,j,false) );

    xb( get(i,m-1,true) ,s);
  end;

  //read 3
  for i:=1 to n-1 do
  for j:=1 to m-1 do
    xb( get(i,j,false) , get(i,j,true) );
end;

procedure qzdl;
var i,j,k,d,l:longint;
begin
  fillchar(min,sizeof(min),$7f);
  change(1,1,s,1,0);
  fillchar(dis,sizeof(dis),$7f);
  dis[1]:=0;

  for i:=1 to s do
  begin
    j:=getmin(1,1,s);
    change(1,1,s,j,maxlongint);

    k:=a[j];
    while k<>0 do
    begin
      d:=da[k]; l:=long[k];
      if dis[j]+l < dis[d] then
      begin
        dis[d]:=dis[j]+l;
        change(1,1,s,d,dis[d]);
      end;
      k:=ne[k];
    end;
  end;
end;

begin
  readandjm;
  qzdl;
  writeln(dis[s]);
end.
Problem1002

type number=array[0..10]of longint;

procedure cheng3(var a:number);
var i:longint;
begin
  for i:=1 to a[0] do a[i]:=a[i]shl 1+a[i];

  for i:=1 to a[0] do
  while a[i]>=100000000 do
  begin
    a[i]:=a[i]-100000000;
    inc(a[i+1]);
  end;

  if (a[0]<7)and(a[a[0]+1]>0) then inc(a[0]);
end;

procedure jian(var a,b:number);
var i:longint;
begin
  for i:=1 to b[0] do a[i]:=a[i]-b[i];

  for i:=1 to a[0]-1 do
  if a[i]<0 then
  begin
    a[i]:=a[i]+100000000;
    dec(a[i+1]);
  end;

  while (a[0]>0)and(a[a[0]]=0) do dec(a[0]);
end;

procedure jia2(var a:number);
var i:longint;
begin
  a[1]:=a[1]+2;
  i:=1;
  while a[i]>=100000000 do
  begin
    a[i]:=a[i]-100000000;
    inc(a[i+1]);
    inc(i);
  end;
  if (a[0]<7)and(a[a[0]+1]>0) then inc(a[0]);
end;

procedure writenum(a:number);
var i:longint;
begin
  write(a[a[0]]);
  for i:=a[0]-1 downto 1 do
  begin
    if a[i]<10000000 then write('0');
    if a[i]<1000000 then write('0');
    if a[i]<100000 then write('0');
    if a[i]<10000 then write('0');
    if a[i]<1000 then write('0');
    if a[i]<100 then write('0');
    if a[i]<10 then write('0');
    write(a[i]);
  end;
  writeln;
end;

var a:array[0..100]of number;
    n,i:longint;
begin
  readln(n);
  a[1,0]:=1; a[1,1]:=1;
  for i:=2 to n do
  begin
    a[i]:=a[i-1];
    cheng3(a[i]);
    jian(a[i],a[i-2]);
    jia2(a[i]);
  end;
  writenum(a[n]);
end.
Problem1003

var
  a:array[1..20,1..20]of longint;
  dis:array[1..20]of longint;
  vis:array[1..20]of boolean;
  use:array[1..20,1..100]of boolean;

  f:array[1..100,1..100]of longint;
  dp:array[0..100]of longint;

  n,m,k,e,i,j:longint;
  conmax:longint;

procedure readdata;
var b,c,d,f:longint;
begin
  readln(n,m,k,e);
  for i:=1 to e do
  begin
    readln(b,c,d);
    a[b,c]:=d;
    a[c,b]:=d;
  end;

  fillchar(use,sizeof(use),true);
  readln(d);
  for i:=1 to d do
  begin
    readln(b,c,f);
    for j:=c to f do use[b,j]:=false;
  end;
end;

procedure qzdl(x,y:longint);
var i,j,k,min,mini:longint;
begin
  fillchar(dis,sizeof(dis),$7f);
  dis[1]:=0;
  fillchar(vis,sizeof(vis),false);
  for i:=1 to m do
  for j:=x to y do
    if use[i,j]=false then vis[i]:=true;

  while vis[m]=false do
  begin
    min:=maxlongint;
    for i:=1 to m do
    if (vis[i]=false)and(dis[i]<min) then
    begin
      min:=dis[i];
      mini:=i;
    end;
    i:=mini;
    vis[i]:=true;
    for j:=1 to m do
    if a[i,j]<>0 then
    if dis[i]+a[i,j]<dis[j] then
      dis[j]:=dis[i]+a[i,j];
  end;

  if dis[m]=conmax then f[x,y]:=dis[m]
    else f[x,y]:=dis[m]*(y-x+1);
end;

begin
  readdata;
  fillchar(conmax,sizeof(conmax),$7f);

  for i:=1 to n do
  for j:=i to n do
    qzdl(i,j);

  {for i:=1 to n do
  for j:=i to n do
    writeln(i,' ',j,' ',f[i,j]);}

  fillchar(dp,sizeof(dp),$7f);
  dp[0]:=0;
  for i:=1 to n do
  for j:=0 to i-1 do
  if dp[j]+f[j+1,i]+k < dp[i] then
    dp[i]:=dp[j]+f[j+1,i]+k;

  writeln(dp[n]-k);
end.
Problem1004

#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=b;i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

int a,b,c,n,m,p;
int f[70];
int s[70],top;
bool qc[70];
int dp[25][25][25];

void gets(){
	forto(i,1,n) qc[i]=true;
	top=0;
	forto(i,1,n)
	if (qc[i]){
		int sum=0;
		for(int j=i;qc[j];j=f[j]){
			qc[j]=false;
			sum++;
		}
		s[++top]=sum;
	}
}

int dfs(int i, int x, int y, int z){
	if (dp[x][y][z]!=-1) return dp[x][y][z];
	int sum=0;
	if (x>=s[i]) sum+=dfs(i-1,x-s[i],y,z);
	if (y>=s[i]) sum+=dfs(i-1,x,y-s[i],z);
	if (z>=s[i]) sum+=dfs(i-1,x,y,z-s[i]);
	sum%=p;
	return dp[x][y][z]=sum;
}

int getk(){
	forto(x,0,a)
	forto(y,0,b)
	forto(z,0,c) dp[x][y][z]=-1;
	
	dp[0][0][0]=1;
	return dfs(top,a,b,c);
}

void gcd(int a, int b, int &d, int &x, int &y){
	if (b==0){ d=a; x=1; y=0; return; }
	gcd(b,a%b,d,y,x);
	y-=x*(a/b);
}

int main(){
	scanf("%d%d%d%d%d",&a,&b,&c,&m,&p);
	n=a+b+c;
	
	forto(i,1,n) f[i]=i;
	gets();
	int sum=getk();
	int num=m+1;
	
	forto(mi,1,m){
		forto(i,1,n) scanf("%d",&f[i]);
		gets();
		if (top!=n){
			sum+=getk(); sum%=p;
		} else num--;
	}
	
	int d,x,y;
	gcd(num,p,d,x,y);
	x%=p; if (x<0) x+=p;
	printf("%d",sum*x%p);
	return 0;
}	
Problem1005

#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1010;

int p[maxn][maxn];

void getp(int n){
	for (int i=2;i<=n;i++){
		int k=i;
		for (int j=2;k!=1;j++)
		while (k%j==0){
			k/=j;
			p[i][j]++;
		}
	}
	for (int i=3;i<=n;i++)
	for (int j=2;j<=n;j++)
		p[i][j]+=p[i-1][j];
}

int ans[maxn];

inline void cheng(int k){
//	printf("cheng %d\n",k);
	
	for (int i=2;i<=k;i++)
		ans[i]+=p[k][i];
}

inline void chu(int k){
//	printf("chu %d\n",k);
	
	for (int i=2;i<=k;i++)
		ans[i]-=p[k][i];
}

inline void cc(int n, int m){
	cheng(n); chu(m); chu(n-m);
}

vector<int> a;
const int base=10000;

void atimesb(int b){
	for (int i=0;i<a.size();i++) a[i]*=b;
	for (int i=0;i<a.size();i++)
	if (a[i]>=base){
		if (i+1>=a.size()) a.push_back(0);
		a[i+1]+=a[i]/base;
		a[i]%=base;
	}
}

void writea(){
	printf("%d",a[a.size()-1]);
	for (int i=a.size()-2;i>=0;i--) printf("%04d",a[i]);
}

int main(){
	int n; scanf("%d",&n);
	getp(n-2);
	
	int sum=n-2, num=n;
	
	for (int i=1;i<=n;i++){
		int d; scanf("%d",&d);
		
		if (d==0 || d-1>sum){
			printf("0");
			return 0;
		}
		
		if (d!=-1){
			cc(sum,d-1);
			sum-=d-1;
			num--;
		}
	}
	
	if (num==0 && sum!=0){
		printf("0");
		return 0;
	}
	
//	printf("num=%d\n",num);
//	printf("sum=%d\n",sum);
	
	ans[num]+=sum;
	
//	int a=1;
//	for (int i=2;i<=n;i++)
//	while (ans[i]--)
//		a*=i;
		
//	printf("%d",a);

	a.push_back(1);
	for (int i=2;i<=n;i++)
	while (ans[i]--)
		atimesb(i);
	writea();
	
	return 0;
}
Problem1007

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
Problem1008

#include<cstdlib>
#include<cstdio>
typedef long long LL;
const LL modnum=100003;

LL power(LL a, LL n){
	if (n==0) return 1;
	LL p=power(a,n>>1);
	p=(p*p)%modnum;
	if (n&1) p=(p*a)%modnum;
	return p;
}

int main(){
	LL m,n; scanf("%lld %lld",&m,&n);
	LL a=power(m,n);
	LL b=(m*power(m-1,n-1))%modnum;
	LL c=a-b;
	if (c<0) c+=modnum;
	printf("%lld",c);
	return 0;
}
Problem1009

#include<cstdlib>
#include<cstdio>
#include<cstring>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)

void kmp(char s1[], int next1[], char s2[], int next2[]){
	int len1=strlen(s1+1), len2=strlen(s2+1);
	int j=0;
	forto(i,1,len1){
		while (j && s1[i]!=s2[j+1]) j=next2[j];
		if (s1[i]==s2[j+1]) j++;
		next1[i]=j;
	}
}

struct matrix{
	int n,m;
	int a[30][30];
	matrix(int n, int m):n(n),m(m){
		forto(i,1,n) forto(j,1,m)
		a[i][j]=0;
	}
};

int n,m,modnum;

matrix cheng(const matrix &a, const matrix &b){
	matrix c(a.n, b.m);
	forto(i,1,a.n)
	forto(j,1,b.m)
	forto(k,1,a.m){
		c.a[i][j]+=a.a[i][k]*b.a[k][j];
		c.a[i][j]%=modnum;
	}
	return c;
}

matrix power(const matrix &a, int n){
	if (n==1) return a;
	matrix p=power(a,n>>1);
	p=cheng(p,p);
	if (n&1) p=cheng(p,a);
	return p;
}	
	
char s[30];	
int next[30];

void makematrix(matrix &a){
	forto(i,0,m-1)
	forto(c,'0','9'){
		int j=i;
		while (j && s[j+1]!=c) j=next[j];
		if (s[j+1]==c) j++;
		a.a[i+1][j+1]++;
		if (a.a[i+1][j+1]==modnum) a.a[i+1][j+1]=0;
		//printf("%d %c %d\n",i,c,j);
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&modnum);
	scanf("%s",s+1);
	next[1]=0;
	kmp(s+1, next+1, s, next);
	
	matrix a(m,m);
	makematrix(a);
	
	matrix f=a;
	a=power(a,n);
	
	//forto(i,1,m){
	//	forto(j,1,m) printf("%d ",f.a[i][j]);
	//	printf("\n");
	//}
	
	matrix b(1,m);
	b.a[1][1]=1;
	
	matrix c=cheng(b,a);
	
	//forto(i,1,m)
	//	printf("%d ",c.a[1][i]);
	
	int ans=0;
	forto(i,1,m){
		ans+=c.a[1][i];
		if (ans>modnum) ans-=modnum;
	}
	
	printf("%d",ans);
	
	//forto(i,1,m)
	//forto(j,1,m)
	//	printf("%d ",a.a[i][j]);
		
	//printf("\n");
	
	//for (int i=1;i<=m;i++) printf("%d",next[i]);
	
	return 0;
}
Problem1010

#include<cstdio>
typedef long long LL;
const int maxn=60000;

LL s[maxn],f[maxn],g[maxn],h[maxn];
int q[maxn],l,r;
int n,c;

inline void count(int i){
	h[i]=f[i]+(g[i]+c)*(g[i]+c);
}	

inline bool check(int i){
	if (r-l+1<2) return false;
	int j=q[r-1], k=q[r];
	return (h[i]-h[k])*(g[k]-g[j]) <= (h[k]-h[j])*(g[i]-g[k]);
}

inline LL zy(int j, int i){
	return f[j]+(g[i]-g[j]-c)*(g[i]-g[j]-c);
}
	
int main(){
	scanf("%d%d",&n,&c);
	c++;
	for (int i=1;i<=n;i++){
		int t; scanf("%d",&t);
		s[i]=s[i-1]+LL(t);
	}
	
//	for (int i=1;i<=n;i++) printf("%lld ",s[i]);
//	printf("\n");
	
	count(0);
	l=r=1; q[1]=0;
	
	for (int i=1;i<=n;i++){
		g[i]=s[i]+i;
		while (l<r && zy(q[l],i)>=zy(q[l+1],i)) l++;
		f[i]=zy(q[l],i);
		
		//printf("zy %d %d\n",q[l],i);
		
		count(i);
		while (check(i)) r--;
		q[++r]=i;
	}
	
//	for (int i=1;i<=n;i++) printf("%lld ",g[i]);
//	printf("\n");
//	
//	for (int i=1;i<=n;i++) printf("%lld ",h[i]);
//	printf("\n");
//	
//	for (int i=1;i<=n;i++) printf("%lld ",f[i]);
	
	printf("%lld\n",f[n]);
	return 0;
}
Problem1012

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
Problem1013

#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define ABS(a) ((a)>=0?(a):-(a))
const int maxn=20;

double s[maxn][maxn];
double a[maxn][maxn];
int n;

void gauss(){
	forto(i,1,n){
		int k=i;
		forto(j,i+1,n) if (ABS(a[j][i])>ABS(a[k][i])) k=j;
		if (i!=k) forto(j,1,n+1) { double t=a[i][j]; a[i][j]=a[k][j]; a[k][j]=t; }
		
		forto(j,1,n) if (j!=i){
			double t=a[j][i]/a[i][i];
			forto(k,1,n+1) a[j][k]-=a[i][k]*t;
		}
	}
}
	
int main(){
	scanf("%d",&n);
	forto(i,1,n+1) forto(j,1,n) scanf("%lf",&s[i][j]);
	
	forto(i,1,n)
	forto(j,1,n){
		a[i][n+1]-=s[i][j]*s[i][j];
		a[i][n+1]+=s[i+1][j]*s[i+1][j];
		a[i][j]-=2*s[i][j];
		a[i][j]+=2*s[i+1][j];
	}
	
//	forto(i,1,n){
//		forto(j,1,n+1) printf("%lf ",a[i][j]);
//		printf("\n");
//	}
	
	gauss();
	forto(i,1,n-1) printf("%0.3lf ",a[i][n+1]/a[i][i]);
	printf("%0.3lf",a[n][n+1]/a[n][n]);
	return 0;
}
Problem1014

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#define nt(x) (ch[fa[x]][1]==x)

const int N=300000;

int fa[N],ch[N][2],size[N],hash[N],top;
char a[N];
int hmi[N];

void ud(int x){
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
	hash[x]=hash[ch[x][0]]*hmi[size[ch[x][1]]+1] + (a[x]-'a'+1)*hmi[size[ch[x][1]]] + hash[ch[x][1]];
}

void rtt(int x){
	int y=fa[x], z=fa[y]; bool p=nt(x);
	if (z) ch[z][nt(y)]=x;
	fa[ch[x][!p]]=y; fa[y]=x; fa[x]=z;
	ch[y][p]=ch[x][!p]; ch[x][!p]=y;
	ud(y);
}

void splay(int x){
	//static int sta[N],top;
	//sta[top=1]=x;
	//for(int y=x;fa[y];y=fa[y]) sta[++top]=fa[y];
	while (fa[x]){
		int y=fa[x];
		if (fa[y]) rtt(nt(x)^nt(y)?x:y);
		rtt(x);
	}
	ud(x);
	//printf("!!\n");
}

int find(int x, int s){
	while (size[ch[x][0]]+1!=s)
	if (s>size[ch[x][0]]+1){
		s-=size[ch[x][0]]+1;
		x=ch[x][1];
	} else x=ch[x][0];
	splay(x);
	return x;
}

void split(int x, int s, int &l, int &r){
	if (s<=0){ l=0; r=x; return; }
	if (s>=size[x]){ l=x; r=0; return; }
	l=find(x,s); r=ch[l][1];
	ch[l][1]=0; fa[r]=0; ud(l);
	return;
}

int merge(int l, int r){
	if (l==0) return r;
	if (r==0) return l;
	l=find(l,size[l]);
	ch[l][1]=r; fa[r]=l; ud(l);
	return l;
}

int insert(int x, int s, char c){
	a[++top]=c; ud(top);
	int l,r; split(x,s,l,r);
	return merge(merge(l,top),r);
}

int change(int x, int s, char c){
	int l,r; split(x,s-1,l,r);
	r=find(r,1);
	a[r]=c; ud(r);
	return merge(l,r);
}

int root;

int gethash(int x, int s){
	int a,b,c,t;
	split(root,x-1,a,t);
	split(t,s,b,c);
	int ans=hash[b];
	root=merge(merge(a,b),c);
	//printf("gethash(%d,%d)=%d size[%d]=%d\n",x,s,ans,b,size[b]);
	return ans;
}

int getans(int x, int y){
	int l=0, r=size[root]-MAX(x,y)+1;
	while (l<r){
		int m=(l+r+1)>>1;
		if (gethash(x,m)==gethash(y,m)) l=m; else r=m-1;
	}
	return l;
}	

char str[N];


int main(){
	hmi[0]=1;
	forto(i,1,N-1) hmi[i]=hmi[i-1]*29;
	
	scanf("%s",str);
	for(int i=0;str[i];i++){
		a[++top]=str[i]; ud(top);
		root=merge(root,top);
		//printf("i=%d size=%d\n",i,size[root]);
	}
	
	int m; scanf("%d",&m);
	while (m--){
		scanf("%s",str);
		if (str[0]=='Q'){
			int x,y; scanf("%d%d",&x,&y);
			printf("%d\n",getans(x,y));
		}
		if (str[0]=='R'){
			int x; char c[10]; scanf("%d%s",&x,c);
			root=change(root,x,c[0]);
		}
		if (str[0]=='I'){
			int x; char c[10]; scanf("%d%s",&x,c);
			root=insert(root,x,c[0]);
		}
	}
	return 0;
}
Problem1015

#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
const int maxn=400100;

struct edge{
	int next,to;
} e[maxn];

int n,m,la[maxn],top;

void addedge(int x, int y){
	e[++top]=(edge){la[x],y}; la[x]=top;
	e[++top]=(edge){la[y],x}; la[y]=top;
}

int f[maxn],ans[maxn],a[maxn],now;
bool b[maxn],vis[maxn];

int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}

void add(int x){
//	printf("add %d\n",x);

	vis[x]=true; now++;
	for(int i=la[x];i;i=e[i].next)
	if (vis[e[i].to]){
		int fx=find(x), fy=find(e[i].to);
		if (fx!=fy){
			f[fy]=fx;
			now--;		
			
//			printf("link %d %d\n",x,e[i].to);
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	while (m--){
		int x,y; scanf("%d%d",&x,&y); x++; y++;
		addedge(x,y);
	}
	
//	forto(i,1,n){
//		printf("%d:",i);
//		for(int j=la[i];j;j=e[j].next) printf(" %d",e[j].to);
//		printf("\n");
//	}
	
	forto(i,1,n) f[i]=i;
	int k; scanf("%d",&k);
	forto(i,1,k){
		scanf("%d",&a[i]); a[i]++;
		b[a[i]]=true;
	}
	forto(i,1,n) if (b[i]==false) add(i);
	
	fordown(i,k,1){
		ans[i]=now;
		add(a[i]);
	}
	printf("%d\n",now);
	forto(i,1,k) printf("%d\n",ans[i]);
	return 0;
}
Problem1024

function dfs(x,y:double;n:longint):double;
var i:longint;
    j,k:double;

begin
  if n=1 then
  begin
    if x>y then exit(x/y) else exit(y/x);
  end;

  dfs:=1e100;

  for i:=1 to n shr 1 do
  begin
    j:=dfs(x,y/n*i,i);
    k:=dfs(x,y/n*(n-i),n-i);
    if k>j then j:=k;
    if j<dfs then dfs:=j;

    j:=dfs(x/n*i,y,i);
    k:=dfs(x/n*(n-i),y,n-i);
    if k>j then j:=k;
    if j<dfs then dfs:=j;
  end;
end;

var x,y:double;
    n:longint;

begin
  readln(x,y,n);
  writeln(dfs(x,y,n):0:6);
end.
Problem1025

var
  a:array[1..1000]of longint;
  f:array[0..1000,0..1000]of int64;
  n,i,j,k,t:longint;
  ans:int64;

procedure prime;
var b:array[2..1000]of boolean;
    i,j,k:longint;
begin
  fillchar(b,sizeof(b),true);
  k:=trunc(sqrt(n+0.5));
  for i:=2 to k do
  if b[i] then
  begin
    j:=i*i;
    while j<=n do
    begin
      b[j]:=false;
      j:=j+i;
    end;
  end;
  for i:=2 to n do
  if b[i] then
  begin
    inc(t);
    a[t]:=i;
  end;
end;

begin
  readln(n);
  prime;
  f[0,0]:=1;

  for i:=1 to t do
  begin
    k:=a[i];
    while k<=n do
    begin
      for j:=k to n do
        f[i,j]:=f[i,j]+f[i-1,j-k];
      k:=k*a[i];
    end;
    for j:=0 to n do f[i,j]:=f[i,j]+f[i-1,j];
  end;

  for i:=0 to n do
    ans:=ans+f[t,i];

  writeln(ans);
end.
Problem1026

var
  a,b,sa,sb:longint;

function windy(x:longint):longint;
var f:array[1..10,0..9]of longint;
    a:array[1..10]of longint;
    len,i,j,k,t:longint;
begin
  len:=0;
  while x>0 do
  begin
    inc(len);
    a[len]:=x mod 10;
    x:=x div 10;
  end;

  if len>1 then t:=len-1 else t:=1;
  while (t>1)and( abs(a[t+1]-a[t])>=2 ) do dec(t);

  fillchar(f,sizeof(f),0);

  for i:=len downto t do
  for j:=0 to a[i]-1 do
  if (i<>len)or(j<>0) then
  if (i=len)or( abs(a[i+1]-j)>=2 ) then
    inc(f[i,j]);

  for i:=1 to len-1 do
  for j:=1 to 9 do
    inc(f[i,j]);

  for i:=len downto 2 do
  for j:=0 to 9 do
  if f[i,j]>0 then
  for k:=0 to 9 do
  if abs(j-k)>=2 then
    f[i-1,k]:=f[i-1,k]+f[i,j];

  windy:=0;
  for i:=0 to 9 do windy:=windy+f[1,i];
end;

begin
  readln(a,b);
  inc(b);
  sa:=windy(a);
  sb:=windy(b);
  writeln(sb-sa);
end.
Problem1031

#include<cstdlib>
#include<cstdio>
#include<cstring>
#define forto(i,a,b) for (int i=(a);i<=(b);i++)
#define fordown(i,a,b) for (int i=(a);i>=(b);i--)
const int maxn=220000;

int n;
int sa[maxn],rk[maxn*2],c[maxn],x[maxn];
char s[maxn];

void suffix_array(){
	forto(i,1,n) sa[i]=i;
	for (int m=300,k=0; k<n; k?k<<=1:k++){
		forto(i,1,m) c[i]=0;
		forto(i,1,n) c[rk[i]]++;
		forto(i,2,m) c[i]+=c[i-1];
		int p=0;
		forto(i,n-k+1,n) x[++p]=i;
		forto(i,1,n) if (sa[i]>k) x[++p]=sa[i]-k;
		fordown(i,n,1) sa[c[rk[x[i]]]--]=x[i];
		m=1; x[sa[1]]=1;
		forto(i,2,n) x[sa[i]]=rk[sa[i]]==rk[sa[i-1]]&&rk[sa[i]+k]==rk[sa[i-1]+k]?m:++m;
		forto(i,1,n) rk[i]=x[i];
		if (m==n) break;
	}
}

int main(){
	scanf("%s",s+1);
	int m=strlen(s+1);
	n=m<<1;
	forto(i,m+1,n) s[i]=s[i-m];
	
	//printf("%s\n",s+1);
	//printf("%d\n",n);
	
	forto(i,1,n) rk[i]=s[i];
	suffix_array();
	
	//forto(i,1,n) printf("%d ",sa[i]);
	//printf("\n");

	forto(i,1,n) if (sa[i]<=m) printf("%c",s[sa[i]+m-1]);
	return 0;
}
Problem1031

#include<cstdlib>
#include<cstdio>
#include<cstring>
#define forto(i,a,b) for (int i=(a);i<=(b);i++)
#define fordown(i,a,b) for (int i=(a);i>=(b);i--)
const int maxn=220000;
 
int n;
int sa[maxn],rk[maxn*2],c[maxn],x[maxn];
char s[maxn];
 
void suffix_array(){
	forto(i,1,n) sa[i]=i;
	
	int p=200;
	for(int k=0; k<n; k?k<<=1:k++){
		forto(i,1,p) c[i]=0;
		forto(i,1,n) c[rk[i]]++;
		forto(i,2,p) c[i]+=c[i-1];
		
		int t=0;
		forto(i,n-k+1,n) x[++t]=i;
		forto(i,1,n) if (sa[i]>k) x[++t]=sa[i]-k;
		
		fordown(i,n,1) sa[c[rk[x[i]]]--]=x[i];
		p=1; x[sa[1]]=1;
		forto(i,2,n) x[sa[i]]= rk[sa[i]]==rk[sa[i-1]] && rk[sa[i]+k]==rk[sa[i-1]+k] ? p:++p;
		
		forto(i,1,n) rk[i]=x[i];
		if (p==n) break;
	}
}
 
int main(){
    scanf("%s",s+1);
    int m=strlen(s+1);
    n=m<<1;
    forto(i,m+1,n) s[i]=s[i-m];
     
    //printf("%s\n",s+1);
    //printf("%d\n",n);
     
    forto(i,1,n) rk[i]=s[i];
    suffix_array();
     
    //forto(i,1,n) printf("%d ",sa[i]);
    //printf("\n");
 
    forto(i,1,n) if (sa[i]<=m) printf("%c",s[sa[i]+m-1]);
    return 0;
}
Problem1036

#include<cstdio>
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
using namespace std;

struct segment_tree{
	static const int maxn=70000;
	int max[maxn],sum[maxn];
	int n;
	
	void setn(int _n){
		n=_n;
	}
	
	void _set(int x, int l, int r, int a, int b){
		if (l==r){
			max[x]=sum[x]=b;
			return;
		}
		int m=(l+r)>>1;
		if (a<=m) _set(x<<1,l,m,a,b);
			else _set((x<<1)+1,m+1,r,a,b);
		max[x]=MAX(max[x<<1], max[(x<<1)+1]);
		sum[x]=sum[x<<1]+sum[(x<<1)+1];
	}
	
	void set(int a, int b){
		_set(1,1,n,a,b);
	}
	
	int _getmax(int x, int l, int r, int ll, int rr){
		if (ll<=l && r<=rr) return max[x];
		
		int maxnum=-100000;
		int m=(l+r)>>1;
		if (ll<=m){
			int temp=_getmax(x<<1,l,m,ll,rr);
			maxnum=MAX(maxnum,temp);
		}
		if (rr>m){
			int temp=_getmax((x<<1)+1,m+1,r,ll,rr);
			maxnum=MAX(maxnum,temp);
		}
		return maxnum;
	}
	
	int getmax(int ll, int rr){
		return _getmax(1,1,n,ll,rr);
	}
	
	int _getsum(int x, int l, int r, int ll, int rr){
		if (ll<=l && r<=rr) return sum[x];
		int sumnum=0;
		int m=(l+r)>>1;
		if (ll<=m) sumnum+=_getsum(x<<1,l,m,ll,rr);
		if (rr>m) sumnum+=_getsum((x<<1)+1,m+1,r,ll,rr);
		return sumnum;
	}
	
	int getsum(int ll, int rr){
		return _getsum(1,1,n,ll,rr);
	}
};

struct link_cut_tree{
	static const int maxn=40000;
	int n;
	vector<int> g[maxn];
	int size[maxn],dep[maxn],son[maxn],fa[maxn];
	int tid[maxn],top[maxn];
	int label;
	segment_tree seq;
	
	void setn(int _n){
		n=_n;
		seq.setn(n);
	}
	
	void add(int a, int b){
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	void find(int x, int father, int depth){
		size[x]=1; dep[x]=depth; son[x]=0; fa[x]=father;
		int maxsize=0;
		for (int i=0; i<g[x].size(); i++)
		if (g[x][i]!=father){
			int y=g[x][i];
			find(y,x,depth+1);
			size[x]+=size[y];
			if (size[y]>maxsize){
				maxsize=size[y];
				son[x]=y;
			}
		}
	}
	
	void connect(int x, int anc){
		tid[x]=++label; top[x]=anc;
		if (son[x]) connect(son[x], anc);
		for (int i=0; i<g[x].size(); i++){
			int y=g[x][i];
			if (y!=son[x] && y!=fa[x]) connect(y,y);
		}
	}
	
	void init(){
		find(1,0,1);
		connect(1,1);
	}
	
	void change(int x, int d){
		seq.set(tid[x],d);
	}
	
	int getmax(int x, int y){
		int maxnum=-100000,temp;
		while (top[x]!=top[y]){
			if (dep[top[x]]<dep[top[y]]) { int z=x; x=y; y=z; }
			temp=seq.getmax(tid[top[x]],tid[x]);
			maxnum=MAX(maxnum,temp);
			x=fa[top[x]];
		}
		if (dep[x]<dep[y]) temp=seq.getmax(tid[x],tid[y]);
			else temp=seq.getmax(tid[y],tid[x]);
		maxnum=MAX(maxnum,temp);
		return maxnum;
	}
	
	int getsum(int x, int y){
		int sumnum=0;
		while (top[x]!=top[y]){
			if (dep[top[x]]<dep[top[y]]) { int z=x; x=y; y=z; }
			sumnum+=seq.getsum(tid[top[x]],tid[x]);
			x=fa[top[x]];
		}
		if (dep[x]<dep[y]) sumnum+=seq.getsum(tid[x],tid[y]);
			sumnum+=seq.getsum(tid[y],tid[x]);
		return sumnum;
	}
} tree;


int main(){
	int n; scanf("%d",&n);
	tree.setn(n);
	for (int i=1;i<n;i++){
		int a,b; scanf("%d%d",&a,&b);
		tree.add(a,b);
	};
	tree.init();
	for (int i=1;i<=n;i++){
		int a; scanf("%d",&a);
		tree.change(i,a);
	}
	
	int q; scanf("%d",&q);
	while (q--){
		char s[20]; int a,b;
		scanf("%s %d%d",s,&a,&b);
		if (s[1]=='H') tree.change(a,b);
		if (s[1]=='M') printf("%d\n",tree.getmax(a,b));
		if (s[1]=='S') printf("%d\n",tree.getsum(a,b));
	}
	return 0;
}
Problem1040

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=la[x];i;i=e[i].ne)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef long long LL;
const int N=1000000+100;

struct E{ int to,ne; } e[N<<1];
int la[N],e_top;

void add(int x, int y){
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,la[y]}; la[y]=e_top;
}

int a[N];
LL f0[N],f1[N];
bool vis1[N],vis2[N],vis3[N];
int x1,x2;

bool dfs1(int x, int fa){
	//printf("dfs1 %d\n",x);
	vis1[x]=true;
	forE(i,x){
		int y=e[i].to;
		if (y==fa) continue;
		if (vis1[y]){
			x1=x; x2=y;
			return true;
		}
		if (dfs1(y,x)) return true;
	}
	return false;
}
	
void dfs2(int x, bool vis[]){
	vis[x]=true;
	f0[x]=0; f1[x]=a[x];
	forE(i,x){
		int y=e[i].to;
		if (vis[y]) continue;
		dfs2(y,vis);
		f0[x]+=f1[y];
		f1[x]+=f0[y];
	}
	if (f0[x]>f1[x]) f1[x]=f0[x];
}

int main(){
	int n; scanf("%d",&n);
	forto(i,1,n){
		int j; scanf("%d%d",&a[i],&j);
		add(i,j);
	}
	LL ans=0;
	forto(i,1,n) if (vis2[i]==false){
		//printf("%d\n",i);
		dfs1(i,0);
		dfs2(x1,vis2);
		LL t1=f0[x1];
		dfs2(x2,vis3);
		LL t2=f0[x2];
		ans+=MAX(t1,t2);
	}
	printf("%lld",ans);
	return 0;
}
Problem1047

var
  f,f1,f2:array[1..1000,1..1000]of longint;
  d,w:array[1..1000]of longint;
  a,b,n,i,j,l,r,ans:longint;

procedure qmax;
begin
  for i:=1 to a do
  begin
    l:=1; r:=0;
    for j:=1 to b do
    begin
      while (l<=r)and(d[r]<=f1[i,j]) do dec(r);
      inc(r); d[r]:=f1[i,j]; w[r]:=j;
      while (l<=r)and(w[l]<j-n+1) do inc(l);
      f1[i,j]:=d[l];
    end;
  end;

  for j:=1 to b do
  begin
    l:=1; r:=0;
    for i:=1 to a do
    begin
      while (l<=r)and(d[r]<=f1[i,j]) do dec(r);
      inc(r); d[r]:=f1[i,j]; w[r]:=i;
      while (l<=r)and(w[l]<i-n+1)do inc(l);
      f1[i,j]:=d[l];
    end;
  end;
end;

begin
  readln(a,b,n);
  for i:=1 to a do
  for j:=1 to b do
    read(f[i,j]);

  f1:=f;
  qmax;
  f2:=f1;

  for i:=1 to a do
  for j:=1 to b do
    f1[i,j]:=-f[i,j];

  qmax;
  ans:=maxlongint;
  for i:=n to a do
  for j:=n to b do
  if f1[i,j]+f2[i,j]<ans then
    ans:=f1[i,j]+f2[i,j];

  writeln(ans);
end.
Problem1051

type data=record
  da,ne:longint;
end;

var
  fi,la,pre,low,z,f,num:array[1..10000]of longint;
  vis,cd:array[1..10000]of boolean;
  a:array[1..50000]of data;
  n,m,i,j,k,t,time,top,c:longint;

procedure dfs(i:longint);
var j,k:longint;
begin
  inc(time);
  low[i]:=time; pre[i]:=time;
  vis[i]:=true;
  inc(top); z[top]:=i;

  k:=fi[i];
  while k<>0 do
  begin
    j:=a[k].da;
    if f[j]=0 then
    begin
      if vis[j]=false then dfs(j);
      if low[j]<low[i] then low[i]:=low[j];
    end;
    k:=a[k].ne;
  end;

  if low[i]=pre[i] then
  begin
    inc(c);
    while z[top]<>i do
    begin
      f[z[top]]:=c;
      dec(top);
      inc(num[c]);
    end;
    f[i]:=c;
    dec(top);
    inc(num[c]);
  end;
end;

begin
  readln(n,m);
  for k:=1 to m do
  begin
    readln(i,j);
    inc(t);
    if fi[i]=0 then
    begin
      fi[i]:=t;
      la[i]:=t;
      a[t].da:=j;
    end else
    begin
      a[la[i]].ne:=t;
      la[i]:=t;
      a[t].da:=j;
    end;
  end;

  for i:=1 to n do
  if vis[i]=false then dfs(i);

  for i:=1 to n do
  begin
    k:=fi[i];
    while k<>0 do
    begin
      j:=a[k].da;
      if f[i]<>f[j] then cd[f[i]]:=true;
      k:=a[k].ne;
    end;
  end;

  j:=0; k:=0;
  for i:=1 to c do
  if cd[i]=false then
  begin
    inc(j);
    k:=k+num[i];
  end;

  if j>1 then writeln('0')
  else writeln(k);
end.
Problem1051

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=la[x];i;i=e[i].ne)

const int N=11000, M=55000;

struct E{ int to,ne; } e[M];
int la[N],e_top;

void add(int x, int y){
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
}

int dfn[N],low[N],time,scc[N],cnt,sta[N],top,size[N];

void dfs(int x){
	dfn[x]=low[x]=++time;
	sta[++top]=x;
	forE(i,x){
		int y=e[i].to;
		if (!scc[y]){
			if (!dfn[y]) dfs(y);
			if (low[y]<low[x]) low[x]=low[y];
		}
	}
	if (dfn[x]==low[x]){
		cnt++;
		while (!scc[x]){
			scc[sta[top--]]=cnt;
			size[cnt]++;
		}
	}
}

bool cd[N];

int main(){
	int n,m; scanf("%d%d",&n,&m);
	while (m--){
		int x,y; scanf("%d%d",&x,&y);
		add(x,y);
	}
	forto(i,1,n) if (!dfn[i]) dfs(i);
	forto(x,1,n) forE(i,x){
		int y=e[i].to;
		if (scc[x]!=scc[y]) cd[scc[x]]=true;
	}
	int sum=0,ans=0;
	forto(i,1,cnt) if (!cd[i]){
		sum++;
		ans+=size[i];
	}
	if (sum==1) printf("%d",ans); else printf("0");
	return 0;
}
Problem1053

const
  a:array[1..10]of longint=(2,3,5,7,11,13,17,19,23,29);

var
  n,maxnum,maxsum:longint;

procedure dfs(num:int64; sum,x,limit:longint);
var i:longint;
begin
  if num>n then exit;
  if (sum>maxsum)or(sum=maxsum)and(num<maxnum) then
  begin
    maxsum:=sum;
    maxnum:=num;
  end;

  i:=1; num:=num*a[x];
  while (i<=limit)and(num<=n) do
  begin
    dfs(num,sum*(i+1),x+1,i);
    inc(i); num:=num*a[x];
  end;
end;

begin
  readln(n);
  dfs(1,1,1,100);
  writeln(maxnum);
end.
Problem1059

#include<cstdlib>
#include<cstdio>
const int maxn=300;

int n;
int a[maxn][maxn];
int f[maxn];
bool b[maxn];

bool dfs(int i){
	for (int j=1;j<=n;j++)
	if (a[i][j]&&b[j]){
		b[j]=false;
		if (f[j]==0||dfs(f[j])){
			f[j]=i;
			return true;
		}
	}
	return false;
}

bool solve(){
	int ans=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	
	for (int i=1;i<=n;i++) f[i]=0;
	
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++) b[j]=true;
		if (dfs(i)) ans++;
	}
	
	return ans==n;
}

int main(){
	int t; scanf("%d",&t);
	while (t--) printf(solve()?"Yes\n":"No\n");
	return 0;
}		
Problem1085

#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const char ans[5][6]={
	"11111",
	"01111",
	"00*11",
	"00001",
	"00000"
};
const int dx[8]={-2,-2,-1,-1,1,1,2,2};
const int dy[8]={-1,1,-2,2,-2,2,-1,1};

char s[5][6];

bool dfs(int n, int x, int y){
	int diff=0;
	forto(i,0,4) forto(j,0,4) diff+=ans[i][j]!=s[i][j];
	if (n==0) return diff==0;
	if (diff-1>n) return 0;
	
	forto(i,0,7){
		int nx=x+dx[i], ny=y+dy[i];
		if (nx>=0 && nx<=4 && ny>=0 && ny<=4){
			s[x][y]=s[nx][ny];
			s[nx][ny]='*';
			bool ok=dfs(n-1,nx,ny);
			s[nx][ny]=s[x][y];
			s[x][y]='*';
			if (ok) return 1;
		}
	}
	return 0;
}

int main(){
	int t; scanf("%d",&t);
	while (t--){
		forto(i,0,4) scanf("%s",s[i]);
		int x,y;
		forto(i,0,4) forto(j,0,4) 
		if (s[i][j]=='*'){
			x=i; y=j;
		}
		
		int i=1;
		while (i<=15 && !(dfs(i,x,y))) i++;
		if (i<=15) printf("%d\n",i); else printf("-1\n");
	}
	return 0;
}
Problem1088

var
  a:array[1..10000]of longint;
  f:array[1..10000,0..1,0..1]of longint;
  n,i,j,k:longint;

begin
  readln(n);
  for i:=1 to n do read(a[i]);

  f[1,0,0]:=1;
  f[1,0,1]:=1;

  for i:=1 to n-1 do
  for j:=0 to 1 do
  for k:=0 to 1 do
  if (a[i]-j-k=0)or(a[i]-j-k=1) then
    f[i+1,k,a[i]-j-k]:= f[i+1,k,a[i]-j-k] + f[i,j,k];

  k:=0;
  for i:=0 to 1 do
  for j:=0 to 1 do
  if i+j=a[n] then
    k:=k+f[n,i,j];

  writeln(k);
end.
Problem1208

#include<cstdio>
#include<set>
#define ABS(i) ((i)<(0)?(-(i)):(i))
using namespace std;
typedef set<int>::iterator it;

set<int> s;
int c,ans;

void done(it i,int b){
	int t=ABS(*i);
	ans=(ans+ABS(t-b))% 1000000;
	s.erase(t);
	s.erase(-t);
}

int main(){
	int n; scanf("%d",&n);
	while (n--){
		int a,b; scanf("%d%d",&a,&b);
		if (a==c||s.empty()){
			s.insert(b);
			s.insert(-b);
			c=a;
		} 
		else {
			it i=s.lower_bound(b);
			it j=s.lower_bound(-b);
			if (i==s.end()) done(j,b);
			else if (j==s.end()) done(i,b);
			else if ( *j+b<=*i-b ) done(j,b);
			else done(i,b);
		}
	}
	printf("%d",ans);
	return 0;
}
Problem1407

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)

typedef long long LL;
const int N=20;

void gcd(LL a, LL b, LL &d, LL &x, LL &y){
	if (b==0){ d=a; x=1; y=0; return; }
	gcd(b,a%b,d,y,x); y-=x*(a/b);
}

int n;
LL c[N],p[N],l[N];

bool ij_check(int i, int j, LL m){
	LL a=p[i]-p[j], b=c[j]-c[i];
	a%=m; if (a<0) a+=m;
	b%=m; if (b<0) b+=m;
	LL d,x,y; gcd(a,m,d,x,y);
	if (b%d) return true;
	b/=d; m/=d;
	x%=m; if (x<0) x+=m;
	LL ans=b*x%m;
	return ans>l[i]||ans>l[j];
}

bool check(LL m){
	forto(i,1,n-1) forto(j,i+1,n)
		if (!ij_check(i,j,m)) return false;
	return true;
}

int main(){
	scanf("%d",&n);
	forto(i,1,n) scanf("%lld%lld%lld",&c[i],&p[i],&l[i]);
	LL m=0;
	forto(i,1,n) if (c[i]>m) m=c[i];
	while (!check(m)) m++;
	printf("%lld\n",m);
	return 0;
}
Problem1854

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
Problem1878

#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=51000,M=210000;

int a[N],L[M],R[M],lev[M],q[M],f[1100000],ans[M];

bool comp(int x, int y){
	if (lev[x]<lev[y]) return true;
	if (lev[x]>lev[y]) return false;
	return R[x]<R[y];
}

int main(){
	int n; scanf("%d",&n);
	forto(i,1,n) scanf("%d",&a[i]);
	int m; scanf("%d",&m);
	int de=sqrt(n+0.5);
	forto(i,1,m){
		scanf("%d%d",&L[i],&R[i]);
		lev[i]=(L[i]-1)/de+1;
		q[i]=i;
	}
	std::sort(q+1,q+m+1,comp);
	
	int l=1,r=1,sum=1;
	f[a[1]]++;
	forto(i,1,m){
		int t=q[i];
		int nl=L[t],nr=R[t];
		while (l>nl) if (f[a[--l]]++==0) sum++;
		while (r<nr) if (f[a[++r]]++==0) sum++;
		while (l<nl) if (--f[a[l++]]==0) sum--;
		while (r>nr) if (--f[a[r--]]==0) sum--;
		ans[t]=sum;
	}
	forto(i,1,m) printf("%d\n",ans[i]);
	
	return 0;
}
Problem2002

#include<cstdio>

const int N=210000;

int fa[N],ch[N][2],size[N];

inline bool ir(int x){ return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x; }
inline bool nt(int x){ return ch[fa[x]][1]==x; }
inline void ud(int x){ size[x]=size[ch[x][0]]+size[ch[x][1]]+1; }

void rtt(int x){
//	printf("in rtt\n");
	
	int y=fa[x], z=fa[y]; bool p=nt(x);
	if (!ir(y)) ch[z][nt(y)]=x;
	fa[y]=x; fa[x]=z; fa[ch[x][!p]]=y;
	ch[y][p]=ch[x][!p]; ch[x][!p]=y;
	ud(y);
	
//	printf("out rtt\n");
}

void splay(int x){
//	printf("in splay\n");
	
	while (!ir(x)){
		int y=fa[x];
		if (!ir(y)) rtt(nt(x)^nt(y)?x:y);
		rtt(x);
	}
	ud(x);
	
//	printf("out splay\n");
}

void access(int x){
//	printf("in access\n");
	
	int y=x, t=0;
	while (x){
		splay(x);
		ch[x][1]=t;
		t=x;
		x=fa[x];
	}
	splay(y);
	
//	printf("out access\n");
}	
	
void link(int c, int f){ access(c); fa[c]=f; }
void cut(int x){ access(x); fa[ch[x][0]]=0; ch[x][0]=0; }

int main(){
	int n; scanf("%d",&n);
	for (int i=1;i<=n;i++) size[i]=1;
	for (int i=1;i<=n;i++){
		int k; scanf("%d",&k);
		if (i+k<=n) link(i,i+k);
	}
	int m; scanf("%d",&m);
	while (m--){
		int i,j,k; scanf("%d%d",&i,&j); j++;
		if (i==1){
			access(j);
			printf("%d\n",size[j]);
		}
		if (i==2){
			scanf("%d",&k);
			cut(j);
			if (j+k<=n) link(j,j+k);
		}
	}
	return 0;
}
Problem2038

#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;
const int N=51000;

int c[N],L[N],R[N],lev[N],q[N],f[N];
LL ans[N];

bool comp(int a, int b){ 
	if (lev[a]<lev[b]) return true;
	if (lev[a]>lev[b]) return false;
	return R[a]>R[b];
}

LL gcd(LL a, LL b){
	while (a&&b){
		if (b&&a>=b) a%=b;
		if (a&&b>=a) b%=a;
	}
	return a?a:b;
}	

int main(){
	int n,m; scanf("%d%d",&n,&m);
	forto(i,1,n) scanf("%d",&c[i]);
	forto(i,1,m) scanf("%d%d",&L[i],&R[i]);
	int de=sqrt(n+0.5);
	forto(i,1,m) lev[i]=(L[i]+1)/de+1;
	forto(i,1,m) q[i]=i;
	std::sort(q+1,q+m+1,comp);
	
	int l=1,r=1; LL sum=0;
	f[c[1]]++;
	forto(i,1,m){
		int t=q[i];
		int nl=L[t], nr=R[t];
		while (l>nl) sum+=f[c[--l]]++;
		//printf("sum=%d\n",sum);
		while (r<nr) sum+=f[c[++r]]++;
		//printf("sum=%d\n",sum);
		while (l<nl) sum-=--f[c[l++]];
		//printf("sum=%d\n",sum);
		while (r>nr) sum-=--f[c[r--]];
		//printf("sum=%d\n",sum);
		ans[t]=sum;
		//printf("ans[%d]=%d\n",t,ans[t]);
	}
	
	forto(i,1,m){
		LL x=ans[i], y=R[i]-L[i]+1;
		y=(y*(y-1))>>1;
		//printf("%I64d\n",y);
		LL g=gcd(x,y);
		//printf("%I64d/%I64d\n",x,y);
		//printf("%I64d\n",g);
		printf("%lld/%lld\n",x/g,y/g);
	}
	return 0;
}
Problem2049

#include<cstdlib>
#include<cstdio>
#define swap(a,b) {swp=a;a=b;b=swp;}
int swp;

inline void readint(int &x){
	x=0; char c=getchar();
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9'){ x=x*10+c-'0'; c=getchar(); }
}

const int maxn=11000;

int n,m,fa[maxn],ch[maxn][2],sta[maxn],top;
bool rev[maxn];

inline bool ir(int x){ return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x; }
inline bool nt(int x){ return ch[fa[x]][1]==x; }

inline void pd(int x){
	if (rev[x]){
		rev[ch[x][0]]^=1; rev[ch[x][1]]^=1;
		swap(ch[x][0],ch[x][1]); rev[x]=false;
	}
}

inline void rtt(int x){
	int y=fa[x], z=fa[y]; bool p=nt(x);
	if (!ir(y)) ch[z][nt(y)]=x;
	fa[ch[x][!p]]=y; fa[y]=x; fa[x]=z;
	ch[y][p]=ch[x][!p]; ch[x][!p]=y;
}

inline void splay(int x){
	top=0; sta[++top]=x;
	for (int y=x;!ir(y);y=fa[y]) sta[++top]=fa[y];
	while (top) pd(sta[top--]);
	while (!ir(x)){
		int y=fa[x];
		if (!ir(y)) rtt(nt(x)^nt(y)?x:y);
		rtt(x);
	}
}

inline void access(int x){
	int t=0;
	while (x){
		splay(x); ch[x][1]=t;
		t=x; x=fa[x];
	}
} 

inline void makeroot(int x){
	access(x); splay(x); x[rev]^=1;
}

inline void link(int x, int y){
	makeroot(x); fa[x]=y;
}

inline void cut(int x, int y){
	makeroot(x); access(y); splay(y); ch[y][0]=fa[x]=0;
}

inline int find(int x){
	access(x); splay(x);
	int y=x; while (ch[y][0]) y=ch[y][0];
	return y;
};	

int main(){
	readint(n); readint(m);
	while (m--){
		char s[10]; scanf("%s",s);
		int x,y; readint(x); readint(y);
		if (s[0]=='Q'){
			if (find(x)==find(y)) printf("Yes\n"); else printf("No\n");
		}
		if (s[0]=='C') link(x,y);
		if (s[0]=='D') cut(x,y);
		
//		for (int x=1;x<=n;x++){
//			for (int y=1;y<=n;y++) printf("%d ",check(x,y));
//			printf("\n");
//		}
	}
	return 0;
}
Problem2111

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef long long LL;
const int N=1100000;

int n,p;
LL fac[N],inv[N];
LL f[N],size[N];

LL C(int n, int m){
	LL ans=1;
	//printf("C(%d,%d)=",n,m);
	while (n||m){
		int a=n%p, b=m%p;
		n/=p; m/=p;
		if (a<b) return 0;
		ans= ans *fac[a]%p *inv[b]%p *inv[a-b]%p;
	}
	//printf("%d\n",int(ans));
	return ans;
}

int main(){
	scanf("%d%d",&n,&p);
	
	int m=MIN(n,p-1);
	fac[0]=1;
	forto(i,1,m) fac[i]=fac[i-1]*i%p;
	inv[1]=1;
	forto(i,2,m) inv[i]=(p-p/i)*inv[p%i]%p;
	inv[0]=1;
	forto(i,1,m) inv[i]=inv[i-1]*inv[i]%p;
	
	fordown(i,n,1){
		if ((i<<1)>n){ f[i]=size[i]=1; }
		if ((i<<1)==n){
			f[i]=f[i<<1];
			size[i]=size[i<<1]+1;
		}
		if ((i<<1)<n){
			size[i]=size[i<<1]+size[i<<1|1]+1;
			f[i]=C(size[i]-1,size[i<<1]) *f[i<<1]%p *f[i<<1|1]%p;
		}
		//printf("f[%d]=%d\n",i,int(f[i]));
	}
	
	//forto(i,1,n) printf("f[%d]=%d\n",i,int(f[i]));
	
	printf("%d",int(f[1]));
	return 0;
}
Problem2132

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int N=12000, M=42000, inf=0x7fffffff;

struct E{ int to,cap,ne; } e[M<<1];
int n,la[N],e_top;

void add(int x, int y, int z){
	e[++e_top]=(E){y,z,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,z,la[y]}; la[y]=e_top; //warn!!!
}

int q[N],l,r,dis[N],cur[N];

bool bfs(){
	q[l=r=1]=1;
	forto(i,1,n) dis[i]=inf;
	dis[1]=0;
	while (l<=r){
		int x=q[l++];
		for(int i=la[x];i;i=e[i].ne)
		if (e[i].cap && dis[x]+1<dis[e[i].to]){
			dis[e[i].to]=dis[x]+1;
			q[++r]=e[i].to;
		}
	}
	return dis[n]!=inf;
}

int dfs(int x, int a){
	if (x==n || a==0) return a;
	int flow=0;
	for(int &i=cur[x];i&&a;i=e[i].ne) if (dis[x]+1==dis[e[i].to] && e[i].cap){
		int t=dfs(e[i].to,MIN(a,e[i].cap));
		flow+=t; a-=t; e[i].cap-=t; e[i^1].cap+=t;
	}
	return flow;
}

int dinic(){
	int flow=0;
	while (bfs()){
		forto(i,1,n) cur[i]=la[i];
		flow+=dfs(1,inf);
		//printf("%d\n",flow);
	}
	return flow;
}	

const int maxn=120;

int a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
int nn,mm;

#define getnum(i,j) (((i)-1)*mm+(j)+1)

int main(){
	scanf("%d%d",&nn,&mm);
	n=nn*mm+2;
	e_top=1;
	
	forto(i,1,nn) forto(j,1,mm) scanf("%d",&a[i][j]);
	forto(i,1,nn) forto(j,1,mm) scanf("%d",&b[i][j]);
	forto(i,1,nn) forto(j,1,mm) scanf("%d",&c[i][j]);
	
	int sum=0;
	//printf("!!\n");
	//printf("e_top=%d\n",e_top);
	
	forto(i,1,nn) forto(j,1,mm){
		if ((i&1)^(j&1)){
			add(1,getnum(i,j),a[i][j]);
			add(getnum(i,j),n,b[i][j]);
			if (i> 1) add(getnum(i,j),getnum(i-1,j),c[i][j]+c[i-1][j]);
			if (i<nn) add(getnum(i,j),getnum(i+1,j),c[i][j]+c[i+1][j]);
			if (j> 1) add(getnum(i,j),getnum(i,j-1),c[i][j]+c[i][j-1]);
			if (j<mm) add(getnum(i,j),getnum(i,j+1),c[i][j]+c[i][j+1]);
		} else {
			add(1,getnum(i,j),b[i][j]);
			add(getnum(i,j),n,a[i][j]);
		}
		
		sum+=a[i][j]+b[i][j];
		if (i> 1) sum+=c[i][j];
		if (i<nn) sum+=c[i][j];
		if (j> 1) sum+=c[i][j];
		if (j<mm) sum+=c[i][j];
		//printf("e_top=%d\n",e_top);
	}
	//printf("!!\n");
	
	printf("%d",sum-dinic());
	
	return 0;
}
Problem2150

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
Problem2282

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int N=310000;
const int inf=0x7fffffff;

struct E{ int to,dis,ne; } e[N<<1];
int n,la[N],e_top;

void add(int x, int y, int z){
	e[++e_top]=(E){y,z,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,z,la[y]}; la[y]=e_top;
}

int dis[N], fa[N], fadis[N], q[N], l,r;

int bfs(int x){
	//forto(i,1,n) dis[i]=-1;
	dis[x]=0;
	q[l=r=1]=x;
	int ans=x;

	while (l<=r){
		x=q[l++];
		for(int i=la[x]; i; i=e[i].ne){
			int y=e[i].to, z=e[i].dis;
			if (dis[y]==-1){
				dis[y]=dis[x]+z;
				if (dis[y]>dis[ans]) ans=y;
				fa[y]=x;
				fadis[y]=z;
				q[++r]=y;
			}
		}
	}
	return ans;
}

int lis[N],d[N],f[N],L[N],R[N],top;

int main(){
	int s; scanf("%d%d",&n,&s);
	forto(i,2,n){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	forto(i,1,n) dis[i]=-1;
	int x=bfs(1);
	forto(i,1,n) dis[i]=-1;
	int y=bfs(x);
	
	while (y!=x){
		lis[++top]=y;
		d[top]=fadis[y];
		y=fa[y];
	}
	lis[++top]=x;
	
	forto(i,1,top){
		forto(j,1,n) dis[j]=-1;
		if (i!=1) dis[lis[i-1]]=0;
		if (i!=top) dis[lis[i+1]]=0;
		int t=bfs(lis[i]);
		f[i]=dis[t];
	}
	
	L[1]=f[1];
	forto(i,2,top) L[i]=MAX(L[i-1]+d[i-1],f[i]);
	R[top]=f[top];
	fordown(i,top-1,1) R[i]=MAX(R[i+1]+d[i],f[i]);
	
	//forto(i,1,top) printf("%d %d %d %d %d\n",lis[i],F[i],L[i],R[i],d[i]);
	
	int ans=inf;
	q[l=r=1]=1;
	int j=1;
	forto(i,1,top){
		while (j!=top && d[j]<=s){
			s-=d[j];
			j++;
			while (l<=r && f[q[r]]<=f[j]) r--;
			q[++r]=j;
		}
		int t=MAX(L[i],R[j]);
		t=MAX(t,f[q[l]]);
		if (t<ans) ans=t;
		if (q[l]==i) l++;
		s+=d[i];
	}
	printf("%d",ans);
	return 0;
}
Problem2440

#include<cstdlib>
#include<cstdio>
#include<cmath>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;
const int N=50000;

int a[N],top,f[N],mo[N];
bool b[N];

void getprime(){
	mo[1]=1;
	forto(i,2,N-1){
		if (b[i]==false){
			a[++top]=i;
			f[i]=top;
			mo[i]=-1;
		}
		forto(j,1,f[i]){
			int t=i*a[j];
			if (t>=N) break;
			b[t]=true;
			f[t]=j;
			if (mo[i] && j!=f[i])
				mo[t]=-mo[i];
		}
	}
}

LL get(LL x){
	LL ans=0; int t=sqrt(x+0.5);
	forto(i,1,t) if (mo[i])
		ans+= x/(i*i)*mo[i];
	return ans;
}

LL getans(int k){
	LL l=1, r=LL(N)*LL(N);
	while (l<r){
		LL m=(l+r)>>1;
		LL t=get(m);
		if (t==k) r=m;
		if (t<k) l=m+1;
		if (t>k) r=m-1;
	}
	return l;
}

int main(){
	getprime();
	int t; scanf("%d",&t);
	while (t--){
		int k; scanf("%d",&k);
		printf("%lld\n",getans(k));
	}
	return 0;
}
Problem2565

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int N=100000+100;

char str[N],s[N<<1];
int f[N<<1],a[N<<1];

int main(){
	scanf("%s",str);
	int n=0;
	for(int i=0;str[i];i++){
		s[++n]='#';
		s[++n]=str[i];
	}
	s[++n]='#';
	
	//printf("%s\n",s+1);
	
	int mx=1,mr=1;
	forto(i,2,n){
		int t=0;
		if (i<mr) t=MIN(f[2*mx-i],mr-i);
		while (i-t-1 && s[i-t-1]==s[i+t+1]) t++;
		f[i]=t;
		if (i+t>mr){ mx=i; mr=i+t; }
	}
	
	//forto(i,1,n) printf("%d",f[i]);
	
	forto(i,1,n) a[i]=i;
	forto(i,1,n) if (i<a[i+f[i]]) a[i+f[i]]=i;
	fordown(i,n-1,1) if (a[i+1]<a[i]) a[i]=a[i+1];
	
	//forto(i,1,n) printf("%d",a[i]);
	
	int ans=0;
	forto(i,1,n){
		int j=i-f[i]-1;
		if (j==0) j=1;
		j=a[j];
		if ((i-j)*2>ans) ans=(i-j)*2;
	}
	
	ans>>=1;
	if (ans==1) ans=0;	
	printf("%d",ans);
	return 0;
}
Problem2659

#include<cstdlib>
#include<cstdio>

typedef long long LL;

int main(){
	LL p,q; scanf("%lld%lld",&p,&q);
	if (p==q) printf("%lld",(p+1)*(p-1)/4);
	else printf("%lld",(p-1)*(q-1)/4);
	return 0;
}
Problem2730

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef long long LL;

const int N=600,M=600;

struct E{ int to,ne; } e[M<<1];
int n,m,r,la[N],e_top;

void add(int x, int y){
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,la[y]}; la[y]=e_top;
}

int dfn[N],low[N],cnt,f[N];

void dfs(int x, int fa){
	dfn[x]=low[x]=++cnt;
	if (fa) f[x]=1;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (dfn[y] && y!=fa) low[x]=MIN(low[x],dfn[y]);
		if (dfn[y]==0){
			dfs(y,x);
			low[x]=MIN(low[x],low[y]);
			if (low[y]>=dfn[x]) f[x]++;
		}
	}
}

bool vis[N];
int sta[N],sta_top;

int getsize(int x){
	//printf("vis %d\n",x);
	vis[x]=true;
	int size=1;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (vis[y]==false){
			if (f[y]<=1) size+=getsize(y);
			if (f[y]>=2) vis[sta[++sta_top]=y]=true;
		}	
	}
	return size;
}

int lis[N],top;

int main(){
	int t=0;
	for(scanf("%d",&m); m; scanf("%d",&m)){
		n=r=e_top=0;
		forto(i,1,550) la[i]=0;
		
		while (m--){
			int x,y; scanf("%d%d",&x,&y);
			n=MAX(n,x); n=MAX(n,y);
			add(x,y);
			if (r==0) r=x;
		}
		
		forto(i,1,n) dfn[i]=low[i]=f[i]=0;
		cnt=0;
		
		dfs(r,0);
		
		//forto(i,1,n) printf("f[%d]=%d\n",i,f[i]);
		
		forto(i,1,n) vis[i]=false;
		top=0;
		forto(i,1,n) if (f[i]<=1 && vis[i]==false){
			lis[++top]=getsize(i);
			if (sta_top!=1) top--;
			//printf("sta_top %d\n",sta_top);
			while (sta_top) vis[sta[sta_top--]]=false;
		}
		
		//forto(i,1,top) printf("lis[%d]=%d\n",i,lis[i]);
		if (top==0) printf("Case %d: 2 %d\n",++t,n*(n-1)/2);
		else {
			LL ans=1;
			forto(i,1,top) ans*=lis[i];
			printf("Case %d: %d %lld\n",++t,top,ans);
		}
	}
	return 0;
}
Problem2752

#include<cstdlib>
#include<cstdio>

typedef long long LL;

inline void readint(int &x){
	x=0; char c=getchar(); bool flag=false;
	while ((c<'0'||c>'9')&&c!='-') c=getchar();
	if (c=='-'){ flag=true; c=getchar(); }
	while (c>='0'&&c<='9'){ x=x*10+c-'0'; c=getchar(); }
	if (flag) x=-x;
}

LL gcd(LL a, LL b){ return b?gcd(b,a%b):a; }

const int maxn=300000;

int n,m,anslen;
LL L[maxn],R[maxn],ans[maxn],sum[maxn],add[maxn];

void merge(int x, int l, int lenl, int r, int lenr){
	LL lenx=lenl+lenr;
	LL sumx=sum[l]+sum[r]+add[x]*(lenx);
	LL t=add[x]*(lenx+1)*lenx/2;
	LL Lx=L[l]+L[r]+sum[l]*lenr+t;
	LL Rx=R[l]+R[r]+sum[r]*lenl+t;
	LL ansx=ans[l]+ans[r]+R[l]*lenr+L[r]*lenl;
	ansx+=add[x]*((lenx+1)*lenx/2*(lenx+1)-lenx*(lenx+1)*(2*lenx+1)/6);
	sum[x]=sumx; L[x]=Lx; R[x]=Rx; ans[x]=ansx; 
}

void update(int x, int l, int r){
	if (l+1==r){
		sum[x]+=add[x];
		L[x]=R[x]=ans[x]=sum[x];
		add[x]=0;
		return;
	}
	int m=(l+r)>>1, lc=x<<1, rc=x<<1|1;
	merge(x,lc,m-l,rc,r-m);
}

void pushdown(int x, int l, int r){
	if (!add[x]) return;
	int m=(l+r)>>1, lc=x<<1, rc=x<<1|1;
	add[lc]+=add[x]; update(lc,l,m);
	add[rc]+=add[x]; update(rc,m,r);
	add[x]=0;
}
	
void __addup(int x, int l, int r, int ll, int rr, int t){
	int m=(l+r)>>1, lc=x<<1, rc=x<<1|1;
	pushdown(x,l,r);
	if (ll<=l&&r<=rr) add[x]+=t;
	else{
		if (ll<m) __addup(lc,l,m,ll,rr,t);
		if (rr>m) __addup(rc,m,r,ll,rr,t);
	}
	update(x,l,r);
}

void addup(int ll, int rr, int t){
	__addup(1,1,n,ll,rr,t);
}

void __getans(int x, int l, int r, int ll, int rr){
	int m=(l+r)>>1, lc=x<<1, rc=x<<1|1;
	pushdown(x,l,r);
	if (ll<=l&&r<=rr){
		merge(0,0,anslen,x,r-l);
		anslen+=r-l;
	} else {
		if (ll<m) __getans(lc,l,m,ll,rr);
		if (rr>m) __getans(rc,m,r,ll,rr);
	}
}

LL getans(int ll, int rr){
	L[0]=R[0]=ans[0]=sum[0]=add[0]=anslen=0;
	__getans(1,1,n,ll,rr);
	return ans[0];
}

int main(){
	readint(n); readint(m);
	while (m--){
		char s[10]; scanf("%s",s);
		int l,r,v;
		if (s[0]=='C'){
			readint(l); readint(r); readint(v);
			addup(l,r,v);
		}
		if (s[0]=='Q'){
			readint(l); readint(r);
			LL a=getans(l,r);
			LL b=(LL(anslen)+1)*LL(anslen)/2;
			LL g=gcd(a,b);
			a/=g; b/=g;
			printf("%lld/%lld\n",a,b);
		}
	}
	return 0;
}
Problem2753

#include<cstdlib>
#include<cstdio>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef long long LL;
const int inf=0x7fffffff;

const int N=110000, M=1100000;

struct E{ int to,dis,ne; } e[M<<1];
int la[N],e_top;

void add(int x, int y, int z){
	e[++e_top]=(E){y,z,la[x]}; la[x]=e_top;
}

int n,m,h[N],min[N];
int q[N],l,r;

void bfs(){
	forto(i,2,n) min[i]=inf;
	q[l=r=1]=1;
	while (l<=r){
		int x=q[l++];
		for(int i=la[x];i;i=e[i].ne){
			int y=e[i].to, z=e[i].dis;
			if (z<min[y]){
				if (min[y]==inf) q[++r]=y;
				min[y]=z;
			}
		}
	}
}

struct data{ int x,y,z; } a[M<<1];
int top;

bool comp(const data &a, const data &b){
	if (h[a.y]>h[b.y]) return true;
	if (h[a.y]<h[b.y]) return false;
	return a.z<b.z;
}	

int f[N];

int gf(int x){
	return f[x]==x?x:f[x]=gf(f[x]);
}

int main(){
	scanf("%d%d",&n,&m);
	forto(i,1,n) scanf("%d",&h[i]);
	forto(i,1,m){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if (h[x]>=h[y]) add(x,y,z);
		if (h[y]>=h[x]) add(y,x,z);
	}
	bfs();
	int sum=0;
	forto(i,1,n) if (min[i]!=inf) sum++;
	printf("%d ",sum);
	
	forto(x,1,n) if (min[x]!=inf)
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to, z=e[i].dis;
		if (min[y]!=inf) a[++top]=(data){x,y,z};
	}
	std::sort(a+1,a+top+1,comp);
	
	//forto(i,1,top) printf("%d %d %d\n", a[i].x, a[i].y, a[i].z);
	
	forto(i,1,n) f[i]=i;
	LL ans=0;
	forto(i,1,top){
		int x=a[i].x, y=a[i].y, z=a[i].z;
		int fx=gf(x), fy=gf(y);
		if (fx!=fy){
			ans+=z;
			f[fy]=fx;
		}
	}
	
	printf("%lld",ans);
	return 0;
}
Problem2956

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;

const LL MOD=19940417, inv=3323403;

LL cal(LL n, LL a){
	LL ans=0, i=1;
	while (i<=n){
		LL k=a/i, j=a/k;
		if (j>n) j=n;
		ans+=(i+j)*(j-i+1)/2*k;
		ans%=MOD; if (ans<0) ans+=MOD;
		i=j+1;
		//printf("%lld %lld\n",i,j);
	}
	return ans;
}

LL cal1(LL n, LL a){
	LL ans=(n%MOD)*(a%MOD)%MOD;
	ans-=cal(n,a);
	if (ans<0) ans+=MOD;
	return ans;
}	

LL sum(LL n){ return n*(n+1)%MOD *(2*n+1)%MOD *inv%MOD; }

LL cal2(LL n, LL m){
	if (n>m){ LL t=n; n=m; m=t; }
	LL ans=(n%MOD)* (n%MOD)%MOD *(m%MOD)%MOD;
	ans-=n*cal(n,m)+m*cal(n,n);
	//printf("%I64d\n",ans);
	ans%=MOD; if (ans<0) ans+=MOD;
	LL i=1;
	while (i<=n){
		LL kn=n/i, jn=n/kn;
		LL km=m/i, jm=m/km;
		LL k=kn*km, j=jn<jm?jn:jm;
		if (j>n) j=n;
		LL t=sum(j)-sum(i-1);
		t%=MOD; if (t<0) t+=MOD;
		ans+=t*k%MOD;
		ans%=MOD;
		i=j+1;
	}
	return ans;
}

int main(){
	//printf("%I64d\n",cal2(10,10));
	//printf("%I64d",sum(5));
	LL n,m; scanf("%lld%lld",&n,&m);
	//printf("%I64d\n",cal(n,n)*cal(m,m)%MOD);
	printf("%lld",( cal1(n,n)*cal1(m,m)%MOD - cal2(n,m) + MOD )%MOD );
	return 0;
}
Problem3124

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef long long LL;

void readint(int &x){
	x=0;
	char c=getchar();
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
}

const int N=210000;

struct E{ int to; LL dis; int ne; } e[N<<1];
int n,la[N],e_top;

void add(int x, int y, LL z){
	e[++e_top]=(E){y,z,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,z,la[y]}; la[y]=e_top;
}

LL dis[N], fadis[N];
int fa[N], q[N], l,r;

int bfs(int x){
	//forto(i,1,n) dis[i]=-1;
	dis[x]=0;
	q[l=r=1]=x;
	int ans=x;

	while (l<=r){
		x=q[l++];
		for(int i=la[x]; i; i=e[i].ne){
			int y=e[i].to; LL z=e[i].dis;
			if (dis[y]==-1){
				dis[y]=dis[x]+z;
				if (dis[y]>dis[ans]) ans=y;
				fa[y]=x;
				fadis[y]=z;
				q[++r]=y;
			}
		}
	}
	return ans;
}

int lis[N], top;
LL d[N], f[N];

int main(){
	readint(n);
	forto(i,2,n){
		int x,y,z; readint(x); readint(y); readint(z);
		add(x,y,z);
	}
	forto(i,1,n) dis[i]=-1;
	int x=bfs(1);
	forto(i,1,n) dis[i]=-1;
	int y=bfs(x);
	printf("%lld\n",dis[y]);
	
	while (y!=x){
		lis[++top]=y;
		d[top]=fadis[y];
		y=fa[y];
	}
	lis[++top]=x;
	
	forto(i,1,n) dis[i]=-1;
	forto(i,1,top){
		if (i!=1) dis[lis[i-1]]=0;
		if (i!=top) dis[lis[i+1]]=0;
		int t=bfs(lis[i]);
		f[i]=dis[t];
		//printf("!! %d\n",lis[i]);
	}
	
	int ltop=1, t=0;
	forto(i,2,top){
		t+=d[i-1];
		if (f[i]==t) ltop=i;
		//printf("%d %lld\n",t,f[i]);
	}
	
	int rtop=top; t=0;
	fordown(i,top-1,1){
		t+=d[i];
		if (f[i]==t) rtop=i;
	}
	
	//printf("%d %d\n",ltop,rtop);
	printf("%d\n",MAX(0,rtop-ltop));
	return 0;
}
Problem3172

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=1100000, alpha=27;

int fa[N<<1],to[N<<1][alpha],len[N<<1],top=1,now=1;
int cnt[N<<1];

void add(int c){
	int x=now;
	len[now=++top]=len[x]+1;
	for(;x&&!to[x][c];x=fa[x]) to[x][c]=now;
	if (!x){ fa[now]=1; return; }
	int y=to[x][c];
	if (len[y]==len[x]+1){ fa[now]=y; return; }
	int z=++top;
	len[z]=len[x]+1;
	fa[z]=fa[y];
	forto(i,0,alpha-1) to[z][i]=to[y][i];
	fa[y]=fa[now]=z;
	for(;x&&to[x][c]==y;x=fa[x]) to[x][c]=z;
}

//    void add(int x) {
//        int now=last, a=++cnt; last=a;
//        l[a]=l[now]+1;
//        for(; now && !c[now][x]; now=f[now]) c[now][x]=a;
//        if(!now) { f[a]=root; return; }
//        int q=c[now][x];
//        if(l[q]==l[now]+1) { f[a]=q; return; }
//        int b=++cnt;
//        memcpy(c[b], c[q], sizeof c[q]);
//        l[b]=l[now]+1;
//        f[b]=f[q];
//        f[q]=f[a]=b;
//        for(; now && c[now][x]==q; now=f[now]) c[now][x]=b;
//    }

//void add(int c){
//	len[++top]=len[la]+1;
//	for(;la&&!to[la][c];la=fa[la]) to[la][c]=top;
//	if (!la) fa[la=top]=1; else{
//		int x=top, y=to[la][c], z=la;
//		if (len[y]==len[z]+1) fa[x]=y; else{
//			len[++top]=len[z]+1;
//			fa[x]=fa[y]=top; 
//			printf("top=%d z=%d\n",top,z);
//			fa[top]=fa[y];
//			forto(i,0,alpha-1) to[top][i]=to[y][i];
//			for(;z&&to[z][c]==y;z=fa[z]) to[z][c]=top;
//		}
//		la=x;
//	}
//}

char s[N];
int cd[N<<1],sta[N<<1],sta_top;

void count(){
	int k=1;
	for(int i=0;s[i];i++){
		k=to[k][s[i]-'a'];
		cnt[k]++;
	}
	//forto(i,1,top) printf("cnt[%d]=%d\n",i,cnt[i]);
	
	forto(i,2,top) cd[fa[i]]++;
	forto(i,2,top) if (cd[i]==0) sta[++sta_top]=i;
	while (sta_top){
		int x=sta[sta_top--];
		cnt[fa[x]]+=cnt[x];
		if (--cd[fa[x]]==0) sta[++sta_top]=fa[x];
	}
}	

int main(){
	int len=0,n; scanf("%d",&n);
	forto(i,1,n){
		scanf("%s",s+len);
		for(;s[len];len++) add(s[len]-'a');
		add(26); s[len++]='a'+26;
	}
	//printf("%s\n",s);
	//fordown(i,top,2) cnt[fa[i]]+=cnt[i];
	//fordown(i,top,1)
	//forto(j,0,alpha-1) if (to[i][j]) f[i]+=f[to[i][j]];
	//forto(i,1,top) printf("to[%d][a]=%d to[%d][#]=%d\n",i,to[i][0],i,to[i][26]);
	//forto(i,1,top) printf("fa[%d]=%d\n",i,fa[i]);
	
	count();
	
	//forto(i,1,top) printf("cnt[%d]=%d\n",i,cnt[i]);
	
	len=0;
	forto(i,1,n){
		int k=1;
		for(;s[len]!='a'+26;len++) k=to[k][s[len]-'a'];
		//printf("k=%d\n",k);
		printf("%d\n",cnt[k]);
		len++;
	}
	return 0;
}
Problem3172

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=1100000, alpha=27;

int fa[N<<1],to[N<<1][alpha],len[N<<1],top=1,now=1,cnt[N<<1];

void add(int c){
	int x=now;
	len[now=++top]=len[x]+1;
	cnt[now]++;
	for(;x&&!to[x][c];x=fa[x]) to[x][c]=now;
	if (!x){ fa[now]=1; return; }
	int y=to[x][c];
	if (len[y]==len[x]+1){ fa[now]=y; return; }
	int z=++top;
	len[z]=len[x]+1;
	fa[z]=fa[y];
	forto(i,0,alpha-1) to[z][i]=to[y][i];
	fa[y]=fa[now]=z;
	for(;x&&to[x][c]==y;x=fa[x]) to[x][c]=z;
}

char s[N];
int cd[N<<1],sta[N<<1],sta_top;

void count(){
	forto(i,2,top) cd[fa[i]]++;
	forto(i,2,top) if (cd[i]==0) sta[++sta_top]=i;
	while (sta_top){
		int x=sta[sta_top--];
		cnt[fa[x]]+=cnt[x];
		if (--cd[fa[x]]==0) sta[++sta_top]=fa[x];
	}
}	

int main(){
	int len=0,n; scanf("%d",&n);
	forto(i,1,n){
		scanf("%s",s+len);
		for(;s[len];len++) add(s[len]-'a');
		add(26); len++;
	}
	count();
	len=0;
	forto(i,1,n){
		int k=1;
		for(;s[len];len++) k=to[k][s[len]-'a'];
		printf("%d\n",cnt[k]);
		len++;
	}
	return 0;
}
Problem3289

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
Problem3669

#include<cstdlib>
#include<cstdio>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=150000+100, M=100000+100, inf=0x7fffffff;

int fa[N],ch[N][2],w[N],mx[N];
bool rev[N];

bool ir(int x){ return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x; }
bool nt(int x){ return ch[fa[x]][1]==x; }

void pd(int x){
	if (rev[x]){
		rev[x]=false;
		rev[ch[x][0]]^=1; rev[ch[x][1]]^=1;
		int t=ch[x][0]; ch[x][0]=ch[x][1]; ch[x][1]=t;
	}
}

void ud(int x){
	mx[x]=x;
	if (w[mx[ch[x][0]]]>w[mx[x]]) mx[x]=mx[ch[x][0]];
	if (w[mx[ch[x][1]]]>w[mx[x]]) mx[x]=mx[ch[x][1]];
}

void rtt(int x){
	int y=fa[x], z=fa[y]; bool p=nt(x);
	if (!ir(y)) ch[z][nt(y)]=x;
	fa[ch[x][!p]]=y; fa[y]=x; fa[x]=z;
	ch[y][p]=ch[x][!p]; ch[x][!p]=y; 
	ud(y);
}

void splay(int x){
	static int sta[N],top,y;
	sta[top=1]=y=x;
	while (!ir(y)) sta[++top]=y=fa[y];
	while (top) pd(sta[top--]);
	while (!ir(x)){
		int y=fa[x];
		if (!ir(y)) rtt(nt(x)^nt(y)?x:y);
		rtt(x);
	}
	ud(x);
}

void access(int x){
	int t=0,y=x;
	while (x){
		splay(x);
		ch[x][1]=t; ud(x);
		t=x; x=fa[x];
	}
	splay(y);
}

void makeroot(int x){
	access(x);
	rev[x]^=1;
}

void link(int x, int y){
	makeroot(x);
	fa[x]=y;
	//printf("link(%d,%d)\n",x,y);
}

void cut(int x, int y){
	makeroot(x);
	access(y);
	ch[y][0]=fa[x]=0;
	//printf("cut(%d,%d)\n",x,y);
}

bool check(int x, int y){
	makeroot(x);
	makeroot(y);
	return fa[x];
}

int query(int x, int y){
	makeroot(x);
	access(y);
	return mx[y];
}

struct E{ int x,y,a,b; } e[M];
int s[M];
bool comp(int l, int r){ return e[l].a<e[r].a; }

int main(){
	int n,m; scanf("%d%d",&n,&m);
	forto(i,1,m) scanf("%d%d%d%d",&e[i].x,&e[i].y,&e[i].a,&e[i].b);
	forto(i,1,m) s[i]=i;
	std::sort(s+1,s+m+1,comp);
	
	//printf("!!\n");
	
	int ans=inf;
	forto(i,1,m){
		int t=s[i], x=e[t].x, y=e[t].y, a=e[t].a, b=e[t].b;
		if (x==y) continue;
		
		//printf("i=%d t=%d\n",i,t);
		
		w[n+t]=b; mx[n+t]=n+t;
		if (check(x,y)){
			int q=query(x,y);
			if (b<w[q]){
				
				//printf("w[%d]=%d\n",q,w[q]);
				
				cut(q,e[q-n].x);
				cut(q,e[q-n].y);
				link(n+t,x);
				link(n+t,y);
			}
		} else {
			link(n+t,x);
			link(n+t,y);
		}
		
		if (check(1,n)){
			int q=query(1,n);
			if (a+w[q]<ans) ans=a+w[q];
			//printf("a=%d w[%d]=%d\n",a,q,w[q]);
			//forto(i,1,n+m) printf("fa[%d]=%d nt[%d]=%d ir[%d]=%d\n",i,fa[i],i,nt(i),i,ir(i));
		}
		
		//printf("ans=%d\n\n",ans);
	}
	
	//printf("!!\n");
	printf("%d",ans!=inf?ans:-1);
	return 0;
}
Problem3673

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=1000000;

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
	
int a[20004];

int main(){
	int n,m; scanf("%d%d",&n,&m);
	build(++top,1,n);
	a[0]=1;
	
	//forto(i,1,top) printf("rc[%d]=%d\n",i,rc[i]);
	//forto(i,1,n) printf("get(%d)=%d\n",i,get(a[0],1,n,i));
	//printf("%d\n",m);
	
	forto(i,1,m){
		int t; scanf("%d",&t);
		if (t==1||t==3){
			int x,y; scanf("%d%d",&x,&y);
			while (true){
				int fx=get(a[i-1],1,n,x);
				if (fx==x) break;
				x=fx;
			}
			while (true){
				int fy=get(a[i-1],1,n,y);
				if (fy==y) break;
				y=fy;
			}
			if (t==1) a[i]=change(a[i-1],1,n,x,y);
			if (t==3){
				printf("%d\n",x==y);
				a[i]=a[i-1];
			}
		}
		if (t==2){
			int k; scanf("%d",&k);
			a[i]=a[k];
		}
		//printf("a[%d]=%d\n",i,a[i]);
	}
	return 0;
}
Problem3674

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
Problem3676

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=300000+100, alpha=26;
typedef long long LL;

int n,s[N],num[N];
int p,last,next[N][alpha],fail[N],len[N],cnt[N];

void init(){
	s[n=0]=len[p=2]=-1;
	fail[fail[last=1]=2]=2;
}

int getfail(int x){
	//printf("in getfail\n");
	while (s[n-len[x]-1]!=s[n]){
		//printf("fail[%d]=%d\n",x,fail[x]);
		x=fail[x];
	}
	//printf("out getfail\n");
	return x;
}

void add(int c){
	s[++n]=c;
	int cur=getfail(last);
	if (!next[cur][c]){
		len[++p]=len[cur]+2;
		fail[p]=next[getfail(fail[cur])][c];
		if (!fail[p]) fail[p]=1;
		next[cur][c]=p;
	}
	last=next[cur][c];
	cnt[last]++;
	//printf("%d %d\n",last,fail[last]);
}

void count(){
	fordown(i,p,3) cnt[fail[i]]+=cnt[i];
}	

char str[N];

int main(){
	scanf("%s",str);
	init();
	for(int i=0;str[i];i++){
		add(str[i]-'a');
		//forto(i,1,p) printf("len[%d]=%d fail[%d]=%d\n",i,len[i],i,fail[i]);
		//printf("\n");
	}
	count();
	LL max=0;
	forto(i,3,p){
		//printf("%d %d %d %d\n",i,len[i],cnt[i],fail[i]);
		if (LL(len[i])*LL(cnt[i])>max) max=LL(len[i])*LL(cnt[i]);
	}
	printf("%lld\n",max);
	return 0;
}
Problem3676

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=300000+100, alpha=26;
typedef long long LL;

int n,s[N];
int p,last,next[N][alpha],fail[N],len[N],cnt[N];

void init(){
	s[n=0]=len[p=1]=-1;
	fail[0]=1;
}

int getfail(int x){
	while (s[n-len[x]-1]!=s[n]) x=fail[x];
	return x;
}

void add(int c){
	s[++n]=c;
	int cur=getfail(last);
	if (!next[cur][c]){
		len[++p]=len[cur]+2;
		fail[p]=next[getfail(fail[cur])][c];
		next[cur][c]=p;
	}
	last=next[cur][c];
	cnt[last]++;
}

void count(){
	fordown(i,p,2) cnt[fail[i]]+=cnt[i];
}	

char str[N];

int main(){
	scanf("%s",str);
	init();
	for(int i=0;str[i];i++) add(str[i]-'a');
	count();
	LL max=0;
	forto(i,2,p) if (LL(len[i])*LL(cnt[i])>max) max=LL(len[i])*LL(cnt[i]);
	printf("%lld\n",max);
	return 0;
}
Problem3884

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;

int phi(int x){
	int ans=x;
	for(int i=2;i*i<=x;i++)
	if (x%i==0){
		ans=ans/i*(i-1);
		while (x%i==0) x/=i;
	}
	if (x!=1){ ans=ans/x*(x-1); }
	return ans;
}

int pow(int b, int n){
	if (b==0) return 1%n;
	int p=pow(b>>1,n);
	p=LL(p)*LL(p)%n;
	if (b&1) p=LL(p)*LL(2)%n;
	return p;
}

int solve(int p){
	if (p==1) return 0;
	//printf("%d\n",p);
	int k=0;
	while ((p&1)==0){
		p>>=1;
		k++;
		//printf("!!");
	}
	int ph=phi(p);
	int z=solve(ph)-k;
	z%=ph; if (z<0) z+=ph;
	//printf("p=%d\n",p);
	int t=pow(z,p);
	return t<<k;
}

int main(){
	//printf("%d\n",phi(1));
	int t; scanf("%d",&t);
	while (t--){
		int p; scanf("%d",&p);
		printf("%d\n",solve(p));
	}
	return 0;
}
Problem4300

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MAX(a,b) ((a)>(b)?(a):(b))

int n,f[31];

int main(){
	scanf("%d",&n);
	int ans=0;
	while (n--){
		int x; scanf("%d",&x);
		int t=1;
		forto(i,0,30) if (1<<i&x) t=MAX(t,f[i]+1);
		ans=MAX(ans,t);
		forto(i,0,30) if (1<<i&x) f[i]=MAX(f[i],t);
	}
	printf("%d\n",ans);
}
Problem4337

#include<cstdlib>
#include<cstdio>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=100;

struct E{ int to,ne; } e[N<<1];
int n,la[N],e_top;

void add(int x, int y){
	e[++e_top]=(E){y,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,la[y]}; la[y]=e_top;
}

int f[N];

void dfs(int x){
	int a[N], top=0;
	f[x]=0; a[++top]=1;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (f[y]==-1){
			dfs(y);
			a[++top]=f[y];
		}
	}
	std::sort(a+1,a+top+1);
	forto(i,1,top) f[x]=f[x]*10077+a[i];
}

int lis[N];

int gethash(){
	scanf("%d",&n);
	e_top=0;
	forto(i,1,n) la[i]=0;
	forto(i,1,n){
		int j; scanf("%d",&j);
		if (j) add(i,j);
	}
	forto(k,1,n){
		forto(i,1,n) f[i]=-1;
		dfs(k);
		lis[k]=f[k];
	}
	std::sort(lis+1,lis+n+1);
	int ans=0;
	forto(i,1,n) ans=ans*10007+lis[i];
	return ans;
}

int h[N];

int main(){
	int t; scanf("%d",&t);
	forto(i,1,t) h[i]=gethash();
	forto(i,1,t){
		int j=1; while (h[i]!=h[j]) j++;
		printf("%d\n",j);
	}	
	return 0;
}
	
Problem4403

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;

const int MOD=1000003;

LL fac[MOD],inv[MOD];

LL C(int n, int m){
	if (n<m) return 0;
	if (n<MOD&&m<MOD) return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
	return C(n/MOD,m/MOD)*C(n%MOD,m%MOD)%MOD;
}	

int main(){
	fac[0]=1;
	forto(i,1,MOD-1) fac[i]=fac[i-1]*i%MOD;
	inv[1]=1;
	forto(i,2,MOD-1) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	inv[0]=1;
	forto(i,1,MOD-1) inv[i]=inv[i-1]*inv[i]%MOD;
	
	int t; scanf("%d",&t);
	while (t--){
		int n,l,r; scanf("%d%d%d",&n,&l,&r);
		int m=r-l+1;
		printf("%d\n",int(C(n+m,n)-1+MOD)%MOD);
	}
	return 0;
}
Problem4403

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;

const int MOD=1000003;

LL fac[MOD],inv[MOD];

LL C(int n, int m){
	LL ans=1;
	while (n||m){
		int a=n%MOD, b=m%MOD;
		n/=MOD; m/=MOD;
		if (a<b) return 0;
		ans= ans *fac[a]%MOD *inv[b]%MOD *inv[a-b]%MOD;
	}
	return ans;
}	

int main(){
	fac[0]=1;
	forto(i,1,MOD-1) fac[i]=fac[i-1]*i%MOD;
	inv[1]=1;
	forto(i,2,MOD-1) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	inv[0]=1;
	forto(i,1,MOD-1) inv[i]=inv[i-1]*inv[i]%MOD;
	
	int t; scanf("%d",&t);
	while (t--){
		int n,l,r; scanf("%d%d%d",&n,&l,&r);
		int m=r-l+1;
		printf("%d\n",int(C(n+m,n)-1+MOD)%MOD);
	}
	return 0;
}
Problem4403

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

typedef long long LL;

const int MOD=1000003;

LL fac[MOD],inv[MOD];

LL C(int n, int m){
	LL ans=1;
	while (n!=m){
		int a=n%MOD, b=m%MOD;
		n/=MOD; m/=MOD;
		if (a<b) return 0;
		ans= ans *fac[a]%MOD *inv[b]%MOD *inv[a-b]%MOD;
	}
	return ans;
}	

int main(){
	fac[0]=1;
	forto(i,1,MOD-1) fac[i]=fac[i-1]*i%MOD;
	inv[1]=1;
	forto(i,2,MOD-1) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	inv[0]=1;
	forto(i,1,MOD-1) inv[i]=inv[i-1]*inv[i]%MOD;
	
	int t; scanf("%d",&t);
	while (t--){
		int n,l,r; scanf("%d%d%d",&n,&l,&r);
		int m=r-l+1;
		printf("%d\n",int(C(n+m,n)-1+MOD)%MOD);
	}
	return 0;
}
Problem4405

#include<cstdlib>
#include<cstdio>
 
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=la[x];i;i=e[i].ne)
 
const int N=700, M=100000;

struct E{ int to,ne; } e[M<<1];
int n,la[N],e_top;
 
void add(int x, int y){
    e[++e_top]=(E){y,la[x]}; la[x]=e_top;
    e[++e_top]=(E){x,la[y]}; la[y]=e_top;
}
 
int f[N];
int find(int x){ return (f[x]==x)?x:(f[x]=find(f[x])); }

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
		if (find(x)==x) f[x]=g;
		if (find(mat[x])==mat[x]) f[mat[x]]=g;
		y=mat[x]; x=pre[y];
	}
}

bool match(int x){
	forto(i,1,n){ cond[i]=-1; pre[i]=0; f[i]=i; }
	cond[q[l=r=1]=x]=0;
	while (l<=r){
		int x=q[l++];
		forE(i,x){
			int y=e[i].to;
			if (cond[y]==-1){
				cond[y]=1; pre[y]=x;
				if (mat[y]==0){
					while (x){
						int las=mat[x];
						mat[x]=y; mat[y]=x;
						y=las; x=pre[y];
					}
					return true;
				}
				cond[q[++r]=mat[y]]=0;
			} else if (find(x)!=find(y)&&cond[y]==0){
				int g=lca(x,y); blossom(x,y,g); blossom(y,x,g);
			}
		}
	}
	return false;
}
 
 
int main(){
    int t; scanf("%d",&t);
    while (t--){
        int a,b,ee; scanf("%d%d%d",&a,&b,&ee);
        n=a+b*3;
         
        forto(i,1,n) mat[i]=la[i]=vis[i]=0;
        e_top=0; vt=0;
        
        forto(i,1,b) add((i-1)*3+1,(i-1)*3+2);
        while (ee--){
            int x,y; scanf("%d%d",&x,&y);
            add(b*3+x,(y-1)*3+1);
            add(b*3+x,(y-1)*3+2);
            add(b*3+x,(y-1)*3+3);
        }
        
        int ans=0;
        forto(i,1,n) if (!mat[i]&&match(i)) ans++;
        
        printf("%d\n",ans-a);
    }
    return 0;
}

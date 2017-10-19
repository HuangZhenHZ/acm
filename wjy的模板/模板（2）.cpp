Trie

void add(char c){
    if(!ch[las][c-='a'])ch[las][c]=++tot;
    las=ch[las][c];
}


KMP

for(i=1;s[i];f[i+1]=s[i]==s[j]?j+1:0,i++)
for(j=f[i];j&&s[i]!=s[j];j=f[j]);


AC自动机

//ch是建好的Trie
void build_AC(){
    for(q[l=r=0]=0;l<=r;l++)
    for(int i=0,j;i<26;i++)
    if(j=ch[q[l]][i]){
        if(q[++r]=j,q[l])fail[j]=ch[fail[q[l]]][i];
    }
    else ch[q[l]][i]=ch[fail[q[l]]][i];
}


回文自动机

int nn(int l){return len[tot]=l,tot++;}//new_node
int gf(int x){//get_fail
    while(s[n-1-len[x]]!=s[n])x=fail[x];
    return x;
}
void add(char c){
    if(las=gf(las),!ch[las][c-='a']){
        now=nn(len[las]+2);
        fail[now]=ch[gf(fail[las])][c];
        ch[las][c]=now;
    }
    las=ch[las][c],f[las]++;
}


SA带height

#define cmp(u,v) (x[u]!=x[v]||x[u+k]!=x[v+k])
for(i=1;i<=n;i++)c[x[i]=s[i]-'a'+1]++;
for(i=1;i<=m;i++)c[i]+=c[i-1];
for(i=n;i;i--)sa[c[x[i]]--]=i;
for(k=1;k<n&&(k==1||m<n);k<<=1,T=x,x=y,y=T){
    for(yt=0,i=n-k+1;i<=n;i++)y[++yt]=i;
    for(i=1;i<=n;i++)if(sa[i]>k)y[++yt]=sa[i]-k;
    for(i=1;i<=m;i++)c[i]=0;
    for(i=1;i<=n;i++)c[x[i]]++;
    for(i=1;i<=m;i++)c[i]+=c[i-1];
    for(i=n;i;i--)sa[c[x[y[i]]]--]=y[i];
    for(m=0,i=1;i<=n;i++)y[sa[i]]=i==1||cmp(sa[i],sa[i-1])?++m:m;
}
for(i=1;i<=n;i++)rk[sa[i]]=i;
for(i=1,k=0;i<=n;hei[rk[i++]]=k)
for(k?k--:0,j=sa[rk[i]-1];s[i+k]==s[j+k];k++);


SAM

class SAM{public:
    int S,tot,las,fail[N],ch[N][26],cnt,len[N];
    SAM(){S=tot=las=1;}
    void add(char c){
        int p=las,np=++tot;
        for(len[np]=len[p]+1;p&&!ch[p][c];p=fail[p])ch[p][c]=np;
        if(las=np,!p)fail[np]=S;
        else if(len[p]+1==len[ch[p][c]])fail[np]=ch[p][c];
        else{
            int q=ch[p][c],r=++tot;
            len[r]=len[p]+1,fail[r]=fail[q],fail[q]=fail[np]=r;
            memcpy(ch[r],ch[q],sizeof(ch[q]));
            for(;p&&ch[p][c]==q;p=fail[p])ch[p][c]=r;
        }
    }
}sam;


快速幂

int power(int t,int k,int p){
    int f=1;
    for(;k;k>>=1,t=1LL*t*t%p)
    if(k&1)f=1LL*f*t%p;
    return f;
}


exgcd

void exgcd(int a,int b,int&x,int&y){
    !b?x=1,y=0:(exgcd(b,a%b,y,x),y-=x*(a/b));
}


线性求逆元

inv[1]=1;
for(int i=2;i<=n;i++)inv[i]=1LL*(p-p/i)*inv[p%i]%p;


线性筛（求phi为例）

for(i=2;i<=n;i++)
for(vis[i]==0?p[++t]=i,phi[i]=i-1:1,j=1;j<=t&&i*p[j]<=n;j++){
    vis[i*p[j]]=1;
    if(i%p[j]==0){
        phi[i*p[j]]=phi[i]*p[j];
        break;
    }
    phi[i*p[j]]=phi[i]*(p[j]-1);
}


Miller-Rabin + Rho

//BZOJ-3667
#include<cstdio>
#include<cstdlib>
typedef long long ll;
ll _,n,x,ans,st;
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
#define abs(x) (x>0?x:-(x))
#define cmax(a,b) (a<b?a=b:1)
ll mul(ll a,ll b,ll p){
    ll tmp=(a*b-(ll)((long double)a/p*b+1e-7)*p);
    return tmp<0?tmp+p:tmp;
}
ll power(ll t,ll k,ll p){
    ll f=1;
    for(;k;k>>=1,t=mul(t,t,p))if(k&1)f=mul(f,t,p);
    return f;
}
bool check(ll a,int k,ll p,ll q){
    ll t=power(a,q,p);
    if(t==1||t==p-1)return 1;
    for(;k--;){
        t=mul(t,t,p);
        if(t==p-1)return 1;
    }
    return 0;
}
bool mr(ll p){
    if(p<=1)return 0;
    if(p==2)return 1;
    if(~p&1)return 0;
    ll q=p-1;int i,k=0;
    while(~q&1)q>>=1,k++;
    for(i=0;i<5;i++)
    if(!check(rand()%(p-1)+1,k,p,q))return 0;
    return 1;
}
ll rho(ll n,ll c){
    ll x=rand()%n,y=x,p=1;
    while(p==1)
        x=(mul(x,x,n)+c)%n,
        y=(mul(y,y,n)+c)%n,
        y=(mul(y,y,n)+c)%n,
        p=gcd(n,abs(x-y));
    return p;
}
void solve(ll n){
    if(n==1)return;
    if(mr(n)){cmax(ans,n);return;}
    if(~n&1)cmax(ans,2),solve(n>>1);
    else{
        ll t=n;
        while(t==n)t=rho(n,rand()%(n-1)+1);
        solve(t),solve(n/t);
    }
}
int main(){
    for(srand(1626),scanf("%lld",&_);_--;){
        scanf("%lld",&x),ans=0;solve(x);
        if(ans==x)puts("Prime");
        else printf("%lld\n",ans);
    }
}


高斯消元

void solve(int n){
    int i,j,k,las;double t;
    for(i=1;i<=n;i++){
        for(t=0,j=i;j<=n;j++)
        if(abs(a[j][i])>t)t=abs(a[j][i]),las=j;
        if(j=las,j!=i)for(k=1;k<=n+1;k++)std::swap(a[i][k],a[j][k]);
        for(j=i+1;j<=n;j++)
        for(t=a[j][i]/a[i][i],k=i;k<=n+1;k++)a[j][k]-=a[i][k]*t;
    }
    for(i=n;i>=1;i--)
    for(a[i][n+1]/=a[i][i],j=i-1;j;j--)a[j][n+1]-=a[j][i]*a[i][n+1];
}


矩阵快速幂

struct M{int m[110][110];}c,t,f;
M operator*(const M&a,const M&b){
    static long long tp[110][110];
    memset(tp,0,sizeof(tp));
    for(int i=0;i<k;i++)
    for(int kk=0;kk<k;kk++)
    for(int j=0;j<k;j++)
    tp[i][j]+=1LL*a.m[i][kk]*b.m[kk][j];
    for(int i=0;i<k;i++)
    for(int j=0;j<k;j++)c.m[i][j]=tp[i][j]%p;
    return c;
}
M power(M t,int k){
    for(f=t,k--;k;k>>=1,t=t*t)if(k&1)f=f*t;
    return f;
}


k阶线性递推-特征多项式

//BZOJ-4161
#include<cstdio>
#define p 1000000007
long long c[4010];
int n,k,u[2010],ans,x;int cnt;
struct P{int s[2010];}f,t;
void mult(P&a,const P&b){
    for(int i=0;i<k+k-1;i++)c[i]=0;
    for(int i=0;i<k;i++)
    for(int j=0;j<k;j++){
        c[i+j]+=1LL*a.s[i]*b.s[j];
        if(c[i+j]>=1LL<<62)c[i+j]%=p;
    }
    for(int i=k+k-2;~i;i--)
    if(c[i]%=p,i>=k){
        for(int j=0;j<k;j++){
            c[i-1-j]+=c[i]*u[j];
            if(c[i-1-j]>=1LL<<62)c[i-1-j]%=p;
        }
        c[i]=0;
    }
    for(int i=0;i<k;i++)a.s[i]=c[i];
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<k;i++)scanf("%d",u+i),u[i]%=p,u[i]<0?u[i]+=p:1;
    for(t.s[1]=f.s[0]=1;n;n>>=1,mult(t,t))if(n&1)mult(f,t);
    for(int i=0;i<k;i++)scanf("%d",&x),x%=p,x<0?x+=p:1,ans=(ans+1LL*x*f.s[i])%p;
    printf("%d\n",ans);
}


拉格朗日插值

#include<cstdio>
#define p 1004535809
#define N 3010
int n,x[N],y[N],q,l,r,x0,sum[N][N],isum[N][N],inv[250010],L[N],R[N],ans;
#define getinv(x) (x>=0?inv[x]:p-inv[-(x)])
int main(){
    scanf("%d",&n);inv[1]=1;
    for(int i=1;i<=n;i++)scanf("%d%d",x+i,y+i);
    for(int i=2;i<=250000;i++)inv[i]=1LL*(p-p/i)*inv[p%i]%p;
    for(int i=1;i<=n;i++){
        sum[i][0]=isum[i][0]=1;
        for(int j=1;j<i;j++)sum[i][j]=1LL*sum[i][j-1]*(p+x[i]-x[j])%p,isum[i][j]=1LL*isum[i][j-1]*getinv(x[i]-x[j])%p;
        sum[i][i]=sum[i][i-1],isum[i][i]=isum[i][i-1];
        for(int j=i+1;j<=n;j++)sum[i][j]=1LL*sum[i][j-1]*(p+x[i]-x[j])%p,isum[i][j]=1LL*isum[i][j-1]*getinv(x[i]-x[j])%p;
    }
    for(scanf("%d",&q);q--;printf("%d\n",ans)){
        scanf("%d%d%d",&l,&r,&x0);L[l-1]=R[r+1]=1;ans=0;
        for(int i=l;i<=r;i++)L[i]=1LL*L[i-1]*(p+x0-x[i])%p;
        for(int i=r;i>=l;i--)R[i]=1LL*R[i+1]*(p+x0-x[i])%p;
        for(int i=l;i<=r;i++)ans=(ans+1LL*sum[i][l-1]*isum[i][r]%p*L[i-1]%p*R[i+1]%p*y[i])%p;
    }
}


牛顿插值

#include<cstdio>
#define N 3010
#define p 1004535809
int n,q,x[N],f[N][N],inv[250010];
#define getinv(x) (x>=0?inv[x]:p-inv[-(x)])
int main(){
    scanf("%d",&n);inv[1]=1;
    for(int i=2;i<=250000;i++)inv[i]=1LL*(p-p/i)*inv[p%i]%p;
    for(int i=1;i<=n;i++)scanf("%d%d",x+i,f[i]+1);
    for(int i=2;i<=n;i++)
    for(int j=2,k=i-1;j<=i;j++,k--)f[i][j]=1LL*(p+f[i-1][j-1]-f[i][j-1])*getinv(x[k]-x[i])%p;
    scanf("%d",&q);
    for(int l,r,x0,ans;q--;printf("%d\n",ans)){
        scanf("%d%d%d",&l,&r,&x0);ans=0;
        for(int i=l,j=1,sum=1;i<=r;i++,j++)ans=(ans+1LL*f[i][j]*sum)%p,sum=1LL*sum*(p+x0-x[i])%p;
    }
}


BSGS

//y^x==z (mod p) ->x=?
scanf("%d%d%d",&y,&z,&p),y%=p,z%=p;j=z;
if(y==0){puts("Cannot find x");continue;}
for(k=s=1;k*k<=p;k++);
std::map<int,int>hash;flag=0;
for(int i=0;i<k;i++,s=1LL*s*y%p,j=1LL*j*y%p)hash[j]=i;
for(int i=1,j=s;i<=k&&!flag;i++,j=1LL*j*s%p)
if(hash.count(j))ans=i*k-hash[j],flag=1;
if(flag==0)puts("Cannot find x");
else printf("%d\n",ans);


阶、原根

bool check(){
    for(i=2;i*i<=p;i++)
    if((p-1)%i==0&&power(g,(p-1)/i,p)==1)return 0;
    return 1;
}
void getroot(){
    if(p==2)g=1;else for(g=2;!check();g++);
    for(ind[1]=0,pw[0]=i=1;i<p-1;i++)pw[i]=pw[i-1]*g%p,ind[pw[i]]=i;
}


exBSGS

int bsgs(int a,ll b,int p){
    if(a%=p,b%=p,b==1)return 0;
    ll t=1;int f,g,delta=0,m=sqrt(p)+1,i;
    for(g=gcd(a,p);g!=1;g=gcd(a,p)){
        if(b%g)return -1;
        b/=g,p/=g,t=t*(a/g)%p,delta++;
        if(b==t)return delta;
    }
    std::map<int,int>hash;
    for(i=0;i<m;i++,b=b*a%p)hash[b]=i;
    for(i=1,f=power(a,m);i<=m+1;i++)
    if(t=t*f%p,hash.count(t))return i*m-hash[t]+delta;
    return -1;
}


O(n^{2/3})求phi/miu的前缀和

//BZOJ-3944
#include<cstdio>
#include<cmath>
typedef long long ll;
typedef unsigned U;
const ll oo=1LL<<60;
#define N 1<<22
const int M=(1<<18)-1;
int n,k,p[N],t,vis[N],T,a[20];ll phi[N],miu[N];
class map{public:
    int et,la[M+1];
    struct E{int nxt;U x;ll ans;}e[1<<18];
    inline ll find(U x){
        for(int i=la[x&M];i;i=e[i].nxt)
        if(e[i].x==x)return e[i].ans;
        return -oo;
    }
    inline void ins(U x,ll ans){
        e[++et]=(E){la[x&M],x,ans},la[x&M]=et;
    }
}_phi,_miu;
ll getphi(U n){
    if(n<=k)return phi[n];
    ll ans=_phi.find(n);
    if(ans!=-oo)return ans;ans=n*(n+1LL)/2;
    for(U l=2,r;l<=n;l=r+1)r=n/(n/l),ans-=(r-l+1)*getphi(n/l);
    return _phi.ins(n,ans),ans;
}
ll getmiu(U n){
    if(n<=k)return miu[n];
    ll ans=_miu.find(n);
    if(ans!=-oo)return ans;ans=1;
    for(U l=2,r;l<=n;l=r+1)r=n/(n/l),ans-=(r-l+1)*getmiu(n/l);
    return _miu.ins(n,ans),ans;
}
int main(){
    scanf("%d",&T);
    for(int i=1;i<=T;i++)scanf("%d",a+i),n<a[i]?n=a[i]:1;
    k=2.5*pow(n,2.0/3)+1;phi[1]=miu[1]=1;
    for(int i=2;i<=k;i++){
        if(!vis[i])p[++t]=i,phi[i]=i-1,miu[i]=-1;
        for(int j=1;j<=t&&i*p[j]<=k;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0){
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            phi[i*p[j]]=phi[i]*phi[p[j]],miu[i*p[j]]=-miu[i];
        }
    }
    for(int i=2;i<=k;i++)phi[i]+=phi[i-1],miu[i]+=miu[i-1];
    for(int i=1;i<=T;i++)printf("%lld %lld\n",getphi(a[i]),getmiu(a[i]));
}


单纯形

struct LP{
    int n,m;ld a[10010][1010],b[10010],c[1010],v;
    void setup(int _n,int _m){
        n=_n,m=_m,v=0;
    }
    void pivot(int l,int e){
        int i,j;
        for(j=1;j<=n;j++)if(j!=e)a[l][j]/=a[l][e];
        b[l]/=a[l][e],a[l][e]=1/a[l][e];
        for(i=1;i<=m;i++)
        if(i!=l&&std::fabs(a[i][e])>eps){
            for(j=1;j<=n;j++)if(j!=e)a[i][j]-=a[i][e]*a[l][j];
            b[i]-=a[i][e]*b[l],a[i][e]*=-a[l][e];
        }
        for(j=1;j<=n;j++)if(j!=e)c[j]-=c[e]*a[l][j];
        v+=c[e]*b[l],c[e]*=-a[l][e];
    }
    ld simplex(){
        int i,l,e;ld tmp;
        while(1){tmp=eps;e=n+1;
            for(i=1;i<=n;i++)if(c[i]>tmp)tmp=c[i],e=i;
            if(e==n+1)return v;
            tmp=oo;
            for(i=1;i<=m;i++)
            if(a[i][e]>eps&&b[i]/a[i][e]<tmp)tmp=b[i]/a[i][e],l=i;
            if(tmp==oo)return tmp;
            pivot(l,e);
        }
    }
}dcx;


FFT

for(k=1;k<n<<1;k<<=1,L++);L--;
for(i=1;i<k;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<L);
for(i=0;i<=k;i++)w[1][k-i]=w[0][i]=(P){cos(PI*2*i/k),sin(PI*2*i/k)};
 
void FFT(P*a,int n,P*w){
    int i,j,k;
    for(i=1;i<n;i++)if(i>rev[i])std::swap(a[i],a[rev[i]]);
    for(i=2;i<=n;i<<=1)
    for(j=0;j<n;j+=i)
    for(k=0;k<i>>1;k++)
    tmp=a[j+k+i/2]*w[n/i*k],a[j+k+i/2]=a[j+k]-tmp,a[j+k]=a[j+k]+tmp;
}


NTT
 
#define ck(x) (x>=p?x-=p:1)
for(n=1;n<m;n<<=1,l++);n<<=1;g=power(3,(P-1)/n);
for(w[0][0]=w[1][0]=i=1;i<n;i++){
    w[1][n-i]=w[0][i]=g*w[0][i-1]%P;
    rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
}
 
void FFT(int*a,int*w){
    int i,j,k,tmp;
    for(i=0;i<n;i++)if(i>rev[i])tmp=a[i],a[i]=a[rev[i]],a[rev[i]]=tmp;
    for(i=2;i<=n;i<<=1)
    for(j=0;j<n;j+=i)
    for(k=0;k<i>>1;k++)
    tmp=1LL*a[j+k+i/2]*w[n/i*k]%p,a[j+k+i/2]=a[j+k]-tmp+p,a[j+k]+=tmp,ck(a[j+k+i/2]),ck(a[j+k]);
}
 

多项式求逆

#include<cstdio>
#include<algorithm>
#define N 1<<18|10
#define p 1004535809
int n,l,k,w[2][N],rev[N],a[N],b[N],c[N],g,tot=1<<18;
int power(int t,int k){
    int f=1;
    for(;k;k>>=1,t=1LL*t*t%p)if(k&1)f=1LL*f*t%p;
    return f;
}
#define ck(x) (x>=p?x-=p:1)
void FFT(int*a,int n,int*w){
    int i,j,k,l,tmp;
    for(i=1;i<n;i++)if(rev[i]<i)tmp=a[rev[i]],a[rev[i]]=a[i],a[i]=tmp;
    for(i=2;i<=n;i<<=1)
    for(l=i>>1,j=0;j<n;j+=i)
    for(k=0;k<l;k++)
    tmp=1LL*a[j+k+l]*w[tot/i*k]%p,a[j+k+l]=a[j+k]-tmp+p,a[j+k]+=tmp,ck(a[j+k+l]),ck(a[j+k]);
}
void getinv(int deg,int*a,int*b){
    if(deg==1){
        b[0]=power(a[0],p-2);
        return;
    }
    getinv(deg+1>>1,a,b);
    for(l=0,k=1;k<deg;k<<=1,l++);k<<=1;
    for(int i=0;i<k;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
    std::copy(a,a+deg,c);
    std::fill(c+deg,c+k,0);
    FFT(b,k,w[0]),FFT(c,k,w[0]);
    for(int i=0;i<k;i++)b[i]=(2-1LL*c[i]*b[i]%p)*b[i]%p+p,ck(b[i]);
    FFT(b,k,w[1]);g=power(k,p-2);
    for(int i=0;i<k;i++)b[i]=1LL*b[i]*g%p;
    std::fill(b+deg,b+k,0);
}
int main(){
    w[0][0]=w[1][0]=1;g=power(3,(p-1)/tot);
    for(k=1;k<=tot;k++)w[0][k]=w[1][tot-k]=1LL*g*w[0][k-1]%p;
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",a+i);
    getinv(n,a,b);
    for(int i=0;i<n;i++)printf("%d ",b[i]);puts("");
}


很龊很龊的找规律

//还是若干年前写的。。。找线性递推规律
#include<cstdio>
typedef long long ll;
const int MAXS=1000;
double a[MAXS][MAXS+1],temp;
void swap(double&i,double&j){temp=i;i=j;j=temp;}
double abs(double a){return a>0?a:-a;}
void solve(ll n){
    ll i,j,k,lasi;double t,maxi;
    for(i=1;i<=n;i++){
        maxi=0;
        for(j=i;j<=n;j++)
        if(abs(a[j][i])>maxi){
            maxi=abs(a[j][i]);lasi=j;
        }j=lasi;
        if(j!=i)for(k=1;k<=n+1;k++)swap(a[i][k],a[j][k]);
        for(j=i+1;j<=n;j++){
            t=a[j][i]/a[i][i];
            for(k=i;k<=n+1;k++)a[j][k]-=a[i][k]*t;
        }
    }
    for(i=n;i>=1;i--){
        a[i][n+1]/=a[i][i];
        for(j=i-1;j>=1;j--)
            a[j][n+1]-=a[j][i]*a[i][n+1];
    }
}
ll f[1000],n,k,ans,
F[1000]={3,9,13,25,81,225,477,1089,2785,6889,16237,38809,94641,229441,551613,1329409,3215041};
 
int main()
{
    int i,j,k;double ans;
    n=15;
    for(int l=2;l<=n;l++)
    {
        for(i=1;i<=l;i++)
        for(j=i;j<=i+l;j++)
        a[i][j-i+1]=F[j];
//      for(i=1;i<=l;i++){for(j=1;j<=l+1;j++)printf("%.0lf ",a[i][j]);printf("\n");}
        solve(l);
        for(i=1;i<=l;i++)printf("%.5lf ",a[i][l+1]);printf("\n");
        getchar();
    }
}


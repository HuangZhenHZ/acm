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

FastIn+FastGetchar 

char ch,B[1<<15],*S=B,*T=B;
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?0:*S++)
#define isd(c) (c>='0'&&c<='9')
int aa,bb;int F(){
    while(ch=getc(),!isd(ch)&&ch!='-');ch=='-'?aa=bb=0:(aa=ch-'0',bb=1);
    while(ch=getc(),isd(ch))aa=aa*10+ch-'0';return bb?aa:-aa;
}


FastOut+FastPutchar

char U[1<<15|1],*O=U,*W=U+(1<<15),stk[20],ts;
#define mod 1000000000
#define putc(c) (O==W?fwrite(U,1,1<<15,stdout),O=U,1:1,*O++=c)
#define pr(x) (x>=mod?pri(x/mod),pr9(x%mod):pri(x))
void pri(int x){
    if(!x)putc('0');else{
        for(ts=0;x;x/=10)stk[++ts]=x%10+'0';
        for(;ts;putc(stk[ts--]));
    }
}
void pr9(int x){
    for(ts=1;ts<=9;ts++)stk[ts]=x%10+'0',x/=10;
    for(ts=9;ts;putc(stk[ts--]));
}


并查集
int fa[N];
int gf(int x){
    return fa[x]==x?x:fa[x]=gf(fa[x]);
}


二叉堆
//若干年前写的= =自从用上了priority_queue之后就再也不想写了虽然某次CTSC被卡过常数555
int hr;struct H{int n,d;}h[M];
void ins(const H&t){
    int i;
    for(i=++hr;i!=1&&t.d<h[i>>1].d;i>>=1)h[i]=h[i>>1];
    h[i]=t;
}
void dlt(){
    hr--;int i;
    for(i=1;(i<<1)<=hr&&!(h[hr+1].d<=h[i<<1].d&&h[hr+1].d<=h[i<<1|1].d);)
    i<<1!=hr&&h[i<<1|1].d<h[i<<1].d?(h[i]=h[i<<1|1],i=i<<1|1):(h[i]=h[i<<1],i=i<<1);
    h[i]=h[hr+1];
}


hash_table

const int M=(1<<20)-1;
class HASH{public:
    int la[1<<20],et;
    struct E{long long key;int f,nxt;}e[N];
    void clr(){et=0;}
    inline void add(long long x,int f){
        for(int i=la[x&M];i;i=e[i].nxt)
        if(e[i].key==x){
            e[i].f=f;return;
        }
        e[++et]=(E){x,f,la[x&M]},la[x&M]=et;
    }
    inline void del(long long x){
        la[x&M]=0;
    }
    inline int query(long long x){
        for(int i=la[x&M];i;i=e[i].nxt)
        if(e[i].key==x)return e[i].f;
        return -1;
    }
}hash;


树状数组
int n,z[N];
void add(int t,int x){
    for(;t<=n;t+=t&-t)z[t]+=x;
}
int getsum(int t){
    int f=0;
    for(;t;t-=t&-t)f+=z[t];
    return f;
}


zkw_Segtree

//单点修改区间查询
for(n=F(),m=F(),d=1;d<n;d<<=1);
for(i=0;i<n;i++)t[i+d]=F();
for(i=d-1;i;i--)t[i]=t[i<<1]>t[i<<1|1]?t[i<<1]:t[i<<1|1];
while(m--)
if(F())for(t[i=d+F()-1]=F();i>>=1;t[i]=t[i<<1]>t[i<<1|1]?t[i<<1]:t[i<<1|1]);
else{
    for(l=F()+d-2,r=F()+d,o=0;l^r^1;l>>=1,r>>=1)
        ~l&1&&o<t[l^1]?o=t[l^1]:1,
         r&1&&o<t[r^1]?o=t[r^1]:1;
    printf("%d\n",o);
}


斜堆
int merge(int x,int y){
    if(!x||!y)return x|y;
    if(v[x]<v[y])swap(x,y);
    R[x]=merge(R[x],y);swap(L[x],R[x]);
    return x;
}


可持久化Treap
struct T{int l,r,siz;char ch;}t[1<<23];
#define ls t[o].l
#define rs t[o].r
int merge(int l,int r){
    if(!l||!r)return l+r;int o=++tot;
    if(rand()%(t[l].siz+t[r].siz)<t[l].siz)
    t[o]=t[l],rs=merge(rs,r);
    else t[o]=t[r],ls=merge(l,ls);
    t[o].siz=t[l].siz+t[r].siz;
    return o;
}
void split(int x,int k,int&l,int&r){
    if(!x){l=r=0;return;}int o=++tot;t[o]=t[x];
    if(t[ls].siz>=k)split(ls,k,l,r),ls=r,r=o;
    else split(rs,k-1-t[ls].siz,l,r),rs=l,l=o;
    t[o].siz=t[ls].siz+t[rs].siz+1;
}


Splay

int fa[N],son[N],rev[N],siz[N];
#define ls son[o][0]
#define rs son[o][1]
void pu(int t){//push_up
    ...
}
void pd(int t){//push_down
    ...
}
void rtt(int t){//rotate
    int f=fa[t],p=son[f][1]==t;
    (fa[t]=fa[f])?son[fa[f]][son[fa[f]][1]==f]=t:1;
    (son[f][p]=son[t][!p])?fa[son[f][p]]=f:1,
    pu(son[fa[f]=t][!p]=f);
}
void pv(int t,int r){//preview
    if(fa[t]!=r)pv(fa[t]);pd(t);
}
void splay(int t,int root=0){int f;
    for(pv(t,root);fa[t]!=root;rtt(t))
    if(f=fa[t],fa[f]!=root)rtt(son[f][1]==t^son[fa[f]][1]==f?t:f);//把这行删掉就变成了spaly 233
    pu(t);
}
int pre(int o){for(splay(o),o=ls;rs;o=rs);return o;}
int nxt(int o){for(splay(o),o=rs;ls;o=ls);return o;}


主席树

//询问区间第k小
int bt(int g,int l,int r,int x){
    int mid=(l+r)>>1,now=++t0;t[now]=t[g],t[now].x++;
    if(l==r)return now;
    if(x<=mid)t[now].l=bt(t[g].l,l,mid,x);
    else t[now].r=bt(t[g].r,mid+1,r,x);
    return now;
}
int query(int rg,int lg,int x,int l,int r){
    if(l==r)return l;
    int mid=(l+r)>>1,v=t[t[rg].l].x-t[t[lg].l].x;
    if(v>=x)return query(t[rg].l,t[lg].l,x,l,mid);
    else return query(t[rg].r,t[lg].r,x-v,mid+1,r);
}


树链剖分

//BZOJ-1036
int et,la[N],n,q,id[N],fa[N],son[N],siz[N],dep[N],top[N],x,y,i,dfn;
#define swap(x,y) (st=x,x=y,y=st)
struct E{int to,nxt;}e[N<<1];
#define add(x,y) (e[++et]=(E){y,la[x]},la[x]=et)
#define max(a,b) (a>b?a:b)
void dfs(int x,int f){
    dep[x]=dep[fa[x]=f]+1,siz[x]=1;
    for(int i=la[x];i;i=e[i].nxt)if(e[i].to!=f){
        dfs(e[i].to,x),siz[x]+=siz[e[i].to];
        if(siz[e[i].to]>siz[son[x]])son[x]=e[i].to;
    }
}
void dfs2(int x,int t){
    if(id[x]=++dfn,top[x]=t,son[x])dfs2(son[x],t);
    for(int i=la[x];i;i=e[i].nxt)
    if(e[i].to!=fa[x]&&e[i].to!=son[x])dfs2(e[i].to,e[i].to);
}
void query(int l,int r){
    //询问线段树中区间[l,r]的答案
}
void getlca(int x,int y){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]<dep[fy])swap(fx,fy),swap(x,y);
        query(id[fx],id[x]),x=fa[fx],fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    query(id[x],id[y]);
}


LCT

//BZOJ-1036
#define cmax(a,b) (a<b?a=b:1)
const int N=30010;
int n,q,u,v,fa[N],son[N][2],val[N],sum[N],max[N],swp,rev[N];
#define swap(a,b) (swp=a,a=b,b=swp)
void pu(int t){
    max[t]=val[t],cmax(max[t],max[son[t][0]]),cmax(max[t],max[son[t][1]]);
    sum[t]=sum[son[t][0]]+sum[son[t][1]]+val[t];
}
void pd(int t){
    if(rev[t])rev[t]=0,rev[son[t][0]]^=1,rev[son[t][1]]^=1,swap(son[t][0],son[t][1]);
}
bool nr(int t){return son[fa[t]][0]==t||son[fa[t]][1]==t;}
void rtt(int t,int f=0,bool p=0){
    p=son[f=fa[t]][1]==t,
    fa[t]=fa[f],nr(f)?son[fa[f]][son[fa[f]][1]==f]=t:1,
    (son[f][p]=son[t][!p])?fa[son[f][p]]=f:1,
    pu(son[fa[f]=t][!p]=f);
}
void pv(int t){
    if(nr(t))pv(fa[t]);pd(t);
}
void splay(int t,int f=0){
    for(pv(t);nr(t);rtt(t))
    if(nr(f=fa[t]))rtt(son[f][1]==t^son[fa[f]][1]==f?t:f);
    pu(t);
}
void access(int t,int las=0){
    for(;t;splay(t),son[t][1]=las,las=t,t=fa[t]);
}
void makeroot(int t){
    access(t),splay(t),rev[t]^=1;
}
void link(int u,int v){
    makeroot(u),fa[u]=v;
}
void cut(int u,int v){
    makeroot(u),access(v),splay(v),son[v][0]=fa[u]=0;
}


KDtree



//BZOJ-2648
int n,m,op,x,y,i,dd,rt,ans;
struct T{int d[2],s[2],x[2],y[2];}t[1<<20];
struct P{int d[2];}a[1<<19];
bool operator<(const P&a,const P&b){return a.d[dd]<b.d[dd]||a.d[dd]==b.d[dd]&&a.d[dd^1]<b.d[dd^1];}
#define abs(x) (x>0?x:-(x))
#define max(a,b) (a>b?a:b)
#define cmax(a,b) (a<b?a=b:a)
#define cmin(a,b) (a>b?a=b:a)
#define ls t[now].s[0]
#define rs t[now].s[1]
void mt(int f,int x){
    cmin(t[f].x[0],t[x].x[0]),cmax(t[f].x[1],t[x].x[1]);
    cmin(t[f].y[0],t[x].y[0]),cmax(t[f].y[1],t[x].y[1]);
}
int bt(int l,int r,int d){
    dd=d;int now=l+r>>1;
    std::nth_element(a+l,a+now,a+r+1);
    t[now].d[0]=t[now].x[0]=t[now].x[1]=a[now].d[0];
    t[now].d[1]=t[now].y[0]=t[now].y[1]=a[now].d[1];
    if(l<now)ls=bt(l,now-1,d^1),mt(now,ls);
    if(now<r)rs=bt(now+1,r,d^1),mt(now,rs);
    return now;
}
int getdis(int p){
    return max(t[p].x[0]-x,0)+max(x-t[p].x[1],0)+max(t[p].y[0]-y,0)+max(y-t[p].y[1],0);
}
void ins(int n){
    for(int p=rt,dd=0;p;dd^=1){
        mt(p,n);int&nx=t[p].s[t[n].d[dd]>=t[p].d[dd]];
        if(nx==0){nx=n;return;}else p=nx;
    }
}
void query(int now){
    int d[2]={1<<30,1<<30},d0=abs(t[now].d[0]-x)+abs(t[now].d[1]-y),p;
    if(ls)d[0]=getdis(ls);if(rs)d[1]=getdis(rs);p=d[0]>=d[1];cmin(ans,d0);
    if(d[p]<ans)query(t[now].s[p]);
    if(d[p^1]<ans)query(t[now].s[p^1]);
}
 

斜率优化

//q表示单调队列，当f[i]=max()时维护开口向下的凸壳，斜率递减/f[i]=min()时维护开口向上的凸壳，斜率递增
//大不了暴力枚举不等号方向跟暴力拍一下，反正就四种情况
for(i=0;i<=n;q[++r]=i++){
        while(l<r&&y[q[l+1]]-y[q[l]]<=(cnt[q[l]+1]-cnt[q[l+1]+1])*d[i])l++;//未移项的不等式
        j=q[l],f[i]=f[j]+s[i]+sum[j+1]-sum[i]-(dis-d[i])*(cnt[j+1]-cnt[i]),y[i]=f[i]+sum[i+1]-dis*cnt[i+1];//表达式
        while(l<r&&(y[q[r]]-y[q[r-1]])*(cnt[i+1]-cnt[q[r]+1])<=(y[i]-y[q[r]])*(cnt[q[r]+1]-cnt[q[r-1]+1]))r--;//比较斜率
}


边表

int et=1,la[N];
struct E{int to,v,nxt;}e[N<<1];
void add(int x,int y,int v){
    e[++et]=(E){y,v,la[x]},la[x]=et;
}


spfa

int q[N],l,r,d[N],in[N];
void spfa(int s){
    memset(d,63,sizeof(d));
    for(q[l=r=0]=s,d[s]=0,in[s]=1;l<=r;in[q[l++]]=0)
    for(int i=la[q[l]];i;i=e[i].nxt)
    if(d[e[i].to]>d[q[l]]+e[i].v){
        d[e[i].to]=d[q[l]]+e[i].v;
        if(!in[e[i].to])in[q[++r]=e[i].to]=1;
    }
}


Dijkstra

//若干年前写的DJ...
#include<cstdio>
#include<cstring>
const int MAXN=1000010,MAXM=10000010;
int la[MAXN],et,d[MAXN],in[MAXN],hr;
struct E{int to,v,nxt;}e[MAXM<<1];
#define add(x,y,v) (e[++et]=(E){y,v,la[x]},la[x]=et)
int hr;struct H{int n,d;}h[M];
void ins(const H&t){int i;for(i=++hr;i!=1&&t.d<h[i>>1].d;i>>=1)h[i]=h[i>>1];h[i]=t;}
void dlt(){
    hr--;int i;
    for(i=1;(i<<1)<=hr&&!(h[hr+1].d<=h[i<<1].d&&h[hr+1].d<=h[i<<1|1].d);)
    i<<1!=hr&&h[i<<1|1].d<h[i<<1].d?(h[i]=h[i<<1|1],i=i<<1|1):(h[i]=h[i<<1],i=i<<1);
    h[i]=h[hr+1];
}
void dijkstra(int s){
    memset(d,127,sizeof(d)),
    memset(in,0,sizeof(in));int i,tmp;
    for(ins((H){s,d[s]=0});hr;dlt())
    if(!in[h[1].n]){
        for(in[h[1].n]=1,i=la[h[1].n];i;i=e[i].nxt)
        if(d[e[i].to]>(tmp=d[h[1].n]+e[i].v))
        ins((H){e[i].to,d[e[i].to]=tmp});
    }
}


二分图匹配-匈牙利

int dfs(int x){
    for(int i=la[x];i;i=e[i].nxt)
    if(vis[e[i].to]!=tim){
        vis[e[i].to]=tim;
        if(!fa[e[i].to]||dfs(fa[e[i].to]))
        return fa[e[i].to]=x,1;
    }
    return 0;
}
main(){
    ...
    for(int i=1;i<=n;i++)tim++,ans+=dfs(i);
    ...
}


Dinic

#include<cstdio>
#include<cstring>
#define N 5010
int n,m,s,t,la[N],et=1,d[N],cur[N],q[N],l,r;
struct E{int to,flow,nxt;}e[100000];
void add(int x,int y,int v){
    e[++et]=(E){y,v,la[x]},la[x]=et;
    e[++et]=(E){x,0,la[y]},la[y]=et;
}
int bfs(){
    memset(d,0,sizeof(d));
    for(q[l=r=0]=t,d[t]=1;l<=r;l++)
    for(int i=la[q[l]];i;i=e[i].nxt)
    if(e[i^1].flow&&!d[e[i].to])
    d[q[++r]=e[i].to]=d[q[l]]+1;
    return d[s];
}
int dfs(int x,int ret){
    if(x==t||ret==0)return ret;
    int tmp,flow=0;
    for(int&i=cur[x];i;i=e[i].nxt)
    if(d[x]==d[e[i].to]+1){
        tmp=dfs(e[i].to,e[i].flow<ret-flow?e[i].flow:ret-flow);
        e[i].flow-=tmp,e[i^1].flow+=tmp,flow+=tmp;
        if(ret==flow)return flow;
    }
    return flow;
}
int maxflow(){
    int flow=0;
    while(bfs())memcpy(cur,la,sizeof(la)),flow+=dfs(s,1<<30);
    return flow;
}


最小费用最大流

#include<cstdio>
#include<cstring>
const int N=2000,M=40000,oo=1<<28;
int p[N],d[N],q[1<<20],la[N],s,t,et=1,in[N];
struct E{int to,flow,cost,nxt;}e[M<<1];
#define cmin(a,b) (a>b?a=b:1)
void add(int from,int to,int flow,int cost){
    e[++et]=(E){to,flow,cost,la[from]},la[from]=et;
    e[++et]=(E){from,0,-cost,la[to]},la[to]=et;
}
int spfa(){
    memset(d,63,sizeof(d));int l,r,i;
    for(q[l=r=1]=s,in[s]=1,d[s]=0;l<=r;in[q[l++]]=0)
    for(i=la[q[l]];i;i=e[i].nxt)
    if(e[i].flow&&d[e[i].to]>d[q[l]]+e[i].cost){
        d[e[i].to]=d[q[l]]+e[i].cost;p[e[i].to]=i;
        if(!in[e[i].to])in[q[++r]=e[i].to]=1;
    }
    return d[t]<d[0];
}
int mincost(){
    int flow=0,cost=1<<20,u,tmp;
    while(spfa()){tmp=oo;
        for(u=t;u!=s;u=e[p[u]^1].to)cmin(tmp,e[p[u]].flow);
        for(u=t;u!=s;u=e[p[u]^1].to)e[p[u]].flow-=tmp,e[p[u]^1].flow+=tmp;
        flow+=tmp,cost+=d[t]*tmp;
    }
    return cost;
}


LCA-倍增

int lca(int x,int y){
    int k,i;
    if(dep[x]<dep[y])k=x,x=y,y=k;
    for(i=0,k=dep[x]-dep[y];k;k>>=1,i++)
    if(k&1)x=fa[x][i];
    if(x==y)return x;
    for(i=0;fa[x][i]!=fa[y][i];i++);
    for(i--;~i;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}


LCA-树链剖分版

//前面两个dfs跟树剖一样
int lca(int x,int y){
    while(top[x]!=top[y])
    if(dep[top[x]]>dep[top[y]])x=fa[top[x]];else y=fa[top[y]];
    return dep[x]<dep[y]?x:y;
}


带花树

#define N 1010
int n,m,x,y,v,mate[N],fa[N],pre[N],la[N],et,ans,q[N],l,r,sta[N],vis[N],tim;
struct E{int to,nxt;}e[6010];
#define add(x,y) (e[++et]=(E){y,la[x]},la[x]=et)
int gf(int x){return fa[x]==x?x:fa[x]=gf(fa[x]);}
int lca(int x,int y){
    for(++tim,x=gf(x),y=gf(y);;v=x,x=y,y=v)if(x){
        if(vis[x]==tim)return x;
        vis[x]=tim,x=gf(pre[mate[x]]);
    }
}
int blossom(int x,int y,int g){
    while(gf(x)!=g){
        if(pre[x]=y,sta[mate[x]]==1)sta[q[++r]=mate[x]]=0;
        if(gf(x)==x)fa[x]=g;if(gf(mate[x])==mate[x])fa[mate[x]]=g;
        y=mate[x],x=pre[y];
    }
}
int match(int s){int i,j,las;
    memset(pre,0,sizeof(pre));
    memset(sta,-1,sizeof(sta));
    for(i=1;i<=n;i++)fa[i]=i;
    for(q[l=r=0]=s,sta[s]=0;l<=r;l++)
    for(i=la[q[l]];i;i=e[i].nxt)
    if(sta[e[i].to]==-1){
        pre[e[i].to]=q[l],sta[e[i].to]=1;
        if(!mate[e[i].to]){
            for(j=q[l],i=e[i].to;j;j=pre[i=las])las=mate[j],mate[j]=i,mate[i]=j;
            return 1;
        }
        sta[q[++r]=mate[e[i].to]]=0;
    }
    else if(gf(e[i].to)!=gf(q[l])&&sta[e[i].to]==0)
        j=lca(e[i].to,q[l]),blossom(e[i].to,q[l],j),blossom(q[l],e[i].to,j);
    return 0;
}


 

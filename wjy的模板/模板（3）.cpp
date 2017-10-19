Point的定义（在复数域上）

typedef double ld;
#define PP const P&
struct P{
    ld x,y;
    bool operator<(PP a)const{return x<a.x||x==a.x&&y<a.y;}
    P operator+(PP a)const{return(P){x+a.x,y+a.y};}
    P operator-(PP a)const{return(P){x-a.x,y-a.y};}
    P operator*(ld a)const{return(P){x*a,y*a};}
    P operator/(ld a)const{return(P){x/a,y/a};}
    P operator*(PP a)const{return(P){x*a.x-y*a.y,x*a.y+y*a.x};}
    ld operator|(PP a)const{return x*a.x+y*a.y;}
    ld operator&(PP a)const{return x*a.y-y*a.x;}
    P operator/(PP a)const{ld g=a.x*a.x+a.y*a.y;return (P){(x*a.x+y*a.y)/g,(y*a.x-x*a.y)/g};}
    void _sqrt(){ld t=atan2(y,x)*.5,len=sqrt(sqrt(x*x+y*y));x=len*cos(t),y=len*sin(t);}
};
ld len2(PP a){return a.x*a.x+a.y*a.y;}
#define check(a,b,c) ((b-a)&(c-a))


二维凸包

std::sort(a+1,a+1+n);
for(i=1;i<=n;i++)a[n+n-i+1]=a[i];
for(r=0,i=1;i<=n+n;q[++r]=a[i++])
while(r>1&&check(q[r-1],q[r],a[i])<=0)r--;


三维凸包

//BZOJ-1209
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
typedef double ld;
char ch,B[1<<15],*S=B,*T=B;
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?0:*S++)
#define isd(c) (c>='0'&&c<='9')
int bb;ld aa,ee;ld F(){
    while(ch=getc(),!isd(ch)&&ch!='-');ch=='-'?aa=bb=0:(aa=ch-'0',bb=1);
    while(ch=getc(),isd(ch))aa=aa*10+ch-'0';ee=1;
    if(ch=='.')while(ch=getc(),isd(ch))aa+=(ch-'0')*(ee*=0.1);return bb?aa:-aa;
}
ld G(){
    return (rand()-(1<<30))/1e21;
}
int n,i,j,t[2],vis[1010][1010],now,las,tmp;ld ans;
struct P{ld x,y,z;}p[1010];
#define PP const P&
P operator-(PP a,PP b){return (P){a.x-b.x,a.y-b.y,a.z-b.z};}
P operator&(PP a,PP b){return (P){a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};}
ld operator|(PP a,PP b){return a.x*b.x+a.y*b.y+a.z*b.z;}
ld len(PP a){return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);}
#define ck(a,b,c) ((b-a)&(c-a))
struct Sfc{
    int a,b,c;P s;
    void up(int x,int y,int z){
        a=x,b=y,c=z,s=ck(p[x],p[y],p[z]);
    }
}q[2][3010];
#define see(i,f) ((f.s|(p[i]-p[f.a]))>0)
#define ns q[las][j]
#define pd(a,b) if(vis[a][b]&&!vis[b][a])q[now][++t[now]].up(a,b,i)
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++)p[i]=(P){F()+G(),F()+G(),F()+G()};
    for(q[1][++t[1]].up(1,2,3),q[1][++t[1]].up(3,2,1),i=4;i<=n;i++){
        now=i&1,las=now^1,t[now]=0;
        for(j=1;j<=t[las];j++){
            if(tmp=see(i,ns),!tmp)q[now][++t[now]]=ns;
            vis[ns.a][ns.b]=vis[ns.b][ns.c]=vis[ns.c][ns.a]=tmp;
        }
        for(j=1;j<=t[las];j++){
            pd(ns.a,ns.b);
            pd(ns.b,ns.c);
            pd(ns.c,ns.a);
        }
    }
    for(now=n&1,i=1;i<=t[now];i++)ans+=len(q[now][i].s);
    printf("%lf\n",ans*0.5);
}


半个半平面交

//BZOJ-1007
#define N 50010
int n,i,q[N],r;
struct P{int x,y,n;}a[N];
#define PP const P&
bool operator<(PP a,PP b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
P operator-(PP a,PP b){return (P){a.x-b.x,a.y-b.y};}
long long operator*(PP a,PP b){return 1LL*a.x*b.y-1LL*a.y*b.x;}
long long check(PP a,PP b,PP c){return (b-a)*(c-a);}
int main(){
    for(n=F(),i=1;i<=n;i++)a[i]=(P){F(),-F(),i};
    std::sort(a+1,a+1+n);
    for(i=1;i<=n;i++)if(a[i].x!=a[i-1].x){
        while(r>1&&check(a[q[r-1]],a[q[r]],a[i])<=0)r--;q[++r]=i;
    }
    for(i=1;i<=r;i++)q[i]=a[q[i]].n;
    std::sort(q+1,q+1+r);
    for(i=1;i<=r;i++)printf("%d ",q[i]);puts("");
}


矩形面积并

//POJ-1151
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1024
#define ld double
int n,m,i,j,t,cnt[N],tot;ld ans,len[N],L[N],R[N],dx[N],dy[N],x1,x2,y1,y2;
struct D{ld x1,x2,y;int p;}d[N];
bool operator<(const D&i,const D&j){return i.y<j.y||i.y==j.y&&i.p>j.p;}
void mt(int o){
    if(cnt[o])len[o]=R[o]-L[o];
    else len[o]=len[o<<1]+len[o<<1|1];
}
void bt(int o,int l,int r){
    L[o]=dx[l],R[o]=dx[r],len[o]=cnt[o]=0;
    int mid=l+r>>1;
    if(l+1<r)bt(o<<1,l,mid),bt(o<<1|1,mid,r);
    else len[o<<1]=len[o<<1|1]=0,L[o<<1]=R[o<<1]=L[o],L[o<<1|1]=R[o<<1|1]=R[o];
}
void upd(int o,ld l,ld r,int p){
    if(l<=L[o]&&R[o]<=r){
        cnt[o]+=p,mt(o);return;
    }
    if(l<R[o<<1])upd(o<<1,l,r,p);
    if(r>L[o<<1|1])upd(o<<1|1,l,r,p);
    mt(o);
}
int main(){
    while(scanf("%d",&n),n){
        for(tot=m=0,i=1;i<=n;i++)
        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2),
        dy[++tot]=x1,d[tot]=(D){x1,x2,y1,1},
        dy[++tot]=x2,d[tot]=(D){x1,x2,y2,-1};
        std::sort(dy+1,dy+1+tot);
        std::sort(d+1,d+1+tot);
        for(i=1,m=0;i<=tot;i++)
        if(dy[i]!=dy[i+1])dx[++m]=dy[i];
        bt(1,1,m);
        for(ans=0,i=1;i<=tot;i++){
            upd(1,d[i].x1,d[i].x2,d[i].p);
            ans+=len[1]*(d[i+1].y-d[i].y);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",++t,ans);
    }
}


曼哈顿距离最小生成树

//BZOJ-2177
#include<cstdio>
#include<cstring>
#include<algorithm>
char B[1<<15],*S=B,*T=B,ch;
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?0:*S++)
int aa,bb;int F(){
    while(ch=getc(),(ch<'0'||ch>'9')&&ch!='-');ch=='-'?aa=bb=0:(aa=ch-'0',bb=1);
    while(ch=getc(),ch>='0'&&ch<='9')aa=aa*10+ch-'0';return bb?aa:-aa;
}
#define N 100010
int n,swp,cnt,z[N];long long ans;
#define swap(a,b) (swp=a,a=b,b=swp)
#define abs(x) (x>0?x:-(x))
#define max(a,b) (a>b?a:b)
#define cmax(x) (ans<x?ans=x:1)
struct P{int x,y,id,nx,ny;}p[N];
bool operator<(const P&a,const P&b){return a.nx<b.nx||a.nx==b.nx&&a.ny<b.ny;}
class Graph{
private:
    int et,la[N],ufs[N],tot;
    struct D{
        int x,y,v;
        bool operator<(const D&a)const{return v<a.v;}
    }d[N<<2];
    struct E{int to,v,nxt;}e[N<<1];
    int gf(int x){return ufs[x]==x?x:ufs[x]=gf(ufs[x]);}
    void adde(int x,int y,int v){
        e[++et]=(E){y,v,la[x]},la[x]=et;
        e[++et]=(E){x,v,la[y]},la[y]=et;
    }
public:
    Graph(){et=1;}
    void add(int x,int y,int v){d[++tot]=(D){x,y,v};}
    void make(){
        std::sort(d+1,d+1+tot);
        for(int i=1;i<=n;i++)ufs[i]=i;cnt=n;
        for(int i=1,x,y;i<=tot;i++)
        if((x=gf(d[i].x))!=(y=gf(d[i].y))){
            ufs[x]=y,cnt--,ans+=d[i].v,
            adde(d[i].x,d[i].y,d[i].v);
        }
    }
}G;
struct D{int x,n;}d[N];
bool operator<(const D&a,const D&b){return a.x<b.x;}
#define dis(i,j) (abs(p[i].x-p[j].x)+abs(p[i].y-p[j].y))
void ins(int i){
    for(int t=p[i].ny;t<=cnt;t+=t&-t)
    if(z[t]==0||p[z[t]].x+p[z[t]].y<p[i].x+p[i].y)z[t]=i;
}
int query(int i){int f=0;
    for(int t=p[i].ny;t>0;t-=t&-t)
    if(z[t]&&(f==0||p[z[t]].x+p[z[t]].y>p[f].x+p[f].y))f=z[t];
    return f;
}
void work(){
    for(int i=1;i<=n;i++)p[i].nx=p[i].x-p[i].y,p[i].ny=p[i].y;
    std::sort(p+1,p+1+n);
    for(int i=1;i<=n;i++)d[i]=(D){p[i].ny,i};
    std::sort(d+1,d+1+n);d[n+1].x=d[n].x;cnt=1;
    for(int i=1;i<=n;i++){
        p[d[i].n].ny=cnt;
        if(d[i].x!=d[i+1].x)cnt++;
    }
    memset(z,0,sizeof(z));
    for(int i=1,j;i<=n;ins(i++))
    if(j=query(i))G.add(p[i].id,p[j].id,dis(i,j));
}
int main(){
    n=F();
    for(int i=1;i<=n;i++)p[i]=(P){F(),F(),i};work();
    for(int i=1;i<=n;i++)swap(p[i].x,p[i].y);work();
    for(int i=1;i<=n;i++)p[i].y=-p[i].y;work();
    for(int i=1;i<=n;i++)swap(p[i].x,p[i].y);work();G.make();
    printf("%lld\n",ans);
}


欧几里德距离最小生成树

//BZOJ-3911
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 100010
#define sqr(x) ((x)*(x))
#define max(a,b) (a>b?a:b)
int aa;char ch;int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-'0';
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-'0';return aa;
}
typedef double ld;
struct P{
    ld x,y;
#define PP const P&
    bool operator<(PP a)const {return x<a.x||x==a.x&&y<a.y;}
    P operator-(PP a)const {return (P){x-a.x,y-a.y};}
    ld operator&(PP a)const {return x*a.y-y*a.x;}
    ld operator|(PP a)const {return x*a.x+y*a.y;}
}p[N];
#define check(a,b,c) ((b-a)&(c-a))
ld dis2(PP a){return a.x*a.x+a.y*a.y;}
#define cross(a,b,c,d) (check(p[a],p[c],p[d])*check(p[b],p[c],p[d])<0&&check(p[c],p[a],p[b])*check(p[d],p[a],p[b])<0)
struct P3{
    ld x,y,z;
    bool operator<(const P3&a)const {return x<a.x||x==a.x&&y<a.y;}
    P3 operator-(const P3&a)const {return (P3){x-a.x,y-a.y,z-a.z};}
    ld operator|(const P3&a)const {return x*a.x+y*a.y+z*a.z;}
    P3 operator&(const P3&a)const {return (P3){y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-y*a.x};}
}ori[N];
#define gp3(a) (P3){a.x,a.y,a.x*a.x+a.y*a.y}
bool incir(int a,int b,int c,int d){
    P3 aa=gp3(p[a]),bb=gp3(p[b]),cc=gp3(p[c]),dd=gp3(p[d]);
    if(check(p[a],p[b],p[c])<0)std::swap(bb,cc);
    return (check(aa,bb,cc)|(dd-aa))<0;
}
int n,m,i,j,et=1,la[N],ts,xx,yy,fa[N][20],tot,cnt,dep[N],l,r,q[N<<2],ufs[N];ld mx[N][20];
struct E{int to,l,r;}e[N<<5];
void add(int x,int y){
    e[++et]=(E){y,la[x]},e[la[x]].r=et,la[x]=et;
    e[++et]=(E){x,la[y]},e[la[y]].r=et,la[y]=et;
}
void del(int x){
    e[e[x].r].l=e[x].l,e[e[x].l].r=e[x].r,la[e[x^1].to]==x?la[e[x^1].to]=e[x].l:1;
}
void delaunay(int l,int r){
    if(r-l<=2){
        for(int i=l;i<r;i++)
        for(int j=i+1;j<=r;j++)add(i,j);
        return;
    }
    int i,j,mid=l+r>>1,ld=0,rd=0,id,op;
    delaunay(l,mid),delaunay(mid+1,r);
    for(tot=0,i=l;i<=r;q[++tot]=i++)
    while(tot>1&&check(p[q[tot-1]],p[q[tot]],p[i])<0)tot--;
    for(i=1;i<tot&&!ld;i++)if(q[i]<=mid&&mid<q[i+1])ld=q[i],rd=q[i+1];
    for(;add(ld,rd),1;){
        id=op=0;
        for(i=la[ld];i;i=e[i].l)if(check(p[ld],p[rd],p[e[i].to])>0)
        if(!id||incir(ld,rd,id,e[i].to))op=-1,id=e[i].to;
        for(i=la[rd];i;i=e[i].l)if(check(p[rd],p[ld],p[e[i].to])<0)
        if(!id||incir(ld,rd,id,e[i].to))op=1,id=e[i].to;
        if(op==0)break;
        if(op==-1){
            for(i=la[ld];i;i=e[i].l)
            if(cross(rd,id,ld,e[i].to))del(i),del(i^1),i=e[i].r;
            ld=id;
        }else{
            for(i=la[rd];i;i=e[i].l)
            if(cross(ld,id,rd,e[i].to))del(i),del(i^1),i=e[i].r;
            rd=id;
        }
    }
}
struct D{int x,y;ld v;}d[N<<3];
bool operator<(const D&i,const D&j){return i.v<j.v;}
int gf(int x){return ufs[x]==x?x:ufs[x]=gf(ufs[x]);}
struct G{int to;double v;int nxt;}g[N<<3];
#define addg(x,y,v) (g[++et]=(G){y,v,la[x]},la[x]=et)
ld query(int x,int y){
    int k,i;ld ans=0;
    if(dep[x]<dep[y])k=x,x=y,y=k;
    for(k=dep[x]-dep[y],i=0;k;k>>=1,i++)if(k&1)
    ans=max(ans,mx[x][i]),x=fa[x][i];
    if(x==y)return ans;
     
    for(i=0;fa[x][i]!=fa[y][i];i++);
    for(i--;~i;i--)if(fa[x][i]!=fa[y][i])
    ans=max(ans,max(mx[x][i],mx[y][i])),x=fa[x][i],y=fa[y][i];
    ans=max(ans,max(mx[x][0],mx[y][0]));return ans;
}
int main(){
    for(n=F(),i=1;i<=n;i++)xx=F(),yy=F(),p[i]=(P){xx,yy},ori[i]=(P3){xx,yy,i},ufs[i]=i;
    std::sort(p+1,p+1+n);std::sort(ori+1,ori+1+n);delaunay(1,n);
     
    for(i=1;i<=n;i++)
    for(j=la[i];j;j=e[j].l)xx=ori[i].z,yy=ori[e[j].to].z,
    d[++tot]=(D){xx,yy,dis2(p[i]-p[e[j].to])};
    std::sort(d+1,d+1+tot);
     
    memset(la,0,sizeof(la)),et=0;
    for(i=1;i<=tot&&cnt<n-1;i++)if(gf(d[i].x)!=gf(d[i].y))
    cnt++,ufs[ufs[d[i].x]]=ufs[d[i].y],
    addg(d[i].x,d[i].y,d[i].v),addg(d[i].y,d[i].x,d[i].v);
     
    for(q[l=r=1]=dep[1]=1;l<=r;l++)
    for(i=la[q[l]];i;i=g[i].nxt)if(!dep[g[i].to])
    for(dep[q[++r]=g[i].to]=dep[q[l]]+1,fa[g[i].to][j=0]=q[l],mx[g[i].to][0]=g[i].v;fa[g[i].to][j];j++)
    fa[g[i].to][j+1]=fa[fa[g[i].to][j]][j],mx[g[i].to][j+1]=max(mx[g[i].to][j],mx[fa[g[i].to][j]][j]);
     
    for(m=F();m--;printf("%.6lf\n",sqrt(query(F(),F()))));
}


平面图点定位

//WC2013 Planner Graph
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<set>
int aa;char ch,B[1<<15],*S=B,*T=B;
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?0:*S++)
#define GetAA() \
    while(ch=getc(),ch<'0'||ch>'9');aa=ch-'0';\
    while(ch=getc(),ch>='0'&&ch<='9')aa=aa*10+ch-'0'
int F(){GetAA();return aa;}
int Fl(){GetAA();return aa<<1|(ch=='.'?getc(),1:0);}
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
#define cmax(a,b) (a<b?a=b:1)
typedef double ld;
typedef long long ll;
#define N 300010
int n,m,qtot,et=1,la[N],id[N],cnt,vis[N],inf;ll sum[N];
struct E{int to,v,nxt,pre;}e[N];
void adde(int x,int y,int v){
    e[++et]=(E){y,v,la[x]},la[x]=et;
    e[++et]=(E){x,v,la[y]},la[y]=et;
}
struct P{int x,y;}p[N];
#define PP const P&
bool operator<(PP a,PP b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
bool operator==(PP a,PP b){return a.x==b.x&&a.y==b.y;}
P operator-(PP a,PP b){return (P){a.x-b.x,a.y-b.y};}
ll operator*(PP a,PP b){return 1LL*a.x*b.y-1LL*a.y*b.x;}
struct D{P to;int n;};
bool operator<(const D&a,const D&b){return atan2(a.to.y,a.to.x)<atan2(b.to.y,b.to.x);}
struct Q{P p;int n;}a[N];
bool operator<(const Q&a,const Q&b){return a.p<b.p||a.p==b.p&&a.n<b.n;}
struct Graph{
    int et,la[N],q[N],l,r,fa[N][20],mx[N][20],vis[N],dep[N],ufs[N],tot;
    struct E{int to,v,nxt;}e[N<<1];
    struct H{
        int x,y,v;
        bool operator<(const H&b)const{return v<b.v;}
    }d[N];
    int gf(int x){return ufs[x]==x?x:ufs[x]=gf(ufs[x]);}
    void adde(int x,int y,int v){
        e[++et]=(E){y,v,la[x]},la[x]=et;
        e[++et]=(E){x,v,la[y]},la[y]=et;
    }
    void add(int x,int y,int v){d[++tot]=(H){x,y,v};}
    void bfs(){
        for(q[l=r=0]=inf==1?2:1,vis[inf==1?2:1]=1;l<=r;l++)
        for(int i=la[q[l]];i;i=e[i].nxt)
        if(!vis[e[i].to]){
            vis[q[++r]=e[i].to]=1;mx[e[i].to][0]=e[i].v;
            dep[e[i].to]=dep[fa[e[i].to][0]=q[l]]+1;
            for(int j=0;fa[e[i].to][j];j++)
            fa[e[i].to][j+1]=fa[fa[e[i].to][j]][j],
            mx[e[i].to][j+1]=max(mx[e[i].to][j],mx[fa[e[i].to][j]][j]);
        }
    }
    int query(int x,int y){
        int k,i,ans=0;
        if(x==inf||y==inf||gf(x)!=gf(y))return -1;
        if(dep[x]<dep[y])k=x,x=y,y=k;
        for(i=0,k=dep[x]-dep[y];k;k>>=1,i++)if(k&1)cmax(ans,mx[x][i]),x=fa[x][i];
        if(x==y)return ans;
        for(i=0;fa[x][i]!=fa[y][i];i++);
        for(i--;~i;i--)if(fa[x][i]!=fa[y][i])
        cmax(ans,mx[x][i]),x=fa[x][i],
        cmax(ans,mx[y][i]),y=fa[y][i];
        cmax(ans,mx[x][0]),cmax(ans,mx[y][0]);return ans;
    }
    void work1(){
        for(int i=1;i<=cnt;i++)ufs[i]=i;
        std::sort(d+1,d+1+tot);et=1;
        for(int i=1,x,y;i<=tot;i++)
        if((x=gf(d[i].x))!=(y=gf(d[i].y)))
        ufs[x]=y,adde(d[i].x,d[i].y,d[i].v);
        bfs();
    }
    void work2(){
        for(int i=1;i<=qtot;i++)printf("%d\n",query(id[i+n],id[i+n+qtot]));
    }
}G;
void sort_edge(int x){
    int tot=0;static D d[N];
    for(int i=la[x];i;i=e[i].nxt)d[++tot]=(D){p[e[i].to]-p[x],i};
    std::sort(d+1,d+1+tot);
    for(int i=2;i<=tot;i++)e[d[i].n].pre=d[i-1].n;
    e[d[1].n].pre=d[tot].n;
}
void get_area(int col,int i){
    int o=i;P x=p[e[i^1].to];
    for(vis[i]=col;(i=e[i^1].pre)!=o;vis[i]=col)
    sum[col]+=(p[e[i^1].to]-x)*(p[e[i].to]-x);
    if(sum[col]<0)sum[col]=-sum[col];
}
void work1(){
    for(int i=1;i<=n;i++)sort_edge(i);
    for(int i=2;i<=et;i++)if(!vis[i])get_area(++cnt,i);
    for(int i=1;i<=cnt;i++)if(sum[i]>sum[inf])inf=i;
    for(int i=2;i<=et;i++)if(vis[i]!=inf&&vis[i^1]!=inf&&vis[i^1]<vis[i])G.add(vis[i],vis[i^1],e[i].v);
}
ld nowx;
struct T{
    int tot;
    struct Node{
        ld k,b,x0;int col;
        bool operator<(const Node&a)const{return k*(nowx+0.001)+b<a.k*(nowx+0.001)+a.b||k*(nowx+0.001)+b==a.k*(nowx+0.001)+a.b&&x0<a.x0;}
    }tr[N];
    std::set<Node>s;
    std::set<Node>::iterator it[N];
    void init(){
        for(int i=2;i<=et;i+=2){
            tr[i>>1].k=1.0*(p[e[i].to].y-p[e[i^1].to].y)/(p[e[i].to].x-p[e[i^1].to].x);
            tr[i>>1].b=p[e[i].to].y-tr[i>>1].k*p[e[i].to].x;
            tr[i>>1].x0=min(p[e[i].to].x,p[e[i^1].to].x);
            if(p[e[i].to].x>p[e[i^1].to].x)tr[i>>1].col=vis[i];else tr[i>>1].col=vis[i^1];
        }
        tr[0].col=inf;tr[0].b=-1;
        tr[tot=(et>>1)+1].k=0,tr[tot].b=1<<30,tr[tot].col=inf;nowx=0;
        it[0]=s.insert(tr[0]).first;
        it[tot]=s.insert(tr[tot]).first;tot++;
    }
    void ins(int x,int k){nowx=x;it[k]=s.insert(tr[k]).first;}
    void del(int k){s.erase(it[k]);}
    void query(int o,int x,int y){
        nowx=x,tr[tot].k=0,tr[tot].b=y;
        id[o]=(*--s.lower_bound(tr[tot])).col;
    }
}tree;
void work2(){
    qtot=F();int tot=n;
    for(int i=1;i<=qtot;i++)id[i]=inf,
    a[++tot].p=(P){Fl(),Fl()},a[tot].n=i+n,
    a[++tot].p=(P){Fl(),Fl()},a[tot].n=i+n+qtot;
    std::sort(a+1,a+1+n+qtot*2);tree.init();
    for(int i=1;i<=tot;i++)
    if(a[i].n<=n){
        for(int j=la[a[i].n];j;j=e[j].nxt)
        if(p[a[i].n].x!=p[e[j].to].x)
        if(p[a[i].n].x>p[e[j].to].x)tree.del(j>>1);
        else tree.ins(p[a[i].n].x,j>>1);
    }
    else tree.query(a[i].n,a[i].p.x,a[i].p.y);
}
int main(){
    n=F(),m=F();G.et=1;
    for(int i=1;i<=n;i++)a[i].p=p[i]=(P){Fl(),Fl()},a[i].n=i;
    for(int i=1,x,y,v;i<=m;i++)x=F(),y=F(),v=F(),adde(x,y,v);
    work1();G.work1();
    work2();G.work2();
}


辛普森积分

//BZOJ-2178 若干年前写的
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define eps 1e-8
#define ld double
int n,i,ll,rr,t;ld ans;
struct qj{ld l,r;}q[1010];
struct data{int x,y,r,lx,rx;}a[1010];
ld abs(ld a){return a>0?a:-a;}
ld max(ld a,ld b){return a>b?a:b;}
bool cmp(const qj&i,const qj&j){return i.l<j.l;}
ld sqr(ld x){return x*x;}
ld f(ld xx)
{
    int i;ld ans=0,nl=-10001,nr=-10001;t=0;
    for(i=1;i<=n;i++)
    if(abs(a[i].x-xx)<=a[i].r)
    {
        q[++t].l=a[i].y-sqrt(sqr(a[i].r)-sqr(a[i].x-xx));
        q[t].r=2*a[i].y-q[t].l;
    }
    std::sort(q+1,q+1+t,cmp);
    for(i=1;i<=t;i++)
    {
        if(nr<q[i].l){ans+=nr-nl;nl=q[i].l;}
        nr=max(nr,q[i].r);
    }
    return ans+nr-nl;
}
ld d(ld l,ld r,ld fl,ld fr,ld fm,ld s)
{
    ld mid=(l+r)/2;
    ld flm=f((l+mid)/2);
    ld fmr=f((mid+r)/2);
    ld ls=(fl+fm+4*flm)*(mid-l);
    ld rs=(fm+fr+4*fmr)*(r-mid);
    if(r-l>3.75)return d(l,mid,fl,fm,flm,ls)+d(mid,r,fm,fr,fmr,rs);
    if(abs(s-ls-rs)<eps)return s;
    else return d(l,mid,fl,fm,flm,ls)+d(mid,r,fm,fr,fmr,rs);
}
bool cmp1(const data&i,const data&j){return i.lx<j.lx;}
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].r);
        a[i].lx=a[i].x-a[i].r;
        a[i].rx=a[i].x+a[i].r;
    }
    std::sort(a+1,a+1+n,cmp1);
    ll=rr=-10001;
    ld fl,fr,fm,fs;
    for(i=1;i<=n;i++)
    {
        if(rr<a[i].lx)
        {
            fl=f(ll);fr=f(rr);fm=f((ll+rr)>>1);fs=(fl+fr+4*fm)*(rr-ll);
            ans+=d(ll,rr,fl,fr,fm,fs);
            ll=a[i].lx;
        }
        rr=max(rr,a[i].rx);
    }
    fl=f(ll);fr=f(rr);fm=f((ll+rr)>>1);fs=(fl+fr+4*fm)*(rr-ll);
    ans+=d(ll,rr,fl,fr,fm,fs);
    printf("%.3lf",ans/6);
}



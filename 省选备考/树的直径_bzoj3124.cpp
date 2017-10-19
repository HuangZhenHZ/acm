/**************************************************************
    Problem: 3124
    User: 8300590
    Language: C++
    Result: Accepted
    Time:1312 ms
    Memory:17212 kb
****************************************************************/
 
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

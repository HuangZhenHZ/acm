/**************************************************************
    Problem: 1036
    User: 8300590
    Language: C++
    Result: Accepted
    Time:2420 ms
    Memory:3984 kb
****************************************************************/
 
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

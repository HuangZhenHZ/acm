/**************************************************************
    Problem: 2049
    User: 8300590
    Language: C++
    Result: Accepted
    Time:1440 ms
    Memory:996 kb
****************************************************************/
 
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
         
//      for (int x=1;x<=n;x++){
//          for (int y=1;y<=n;y++) printf("%d ",check(x,y));
//          printf("\n");
//      }
    }
    return 0;
}

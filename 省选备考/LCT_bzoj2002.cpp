/**************************************************************
    Problem: 2002
    User: 8300590
    Language: C++
    Result: Accepted
    Time:1548 ms
    Memory:4088 kb
****************************************************************/
 
#include<cstdio>
 
const int N=210000;
 
int fa[N],ch[N][2],size[N];
 
inline bool ir(int x){ return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x; }
inline bool nt(int x){ return ch[fa[x]][1]==x; }
inline void ud(int x){ size[x]=size[ch[x][0]]+size[ch[x][1]]+1; }
 
void rtt(int x){
//  printf("in rtt\n");
     
    int y=fa[x], z=fa[y]; bool p=nt(x);
    if (!ir(y)) ch[z][nt(y)]=x;
    fa[y]=x; fa[x]=z; fa[ch[x][!p]]=y;
    ch[y][p]=ch[x][!p]; ch[x][!p]=y;
    ud(y);
     
//  printf("out rtt\n");
}
 
void splay(int x){
//  printf("in splay\n");
     
    while (!ir(x)){
        int y=fa[x];
        if (!ir(y)) rtt(nt(x)^nt(y)?x:y);
        rtt(x);
    }
    ud(x);
     
//  printf("out splay\n");
}
 
void access(int x){
//  printf("in access\n");
     
    int y=x, t=0;
    while (x){
        splay(x);
        ch[x][1]=t;
        t=x;
        x=fa[x];
    }
    splay(y);
     
//  printf("out access\n");
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

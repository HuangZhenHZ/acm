/**************************************************************
    Problem: 1010
    User: 8300590
    Language: C++
    Result: Accepted
    Time:128 ms
    Memory:2916 kb
****************************************************************/
 
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
     
//  for (int i=1;i<=n;i++) printf("%lld ",s[i]);
//  printf("\n");
     
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
     
//  for (int i=1;i<=n;i++) printf("%lld ",g[i]);
//  printf("\n");
//  
//  for (int i=1;i<=n;i++) printf("%lld ",h[i]);
//  printf("\n");
//  
//  for (int i=1;i<=n;i++) printf("%lld ",f[i]);
     
    printf("%lld\n",f[n]);
    return 0;
}

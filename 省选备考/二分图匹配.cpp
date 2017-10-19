/**************************************************************
    Problem: 1059
    User: 8300590
    Language: C++
    Result: Accepted
    Time:360 ms
    Memory:1160 kb
****************************************************************/
 
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

/**************************************************************
    Problem: 1085
    User: 8300590
    Language: C++
    Result: Accepted
    Time:376 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
 
const char ans[5][6]={
    "11111",
    "01111",
    "00*11",
    "00001",
    "00000"
};
const int dx[8]={-2,-2,-1,-1,1,1,2,2};
const int dy[8]={-1,1,-2,2,-2,2,-1,1};
 
char s[5][6];
 
bool dfs(int n, int x, int y){
    int diff=0;
    forto(i,0,4) forto(j,0,4) diff+=ans[i][j]!=s[i][j];
    if (n==0) return diff==0;
    if (diff-1>n) return 0;
     
    forto(i,0,7){
        int nx=x+dx[i], ny=y+dy[i];
        if (nx>=0 && nx<=4 && ny>=0 && ny<=4){
            s[x][y]=s[nx][ny];
            s[nx][ny]='*';
            bool ok=dfs(n-1,nx,ny);
            s[nx][ny]=s[x][y];
            s[x][y]='*';
            if (ok) return 1;
        }
    }
    return 0;
}
 
int main(){
    int t; scanf("%d",&t);
    while (t--){
        forto(i,0,4) scanf("%s",s[i]);
        int x,y;
        forto(i,0,4) forto(j,0,4) 
        if (s[i][j]=='*'){
            x=i; y=j;
        }
         
        int i=1;
        while (i<=15 && !(dfs(i,x,y))) i++;
        if (i<=15) printf("%d\n",i); else printf("-1\n");
    }
    return 0;
}

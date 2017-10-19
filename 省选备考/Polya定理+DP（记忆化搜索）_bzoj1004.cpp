/**************************************************************
    Problem: 1004
    User: 8300590
    Language: C++
    Result: Accepted
    Time:32 ms
    Memory:868 kb
****************************************************************/
 
#include<cstdlib>
#include<cstdio>
#define forto(i,a,b) for(int i=(a);i<=b;i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
 
int a,b,c,n,m,p;
int f[70];
int s[70],top;
bool qc[70];
int dp[25][25][25];
 
void gets(){
    forto(i,1,n) qc[i]=true;
    top=0;
    forto(i,1,n)
    if (qc[i]){
        int sum=0;
        for(int j=i;qc[j];j=f[j]){
            qc[j]=false;
            sum++;
        }
        s[++top]=sum;
    }
}
 
int dfs(int i, int x, int y, int z){
    if (dp[x][y][z]!=-1) return dp[x][y][z];
    int sum=0;
    if (x>=s[i]) sum+=dfs(i-1,x-s[i],y,z);
    if (y>=s[i]) sum+=dfs(i-1,x,y-s[i],z);
    if (z>=s[i]) sum+=dfs(i-1,x,y,z-s[i]);
    sum%=p;
    return dp[x][y][z]=sum;
}
 
int getk(){
    forto(x,0,a)
    forto(y,0,b)
    forto(z,0,c) dp[x][y][z]=-1;
     
    dp[0][0][0]=1;
    return dfs(top,a,b,c);
}
 
void gcd(int a, int b, int &d, int &x, int &y){
    if (b==0){ d=a; x=1; y=0; return; }
    gcd(b,a%b,d,y,x);
    y-=x*(a/b);
}
 
int main(){
    scanf("%d%d%d%d%d",&a,&b,&c,&m,&p);
    n=a+b+c;
     
    forto(i,1,n) f[i]=i;
    gets();
    int sum=getk();
    int num=m+1;
     
    forto(mi,1,m){
        forto(i,1,n) scanf("%d",&f[i]);
        gets();
        if (top!=n){
            sum+=getk(); sum%=p;
        } else num--;
    }
     
    int d,x,y;
    gcd(num,p,d,x,y);
    x%=p; if (x<0) x+=p;
    printf("%d",sum*x%p);
    return 0;
}   

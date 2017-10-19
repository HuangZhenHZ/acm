/**************************************************************
    Problem: 1005
    User: 8300590
    Language: C++
    Result: Accepted
    Time:72 ms
    Memory:4796 kb
****************************************************************/
 
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1010;
 
int p[maxn][maxn];
 
void getp(int n){
    for (int i=2;i<=n;i++){
        int k=i;
        for (int j=2;k!=1;j++)
        while (k%j==0){
            k/=j;
            p[i][j]++;
        }
    }
    for (int i=3;i<=n;i++)
    for (int j=2;j<=n;j++)
        p[i][j]+=p[i-1][j];
}
 
int ans[maxn];
 
inline void cheng(int k){
//  printf("cheng %d\n",k);
     
    for (int i=2;i<=k;i++)
        ans[i]+=p[k][i];
}
 
inline void chu(int k){
//  printf("chu %d\n",k);
     
    for (int i=2;i<=k;i++)
        ans[i]-=p[k][i];
}
 
inline void cc(int n, int m){
    cheng(n); chu(m); chu(n-m);
}
 
vector<int> a;
const int base=10000;
 
void atimesb(int b){
    for (int i=0;i<a.size();i++) a[i]*=b;
    for (int i=0;i<a.size();i++)
    if (a[i]>=base){
        if (i+1>=a.size()) a.push_back(0);
        a[i+1]+=a[i]/base;
        a[i]%=base;
    }
}
 
void writea(){
    printf("%d",a[a.size()-1]);
    for (int i=a.size()-2;i>=0;i--) printf("%04d",a[i]);
}
 
int main(){
    int n; scanf("%d",&n);
    getp(n-2);
     
    int sum=n-2, num=n;
     
    for (int i=1;i<=n;i++){
        int d; scanf("%d",&d);
         
        if (d==0 || d-1>sum){
            printf("0");
            return 0;
        }
         
        if (d!=-1){
            cc(sum,d-1);
            sum-=d-1;
            num--;
        }
    }
     
    if (num==0 && sum!=0){
        printf("0");
        return 0;
    }
     
//  printf("num=%d\n",num);
//  printf("sum=%d\n",sum);
     
    ans[num]+=sum;
     
//  int a=1;
//  for (int i=2;i<=n;i++)
//  while (ans[i]--)
//      a*=i;
         
//  printf("%d",a);
 
    a.push_back(1);
    for (int i=2;i<=n;i++)
    while (ans[i]--)
        atimesb(i);
    writea();
     
    return 0;
}

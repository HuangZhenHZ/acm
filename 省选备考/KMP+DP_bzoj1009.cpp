/**************************************************************
    Problem: 1009
    User: 8300590
    Language: C++
    Result: Accepted
    Time:36 ms
    Memory:960 kb
****************************************************************/
 
#include<cstdlib>
#include<cstdio>
#include<cstring>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
 
void kmp(char s1[], int next1[], char s2[], int next2[]){
    int len1=strlen(s1+1), len2=strlen(s2+1);
    int j=0;
    forto(i,1,len1){
        while (j && s1[i]!=s2[j+1]) j=next2[j];
        if (s1[i]==s2[j+1]) j++;
        next1[i]=j;
    }
}
 
struct matrix{
    int n,m;
    int a[30][30];
    matrix(int n, int m):n(n),m(m){
        forto(i,1,n) forto(j,1,m)
        a[i][j]=0;
    }
};
 
int n,m,modnum;
 
matrix cheng(const matrix &a, const matrix &b){
    matrix c(a.n, b.m);
    forto(i,1,a.n)
    forto(j,1,b.m)
    forto(k,1,a.m){
        c.a[i][j]+=a.a[i][k]*b.a[k][j];
        c.a[i][j]%=modnum;
    }
    return c;
}
 
matrix power(const matrix &a, int n){
    if (n==1) return a;
    matrix p=power(a,n>>1);
    p=cheng(p,p);
    if (n&1) p=cheng(p,a);
    return p;
}   
     
char s[30]; 
int next[30];
 
void makematrix(matrix &a){
    forto(i,0,m-1)
    forto(c,'0','9'){
        int j=i;
        while (j && s[j+1]!=c) j=next[j];
        if (s[j+1]==c) j++;
        a.a[i+1][j+1]++;
        if (a.a[i+1][j+1]==modnum) a.a[i+1][j+1]=0;
        //printf("%d %c %d\n",i,c,j);
    }
}
 
int main(){
    scanf("%d%d%d",&n,&m,&modnum);
    scanf("%s",s+1);
    next[1]=0;
    kmp(s+1, next+1, s, next);
     
    matrix a(m,m);
    makematrix(a);
     
    matrix f=a;
    a=power(a,n);
     
    //forto(i,1,m){
    //  forto(j,1,m) printf("%d ",f.a[i][j]);
    //  printf("\n");
    //}
     
    matrix b(1,m);
    b.a[1][1]=1;
     
    matrix c=cheng(b,a);
     
    //forto(i,1,m)
    //  printf("%d ",c.a[1][i]);
     
    int ans=0;
    forto(i,1,m){
        ans+=c.a[1][i];
        if (ans>modnum) ans-=modnum;
    }
     
    printf("%d",ans);
     
    //forto(i,1,m)
    //forto(j,1,m)
    //  printf("%d ",a.a[i][j]);
         
    //printf("\n");
     
    //for (int i=1;i<=m;i++) printf("%d",next[i]);
     
    return 0;
}

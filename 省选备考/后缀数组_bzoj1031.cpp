/**************************************************************
    Problem: 1031
    User: 8300590
    Language: C++
    Result: Accepted
    Time:736 ms
    Memory:5316 kb
****************************************************************/
 
#include<cstdlib>
#include<cstdio>
#include<cstring>
#define forto(i,a,b) for (int i=(a);i<=(b);i++)
#define fordown(i,a,b) for (int i=(a);i>=(b);i--)
const int maxn=220000;
 
int n;
int sa[maxn],rk[maxn*2],c[maxn],x[maxn];
char s[maxn];
 
void suffix_array(){
    forto(i,1,n) sa[i]=i;
    for (int m=300,k=0; k<n; k?k<<=1:k++){
        forto(i,1,m) c[i]=0;
        forto(i,1,n) c[rk[i]]++;
        forto(i,2,m) c[i]+=c[i-1];
        int p=0;
        forto(i,n-k+1,n) x[++p]=i;
        forto(i,1,n) if (sa[i]>k) x[++p]=sa[i]-k;
        fordown(i,n,1) sa[c[rk[x[i]]]--]=x[i];
        m=1; x[sa[1]]=1;
        forto(i,2,n) x[sa[i]]=rk[sa[i]]==rk[sa[i-1]]&&rk[sa[i]+k]==rk[sa[i-1]+k]?m:++m;
        forto(i,1,n) rk[i]=x[i];
        if (m==n) break;
    }
}
 
int main(){
    scanf("%s",s+1);
    int m=strlen(s+1);
    n=m<<1;
    forto(i,m+1,n) s[i]=s[i-m];
     
    //printf("%s\n",s+1);
    //printf("%d\n",n);
     
    forto(i,1,n) rk[i]=s[i];
    suffix_array();
     
    //forto(i,1,n) printf("%d ",sa[i]);
    //printf("\n");
 
    forto(i,1,n) if (sa[i]<=m) printf("%c",s[sa[i]+m-1]);
    return 0;
}

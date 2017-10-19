/**************************************************************
    Problem: 1008
    User: 8300590
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdlib>
#include<cstdio>
typedef long long LL;
const LL modnum=100003;
 
LL power(LL a, LL n){
    if (n==0) return 1;
    LL p=power(a,n>>1);
    p=(p*p)%modnum;
    if (n&1) p=(p*a)%modnum;
    return p;
}
 
int main(){
    LL m,n; scanf("%lld %lld",&m,&n);
    LL a=power(m,n);
    LL b=(m*power(m-1,n-1))%modnum;
    LL c=a-b;
    if (c<0) c+=modnum;
    printf("%lld",c);
    return 0;
}

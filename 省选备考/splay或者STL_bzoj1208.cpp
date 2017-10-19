/**************************************************************
    Problem: 1208
    User: 8300590
    Language: C++
    Result: Accepted
    Time:320 ms
    Memory:1204 kb
****************************************************************/
 
#include<cstdio>
#include<set>
#define ABS(i) ((i)<(0)?(-(i)):(i))
using namespace std;
typedef set<int>::iterator it;
 
set<int> s;
int c,ans;
 
void done(it i,int b){
    int t=ABS(*i);
    ans=(ans+ABS(t-b))% 1000000;
    s.erase(t);
    s.erase(-t);
}
 
int main(){
    int n; scanf("%d",&n);
    while (n--){
        int a,b; scanf("%d%d",&a,&b);
        if (a==c||s.empty()){
            s.insert(b);
            s.insert(-b);
            c=a;
        } 
        else {
            it i=s.lower_bound(b);
            it j=s.lower_bound(-b);
            if (i==s.end()) done(j,b);
            else if (j==s.end()) done(i,b);
            else if ( *j+b<=*i-b ) done(j,b);
            else done(i,b);
        }
    }
    printf("%d",ans);
    return 0;
}

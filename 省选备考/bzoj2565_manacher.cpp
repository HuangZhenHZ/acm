#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int N=100000+100;

char str[N],s[N<<1];
int f[N<<1],a[N<<1];

int main(){
	scanf("%s",str);
	int n=0;
	for(int i=0;str[i];i++){
		s[++n]='#';
		s[++n]=str[i];
	}
	s[++n]='#';
	
	//printf("%s\n",s+1);
	
	int mx=1,mr=1;
	forto(i,2,n){
		int t=0;
		if (i<mr) t=MIN(f[2*mx-i],mr-i);
		while (i-t-1 && s[i-t-1]==s[i+t+1]) t++;
		f[i]=t;
		if (i+t>mr){ mx=i; mr=i+t; }
	}
	
	//forto(i,1,n) printf("%d",f[i]);
	
	forto(i,1,n) a[i]=i;
	forto(i,1,n) if (i<a[i+f[i]]) a[i+f[i]]=i;
	fordown(i,n-1,1) if (a[i+1]<a[i]) a[i]=a[i+1];
	
	//forto(i,1,n) printf("%d",a[i]);
	
	int ans=0;
	forto(i,1,n){
		int j=i-f[i]-1;
		if (j==0) j=1;
		j=a[j];
		if ((i-j)*2>ans) ans=(i-j)*2;
	}
	
	ans>>=1;
	if (ans==1) ans=0;	
	printf("%d",ans);
	return 0;
}

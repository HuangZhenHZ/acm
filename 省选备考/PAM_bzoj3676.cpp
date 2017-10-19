#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

const int N=300000+100, alpha=26;
typedef long long LL;

int n,s[N],num[N];
int p,last,next[N][alpha],fail[N],len[N],cnt[N];

void init(){
	s[n=0]=len[p=2]=-1;
	fail[fail[last=1]=2]=2;
}

int getfail(int x){
	//printf("in getfail\n");
	while (s[n-len[x]-1]!=s[n]){
		//printf("fail[%d]=%d\n",x,fail[x]);
		x=fail[x];
	}
	//printf("out getfail\n");
	return x;
}

void add(int c){
	s[++n]=c;
	int cur=getfail(last);
	if (!next[cur][c]){
		len[++p]=len[cur]+2;
		fail[p]=next[getfail(fail[cur])][c];
		if (!fail[p]) fail[p]=1;
		next[cur][c]=p;
	}
	last=next[cur][c];
	cnt[last]++;
	//printf("%d %d\n",last,fail[last]);
}

void count(){
	fordown(i,p,3) cnt[fail[i]]+=cnt[i];
}	

char str[N];

int main(){
	scanf("%s",str);
	init();
	for(int i=0;str[i];i++){
		add(str[i]-'a');
		//forto(i,1,p) printf("len[%d]=%d fail[%d]=%d\n",i,len[i],i,fail[i]);
		//printf("\n");
	}
	count();
	LL max=0;
	forto(i,3,p){
		//printf("%d %d %d %d\n",i,len[i],cnt[i],fail[i]);
		if (LL(len[i])*LL(cnt[i])>max) max=LL(len[i])*LL(cnt[i]);
	}
	printf("%lld\n",max);
	return 0;
}













#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;

const int N=200200, alpha=26;

char s[N];
int S,cnt,last;
int a[N],fa[N],l[N],ch[N][alpha];

void add(int x){
	int c=a[x];
	int p=last,np=++cnt;last=np;
	l[np]=x;
	for(;p&&!ch[p][c];p=fa[p])ch[p][c]=np;
	if(!p)fa[np]=S;
	else {
		int q=ch[p][c];
		if(l[p]+1==l[q])fa[np]=q;
		else {
			int nq=++cnt;l[nq]=l[p]+1;
			memcpy(ch[nq],ch[q],sizeof ch[q]);
			fa[nq]=fa[q];
			fa[np]=fa[q]=nq;
			for(;ch[p][c]==q;p=fa[p])ch[p][c]=nq;
		}
	}
}

int sg[N];
bool vis[N];

int get(int x){
	if (vis[x]) return sg[x];
	bool a[30]={false};
	forto(i,0,alpha-1) if (ch[x][i]) a[get(ch[x][i])]=true;
	int i=0; while (a[i]) i++;
	vis[x]=true;
	return sg[x]=i;
}

int main(){
	while (scanf("%s",s+1)>0){
		S=cnt=last=0;
		last=S=++cnt;
		int len=strlen(s+1);
		forto(i,0,len*2){
			fa[i]=l[i]=0; vis[i]=false;
			memset(ch[i],0,sizeof(ch[i]));
		}
		forto(i,1,len) a[i]=s[i]-'a';
		forto(i,1,len) add(i);
		get(1);
		
		int ans=0;
		int m; scanf("%d",&m);
		while (m--){
			scanf("%s",s+1);
			int x=1;
			for(int i=1; s[i]; i++) x=ch[x][s[i]-'a'];
			ans^=sg[x];
		}
		printf(ans?"Alice\n":"Bob\n");
	}
	return 0;
}
			
		
	


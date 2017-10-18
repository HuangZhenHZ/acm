#include<cstdio>
#include<cctype>
#include<queue>
#include<cstring>
using namespace std;

char readchar(){
	int i=getchar();
	while (!isalpha(i)) i=getchar();
	return i;
}

const int maxn=50;

int list[maxn][maxn], order[maxn][maxn], next[maxn];
int a[maxn],b[maxn];
int na[200],nb[200],name[200];
queue<int> q;

void init(){
	memset(next,0,sizeof(next));
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(na,0,sizeof(na));
}	

void engage(int x,int y){
	int m=b[y];
	if (m){
		a[m]=0;
		q.push(m);
	}
	a[x]=y; b[y]=x;
}	

int main(){
	int t; scanf("%d",&t);
	while (t--){
		init();
		int n;
		scanf("%d",&n);
				
		for (int i=1;i<=n;i++){
			char j=readchar();
			na[j]=i;
		}
		for (int i=1;i<=n;i++){
			char j=readchar();
			nb[j]=i;
			name[i]=j;
		}
		for (int i=1;i<=n;i++){
			char c=readchar();
			for (int j=1;j<=n;j++){
				char d=readchar();
				list[na[c]][j]=nb[d];
			}
		}
		for (int i=1;i<=n;i++){
			char c=readchar();
			for (int j=1;j<=n;j++){
				char d=readchar();
				order[nb[c]][na[d]]=j;
			}
		}
		
		for (int i=1;i<=n;i++) q.push(i);
		
		while (!q.empty()){
			int i=q.front(); q.pop();
			int j=list[i][++next[i]];
			if (!b[j]) engage(i,j);
			else if(order[j][i]<order[j][b[j]]) engage(i,j);
			else q.push(i);
		}
		
		for (char i='A';i<='z';i++)
		if (na[i]){
			char j=name[a[na[i]]];
			printf("%c %c\n",i,j);
		}
		printf("\n");
	}
	return 0;
}

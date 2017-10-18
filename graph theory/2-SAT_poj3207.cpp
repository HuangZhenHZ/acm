#include<cstdio>
#include<vector>
#include<stack>
using namespace std;
const int maxn=600;

struct twosat{
	int n;
	vector<int> g[maxn*2];
	bool mark[maxn*2];
	stack<int> s;
	
	void add(int x,int xx,int y,int yy){
		x=x*2+xx;
		y=y*2+yy;
		g[x^1].push_back(y);
		g[y^1].push_back(x);
	}
	
	bool dfs(int x){
		if (mark[x^1]) return false;
		if (mark[x]) return true;
		mark[x]=true;
		s.push(x);
		for (int i=0; i<g[x].size(); i++)
			if (!dfs(g[x][i])) return false;
		return true;
	}
	
	bool solve(){
		for (int i=0;i<n*2;i+=2)
		if (!mark[i] && !mark[i+1]){
			while (!s.empty()) s.pop();
			if (!dfs(i)){
				while (!s.empty()){
					mark[s.top()]=false;
					s.pop();
				}
				if (!dfs(i+1)) return false;
			}
		}
		return true;
	}
} g;

int a[maxn],b[maxn];

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for (int i=1;i<=m;i++){
		scanf("%d %d",&a[i],&b[i]);
		if (a[i]>b[i]){ int c=a[i]; a[i]=b[i]; b[i]=c; }
	}	
	g.n=m;	
	for (int i=1;i<=m;i++)
	for (int j=1;j<=m;j++)
	if ( a[i]<a[j] && a[j]<b[i] && b[i]<b[j] ){	
		g.add(i,0,j,0);
		g.add(i,1,j,1);
	}
	if (g.solve()) printf("panda is telling the truth..."); else printf("the evil panda is lying again");
	return 0;
}

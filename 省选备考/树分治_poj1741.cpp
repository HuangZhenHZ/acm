#include<cstdlib>
#include<cstdio>
#include<algorithm>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

const int inf=0x7fffffff, N=11000;

struct E{ int to,dis,ne; } e[N<<1];
int n,k,la[N],e_top;

void add(int x, int y, int z){
	e[++e_top]=(E){y,z,la[x]}; la[x]=e_top;
	e[++e_top]=(E){x,z,la[y]}; la[y]=e_top;
}

int bal[N],root;

int getbal(int x, int n){
	bal[x]=0;
	int sum=1;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (bal[y]==-1){
			int t=getbal(y,n);
			bal[x]=MAX(bal[x],t);
			sum+=t;
		}
	}
	bal[x]=MAX(bal[x],n-sum);
	if (root==0||bal[x]<bal[root]) root=x;
	return sum;
}

bool vis[N];
int dep1[N],d1_top;
int dep2[N],d2_top;

void getdep(int x, int now){
	dep1[++d1_top]=now;
	dep2[++d2_top]=now;
	vis[x]=true;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to, z=e[i].dis;
		if (bal[y]!=-2 && vis[y]==false) getdep(y,now+z);
	}
}

int cal(int dep[], int top){
	std::sort(dep+1,dep+top+1);
	//printf("dep ");
	//forto(i,1,top) printf("%d ",dep[i]);
	//printf("\n");
	int j=top, sum=0;
	forto(i,1,top){
		while (j && dep[i]+dep[j]>k) j--;
		if (i<j) sum+=j-i;
	}
	//printf("cal sum=%d\n",sum);
	return sum;
}	

int solve(int x, int n){
	//printf("in solve x=%d n=%d\n",x,n);
	int ans=0;
	d1_top=d2_top=0;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to, z=e[i].dis;
		if (bal[y]==-2) continue;
		getdep(y,z);
		ans-=cal(dep1,d1_top);
		//printf("%d %d\n",y,ans);
		d1_top=0;
	}
	dep2[++d2_top]=0;
	ans+=cal(dep2,d2_top);
	//printf("%d\n",ans);
	//printf("out solve x=%d n=%d ans=%d\n",x,n,ans);
	return ans;
}

int init(int x){
	int size=1; bal[x]=-1; vis[x]=0;
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		if (bal[y]>=0) size+=init(y);
	}
	return size;
}

int dfs(int x, int n){
	//printf("dfs x=%d n=%d\n",x,n);
	root=0;
	getbal(x,n); x=root;
	bal[x]=-2;
	int ans=solve(x,n);
	for(int i=la[x];i;i=e[i].ne){
		int y=e[i].to;
		//printf("%d\n",y);
		if (bal[y]!=-2) ans+=dfs(y,init(y));
	}
	//printf("dfs x=%d n=%d ans=%d\n",x,n,ans);
	return ans;
}
		
int main(){
	for( scanf("%d%d",&n,&k); n; scanf("%d%d",&n,&k) ){
		forto(i,1,n) la[i]=0;
		e_top=0;
		
		forto(i,2,n){
			int x,y,z; scanf("%d%d%d",&x,&y,&z);
			//printf("%d %d %d\n",x,y,z);
			add(x,y,z);
		}
		
//		forto(x,1,n){
//			printf("%d : ",x);
//			for(int i=la[x];i;i=e[i].ne) printf("%d ",e[i].to);
//			printf("\n");
//		}
			
		forto(i,1,n){
			bal[i]=-1;
			vis[i]=0;
		}
		printf("%d\n",dfs(1,n));
	}
	return 0;
}

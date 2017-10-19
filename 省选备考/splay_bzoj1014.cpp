#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#define nt(x) (ch[fa[x]][1]==x)

const int N=300000;

int fa[N],ch[N][2],size[N],hash[N],top;
char a[N];
int hmi[N];

void ud(int x){
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
	hash[x]=hash[ch[x][0]]*hmi[size[ch[x][1]]+1] + (a[x]-'a'+1)*hmi[size[ch[x][1]]] + hash[ch[x][1]];
}

void rtt(int x){
	int y=fa[x], z=fa[y]; bool p=nt(x);
	if (z) ch[z][nt(y)]=x;
	fa[ch[x][!p]]=y; fa[y]=x; fa[x]=z;
	ch[y][p]=ch[x][!p]; ch[x][!p]=y;
	ud(y);
}

void splay(int x){
	//static int sta[N],top;
	//sta[top=1]=x;
	//for(int y=x;fa[y];y=fa[y]) sta[++top]=fa[y];
	while (fa[x]){
		int y=fa[x];
		if (fa[y]) rtt(nt(x)^nt(y)?x:y);
		rtt(x);
	}
	ud(x);
	//printf("!!\n");
}

int find(int x, int s){
	while (size[ch[x][0]]+1!=s)
	if (s>size[ch[x][0]]+1){
		s-=size[ch[x][0]]+1;
		x=ch[x][1];
	} else x=ch[x][0];
	splay(x);
	return x;
}

void split(int x, int s, int &l, int &r){
	if (s<=0){ l=0; r=x; return; }
	if (s>=size[x]){ l=x; r=0; return; }
	l=find(x,s); r=ch[l][1];
	ch[l][1]=0; fa[r]=0; ud(l);
	return;
}

int merge(int l, int r){
	if (l==0) return r;
	if (r==0) return l;
	l=find(l,size[l]);
	ch[l][1]=r; fa[r]=l; ud(l);
	return l;
}

int insert(int x, int s, char c){
	a[++top]=c; ud(top);
	int l,r; split(x,s,l,r);
	return merge(merge(l,top),r);
}

int change(int x, int s, char c){
	int l,r; split(x,s-1,l,r);
	r=find(r,1);
	a[r]=c; ud(r);
	return merge(l,r);
}

int root;

int gethash(int x, int s){
	int a,b,c,t;
	split(root,x-1,a,t);
	split(t,s,b,c);
	int ans=hash[b];
	root=merge(merge(a,b),c);
	//printf("gethash(%d,%d)=%d size[%d]=%d\n",x,s,ans,b,size[b]);
	return ans;
}

int getans(int x, int y){
	int l=0, r=size[root]-MAX(x,y)+1;
	while (l<r){
		int m=(l+r+1)>>1;
		if (gethash(x,m)==gethash(y,m)) l=m; else r=m-1;
	}
	return l;
}	

char str[N];


int main(){
	hmi[0]=1;
	forto(i,1,N-1) hmi[i]=hmi[i-1]*29;
	
	scanf("%s",str);
	for(int i=0;str[i];i++){
		a[++top]=str[i]; ud(top);
		root=merge(root,top);
		//printf("i=%d size=%d\n",i,size[root]);
	}
	
	int m; scanf("%d",&m);
	while (m--){
		scanf("%s",str);
		if (str[0]=='Q'){
			int x,y; scanf("%d%d",&x,&y);
			printf("%d\n",getans(x,y));
		}
		if (str[0]=='R'){
			int x; char c[10]; scanf("%d%s",&x,c);
			root=change(root,x,c[0]);
		}
		if (str[0]=='I'){
			int x; char c[10]; scanf("%d%s",&x,c);
			root=insert(root,x,c[0]);
		}
	}
	return 0;
}
	














	
	
	

#include<cstdlib>
#include<cstdio>

#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)

#define ABS(x) ((x)>=0?(x):-(x))

const int N=2200;

int a[N],lc[N],rc[N],d[N],size[N];

int merge(int x, int y){
	if (x==0) return y;
	if (y==0) return x;
	if (a[x]<a[y]){ int z=x; x=y; y=z; }
	rc[x]=merge(rc[x],y);
	if (d[rc[x]]>d[lc[x]]){ int t=lc[x]; lc[x]=rc[x]; rc[x]=t; }
	d[x]=d[rc[x]+1];
	size[x]=size[lc[x]]+size[rc[x]]+1;
	return x;
}

int pop(int x){
	return merge(lc[x],rc[x]);
}	

int sta[N],len[N],top;

int main(){
	int n; scanf("%d",&n);
	forto(i,1,n) scanf("%d",&a[i]);
	forto(i,1,n) size[i]=1;
	
	forto(i,1,n){
		sta[++top]=i; len[top]=1;
		while (top>=2 && a[sta[top]]<a[sta[top-1]]){
			sta[top-1]=merge(sta[top-1],sta[top]);
			len[top-1]=len[top-1]+len[top];
			top--;
			while (size[sta[top]]>(len[top]+1)>>1) sta[top]=pop(sta[top]);
		}
	}
	
	int j=0, ans=0;
	forto(i,1,top) while (len[i]--){
		j++;
		ans+=ABS(a[j]-a[sta[i]]);
	}
	printf("%d",ans);
	return 0;
}
	
				
			
		
	


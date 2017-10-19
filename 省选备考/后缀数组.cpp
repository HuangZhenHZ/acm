... ...


int sa[maxn],rk[maxn*2],c[maxn],x[maxn],y[maxn];

void suffix_array(){
	forto(i,1,n) sa[i]=i;
	
	int p=200;
	for(int k=0; k<n; k?k<<=1:k++){
		forto(i,1,p) c[i]=0;
		forto(i,1,n) c[rk[i]]++;
		forto(i,2,p) c[i]+=c[i-1];
		
		int t=0;
		forto(i,n-k+1,n) x[++t]=i;
		forto(i,1,n) if (sa[i]>k) x[++t]=sa[i]-k;
		
		fordown(i,n,1) sa[c[rk[x[i]]]--]=x[i];
		p=1; x[sa[1]]=1;
		forto(i,2,n) x[sa[i]]= rk[sa[i]]==rk[sa[i-1]] && rk[sa[i]+k]==rk[sa[i-1]+k] ? p:++p;
		
		forto(i,1,n) rk[i]=x[i];
		if (p==n) break;
	}
}

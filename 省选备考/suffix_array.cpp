int n;
int sa[maxn],rk[maxn*2],c[maxn],x[maxn],h[maxn];
char s[maxn];
 
void suffix_array(){
    forto(i,1,n) sa[i]=i;
    for (int m=300,k=0; k<n; k?k<<=1:k++){
        forto(i,1,m) c[i]=0;
        forto(i,1,n) c[rk[i]]++;
        forto(i,2,m) c[i]+=c[i-1];
        int p=0;
        forto(i,n-k+1,n) x[++p]=i;
        forto(i,1,n) if (sa[i]>k) x[++p]=sa[i]-k;
        fordown(i,n,1) sa[c[rk[x[i]]]--]=x[i];
        m=1; x[sa[1]]=1;
        forto(i,2,n) x[sa[i]]=rk[sa[i]]==rk[sa[i-1]]&&rk[sa[i]+k]==rk[sa[i-1]+k]?m:++m;
        forto(i,1,n) rk[i]=x[i];
        if (m==n) break;
    }
}

void geth(){ 
    forto(i,1,n)
	if (rk[i]!=n){
    	h[i]=h[i-1]-1;
		if (h[i]<0) h[i]=0;
    	int j=sa[rk[i]+1];
    	while (s[i+h[i]]==s[j+h[i]]) h[i]++;
    }
}

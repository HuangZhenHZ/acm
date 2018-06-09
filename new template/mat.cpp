struct mat { int n,m,x[N][N]; };

mat operator* (const mat &a, const mat &b){
	mat c; c.n=a.n; c.m=b.m;
	forto(i,1,c.n) forto(j,1,c.m){
		LL sum=0;
		forto(k,1,a.m) sum=(sum+LL(a.x[i][k])*LL(b.x[k][j]))%MOD;
		c.x[i][j]=sum%MOD;
	}
	return c;
}

mat iden(int n){
	mat a; a.n=a.m=n;
	forto(i,1,n) forto(j,1,n) a.x[i][j]=0;
	forto(i,1,n) a.x[i][i]=1;
	return a;
}

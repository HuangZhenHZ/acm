#include <bits/stdc++.h>
#define forto(i,a,b) for(int i=(a);i<=(b);i++)
#define fordown(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(a,b) ((a)<=(b)?(a):(b))
#define MAX(a,b) ((a)>=(b)?(a):(b))
#define IL inline

typedef long long LL;
const int maxlen=1000;
const int MOD=100000000;

struct bigint{
	int len,x[maxlen+2];
	
	IL bigint(int a){
		memset(x,0,sizeof(x));
		for(len=0;a;a/=MOD) x[++len]=a%MOD;
	}
	
	IL void operator+= (const bigint &a){
		forto(i,1,a.len) x[i]+=a.x[i];
		if (a.len>len) len=a.len;
		forto(i,1,len) if (x[i]>=MOD) { x[i]-=MOD; x[i+1]+=1; }
		if (x[len+1]) len++;
	}
	
	IL void operator-= (const bigint &a){
		forto(i,1,a.len) x[i]-=a.x[i];
		forto(i,1,len) if (x[i]<0) { x[i]+=MOD; x[i+1]-=1; }
		while (len && !x[len]) len--;
	}
	
	IL void operator*= (int a){
		static LL up; up=0;
		forto(i,1,len){
			up+=LL(x[i])*LL(a);
			x[i]=up%MOD;
			up/=MOD;
		}
		if (up) x[++len]=up;
	}
	
	inline void operator/= (int a){
		if (a==0) exit(1);
		fordown(i,len,2) { x[i-1]+=x[i]%a*MOD; x[i]/=a; }
		x[1]/=a;
		while (len && !x[len]) len--;
	}
	
	inline int operator% (int a) const{
		if (a==0) exit(2);
		int ans=0;
		fordown(i,len,1) ans=(LL(ans)*MOD+x[i])/a;
		return ans;
	}
	
	inline void c2(){
		forto(i,1,len) x[i]<<=1;
		forto(i,1,len) if (x[i]>=MOD) { x[i]-=MOD; x[i+1]+=1; }
		if (x[len+1]) len++;
	}
	
	inline void div2(){
		fordown(i,len,2) { x[i-1]+=(x[i]&1)*MOD; x[i]>>=1; }
		x[1]>>=1;
		if (len && !x[len]) len--;
	}
	
	inline void print() const{
		printf("%d",x[len]);
		fordown(i,len-1,1) printf("%08d",x[i]);
	}
};

inline int comp(const bigint &a, const bigint &b){
	if (a.len>b.len) return 1;
	if (a.len<b.len) return -1;
	fordown(i,a.len,1){
		if (a.x[i]>b.x[i]) return 1;
		if (a.x[i]<b.x[i]) return -1;
	}
	return 0;
}

inline bool operator== (const bigint &a, const bigint &b){ return comp(a,b)==0; }
inline bool operator!= (const bigint &a, const bigint &b){ return comp(a,b)!=0; }
inline bool operator>  (const bigint &a, const bigint &b){ return comp(a,b)> 0; }
inline bool operator>= (const bigint &a, const bigint &b){ return comp(a,b)>=0; }
inline bool operator<  (const bigint &a, const bigint &b){ return comp(a,b)< 0; }
inline bool operator<= (const bigint &a, const bigint &b){ return comp(a,b)<=0; }

inline bigint operator+ (bigint a, const bigint &b){ a+=b; return a; }
inline bigint operator- (bigint a, const bigint &b){ a-=b; return a; }
inline bigint operator* (bigint a, int b){ a*=b; return a; }
inline bigint operator/ (bigint a, int b){ a/=b; return a; }

inline bigint operator* (const bigint &a, const bigint &b){
	if (a.len==0||b.len==0) return bigint(0);
	bigint c(0);
	forto(i,1,a.len) forto(j,1,b.len){
		static LL t; t=a.x[i]*b.x[j];
		static int k; k=i+j-1;
		c.x[k]+=LL%MOD;
		c.x[k+1]+=LL/MOD;
		if (c.x[k]>=MOD) { c.x[k]-=MOD; c.x[k+1]+=1; }
		if (c.x[k+1]>=MOD) { c.x[k+1]-=MOD; c.x[k+2]+=1; }
	}
	c.len=a.len+b.len;
	if (!c.x[c.len]) c.len--;
	return c;
}

inline bigint operator/ (bigint a, bigint b){
	if (!b.len) exit(3);
	static bigint ans,k;
	ans=bigint(0); k=bigint(1);
	while (b<a) { k.c2(); b.c2(); }
	while (k.len) {
		if (a>=b) { a-=b; ans+=k; }
		k.div2(); b.div2();
	}
	return ans;
}

inline bigint operator% (bigint a, bigint b){
	if (!b.len) exit(4);
	static int i; i=1;
	while (b<a){ b.c2(); i++; }
	while (i--){
		if (a>=b) a-=b;
		b.div2();
	}
	return a;
}

inline void operator*= (bigint &a, const bigint &b){ a=a*b; }
inline void operator/= (bigint &a, bigint b){ a=a/b; }
inline void operator%= (bigint &a, bigint b){ a=a%b; }

inline bigint gcd(bigint a, bigint b){
	while (a.len && b.len) if (a>=b) a%=b; else b%=a;
	return a.len?a:b;
}

struct number{
	bigint x,y;
	bool s;
	number():x(0),y(1),s(false){}
	number(int x, int y=1, bool s=false):x(x),y(y),s(s){}
	number(const bigint &x, const bigint &y=bigint(1), bool s=false):x(x),y(y),s(s){}
	
	inline void simp(){
		bigint d=gcd(x,y);
		x/=d; y/=d;
		if (x==0) s=false;
		if (y==0) thr("分母为零");
	}
	inline void print1() const{
		if (s) printf("-");
		x.print();
		if (y!=bigint(1)){
			printf(" / ");
			y.print();
		}
	}
	inline void print2() const;
	inline void print3() const;
	inline void print() const{
		print1();
		printf("\n");
		if (y!=bigint(1)){
			printf("          or\n          ");
			print2();
			printf("\n");
		}
		printf("          or\n          ");
		print3();
		printf("\n");
	}	
};

inline int comp(const number &a, const number &b){
	if (!a.s && b.s) return 1;
	if (a.s && !b.s) return -1;
	return comp(a.x*b.y, b.x*a.y);
}
inline bool operator== (const number &a, const number &b){ return comp(a,b)==0; }
inline bool operator!= (const number &a, const number &b){ return comp(a,b)!=0; }
inline bool operator>  (const number &a, const number &b){ return comp(a,b)> 0; }
inline bool operator>= (const number &a, const number &b){ return comp(a,b)>=0; }
inline bool operator<  (const number &a, const number &b){ return comp(a,b)< 0; }
inline bool operator<= (const number &a, const number &b){ return comp(a,b)<=0; }

inline number operator* (const number &a, const number &b){
	number c(a.x*b.x, a.y*b.y, a.s^b.s);
	c.simp();
	return c;
}
inline number operator/ (const number &a, const number &b){
	number c(a.x*b.y, a.y*b.x, a.s^b.s);
	c.simp();
	return c;
}
inline number operator+ (const number &a, const number &b){
	number c; 
	if (a.s==b.s) c=number(a.x*b.y+b.x*a.y, a.y*b.y, a.s);
	else if (a.x*b.y > b.x*a.y) c=number(a.x*b.y - b.x*a.y, a.y*b.y, a.s);
	else c=number(b.x*a.y - a.x*b.y, a.y*b.y, b.s);
	c.simp();
	return c;
}
inline number operator- (const number &a, const number &b){
	return a+b*number(1,1,true);
}

inline void operator+= (number &a, const number &b){ a=a+b; }
inline void operator-= (number &a, const number &b){ a=a-b; }
inline void operator*= (number &a, const number &b){ a=a*b; }
inline void operator/= (number &a, const number &b){ a=a/b; }
inline void number::print2() const{
	if (s) printf("-");
	bigint z=x/y;
	z.print();
	printf(".");
	number a=(*this)-number(z);
	number k(1);
	forto(i,1,5){
		k=k/number(10);
		int t=0;
		while (a>=k){
			a=a-k;
			t++;
		}
		printf("%d",t);
	}
	k=k/number(10);
	int t=0;
	while (a>=k){
		a=a-k;
		t++;
	}
	if (a>=k/number(2)) t++;
	printf("%d",t);
}

inline void number::print3() const{
	number t=*this;
	if (t.s){
		printf("-");
		t.s=false;
	}
	int k=0;
	while (t>=number(10)){
		t/=number(10);
		k++;
	}
	while (t<number(1)){
		t*=number(10);
		k--;
	}
	t.print2();
	printf("*10^%d",k);
}	

inline number pow(number a, int n){
	static bool s[30];
	static int t;
	static number p;
	
	for (t=0;n;n>>=1) s[++t]=n&1;
	for (p=number(1);t;t--){
		p=p*p;
		if (s[t]) p=p*a;
	}
	return p;
}

inline int pri(char a){
	if (a=='(') return 0;
	if (a=='c') return 1;
	if (a=='+'||a=='-') return 2;
	if (a=='*'||a=='/'||a=='%') return 3;
	if (a=='^') return 4;
	return 0;
}
inline number __ope(const number &a, const number &b, char s){
	if (s=='+') return a+b;
	if (s=='-') return a-b;
	if (s=='*') return a*b;
	if (s=='/') return a/b;
	if (s=='%'){
		if (a.y!=bigint(1)||b.y!=bigint(1)) thr("暂不支持分数取模");
		if (a.s||b.s) thr("暂不支持负数取模");
		return number(a.x%b.x);
	}	
	if (s=='^'){
		if (b.y!=bigint(1)) thr("指数暂时不能为分数");
		if (b.s) thr("指数暂时不能为负数");
		if (b.x.len>1) thr("为避免乘法溢出，已限制指数必须小于10000");
		return pow(a, b.x.x[1]);
	}
	if (s=='c') return number(comp(a,b));
	return number(0);
} 

#define maxstrlen 10001 
#define maxstalen 101 

char s[maxstrlen];
number num[maxstalen];
char sym[maxstalen];
int topnum, topsym;

inline void ope(){
	num[topnum-1]=__ope(num[topnum-1],num[topnum],sym[topsym]);
	topnum--; topsym--;
}
number save[101];
inline void read_and_calc(int t){
	gets(s);
	topnum=0, topsym=0;
	num[1]=number(0);
	bool b=false;
	
	for(int i=0;s[i];){
		if ( (s[i]>='0'&&s[i]<='9') || ( (s[i]=='-'||s[i]=='+') && b==false) || s[i]=='#' ){
			if (b==true) thr("多余的数字（缺少运算符）");
			if (s[i]=='+') i++; else
			if (s[i]=='-'){
				num[++topnum]=number(1,1,true);
				sym[++topsym]='*';
				i++;
			} else 
			if (s[i]=='#'){
				b=true;
				i++;
				if (s[i]<'0'||s[i]>'9') thr("#号之后应有数字");
				int k=0;
				while (s[i]>='0' && s[i]<='9'){
					k=k*10+(s[i]-'0');
					i++;
				}
				if (k==0||k>=t) thr("引用了未使用的结果");
				num[++topnum]=save[k];
			} else {
				b=true;
				number t;
				while (s[i]>='0' && s[i]<='9'){
					t=t*number(10)+number(s[i]-'0');
					i++;
				}
				if (s[i]=='.'){
					i++;
					number k(1);
					while (s[i]>='0' && s[i]<='9'){
						k/=10;
						t+=(s[i]-'0')*k;
						i++;
					}
				}
				num[++topnum]=t;
			}
		} else
		if (s[i]=='('){
			if (b==true) thr("左括号前缺少运算符"); 
			sym[++topsym]='(';
			i++;
		} else
		if (s[i]==')'){
			if (b==false) thr("右括号前缺少数字"); 
			while (topsym && sym[topsym]!='(') ope();
			if (topsym==0) thr("括号不匹配");
			topsym--;
			i++;
		} else
		if (s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^'||s[i]=='%'||s[i]=='c'){
			if (b==false) thr("多余的运算符（缺少数字）");
			b=false;
			while (pri(s[i])<=pri(sym[topsym])) ope();
			sym[++topsym]=s[i];
			i++;
		} else
		if (s[i]==' ') i++; else thr("输入中含有多余内容"); 
	}
	while (topsym && sym[topsym]!='(') ope();
	if (topsym) thr("括号不匹配"); 
	printf("Out [%02d]: ",t);
	num[1].print();
	printf("\n");
	save[t]=num[1];
}

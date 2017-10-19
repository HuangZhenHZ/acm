... ...

struct E{int to,ne} e[maxm*2];
int la[maxn],top;

void push(int &i,int d){
	e[++top]=(E){d,i};
	i=top;
}

void addedge(int x, int y){
	push(la[x],y);
	push(la[y],x);
}
//or

void addedge(int x, int y){
	e[++top]=(E){y,la[x]}; la[x]=top;
	e[++top]=(E){x,la[y]}; la[y]=top;
}

int dfn[N],low[N],time;
int scc[N],cnt;
int sta[N],top;
int size[N];

void dfs(int x){
    dfn[x]=low[x]=++time;
    sta[++top]=x;
    forE(i,x){
        int y=e[i].to;
        if (!scc[y]){
            if (!dfn[y]) dfs(y);
            if (low[y]<low[x]) low[x]=low[y];
        }
    }
    if (dfn[x]==low[x]){
        cnt++;
        while (!scc[x]){
            scc[sta[top--]]=cnt;
            size[cnt]++;
        }
    }
}

forto(i,1,n) if (!dfn[i]) dfs(i);


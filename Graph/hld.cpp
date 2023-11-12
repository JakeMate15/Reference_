struct DT{
    int n;
    vll st,lazy;
    DT(int _n):n(_n),st(4*_n+1),lazy(4*_n+1){}
    void push(int l, int r, int i) {
        if (!lazy[i]) return;
        st[i] += (r-l+1) * lazy[i];
        if (l != r) {
            lazy[2*i+1] += lazy[i];
            lazy[2*i+2] += lazy[i];
        }
        lazy[i] = 0;
    }
    void update(int l, int r, int a, int b, ll x, int i) {
        push(l, r, i);
        if (a > r || b < l) return;
        if (a <= l && r <= b) {
            lazy[i] += x;
            push(l, r, i);
            return;
        }
        int m = l+r>>1;
        update(l, m, a, b, x, 2*i+1);
        update(m+1, r, a, b, x, 2*i+2);
        st[i] = st[2*i+1] + st[2*i+2];
    }
    ll query(int l, int r, int a, int b, int i) {
        if (a > r || b < l) return 0;
        push(l, r, i);
        if (a <= l && r <= b) return st[i];
        int m = l+r>>1;
        return query(l, m, a, b, 2*i+1) + query(m+1, r, a, b, 2*i+2);
    }
};
struct hld{
    int n,timer;
    vi *T,deep,CH,SZE,PT,P,PTN;
    DT st;
    hld(int _n):n(_n),deep(_n+1),CH(_n+1),SZE(_n+1),PT(_n+1),PTN(_n+1),P(_n+1),st(_n){
        timer=1; 
        T=new vector<int>[_n+1];
    }
    void dfs(int u,int p){
        P[u]=p,SZE[u]+=1,deep[u]=deep[p]+1;
        for(auto v:T[u]){
            if(v==p)continue;
            dfs(v,u);
            SZE[u]+=SZE[v];
        }
    }
    void dfsHLD(int u,int p,int head){
        int mv=-1,cmv=-1;
        PTN[u]=timer,PT[timer++]=u,CH[u]=head;
        for(auto v:T[u]){
            if(v==p) continue;
            if(cmv<SZE[v]) mv=v, cmv=SZE[v];
        }
        if(mv!=-1) dfsHLD(mv,u,head);
        for(auto v:T[u]){
            if(v==p || mv==v)continue;
            dfsHLD(v,u,v);
        }
    }
    void update(int u,int v,int k){
        while(CH[u]!=CH[v]){
            if(deep[CH[u]]<deep[CH[v]])swap(u,v);
            st.update(0,n,PTN[CH[u]],PTN[u],k,0);
            u=P[CH[u]];
        }
        if(PTN[u]>PTN[v]) swap(u,v);
        st.update(0,n,PTN[u],PTN[v],k,0);
    }
    ll  query(int u,int v){
        ll res=0;
        while(CH[u]!=CH[v]){
            if(deep[CH[u]]<deep[CH[v]])swap(u,v);
            res+=st.query(0,n,PTN[CH[u]],PTN[u],0);
            u=P[CH[u]];
        }
        if(PTN[u]>PTN[v]) swap(u,v);
        return res+st.query(0,n,PTN[u],PTN[v],0);
    }
};
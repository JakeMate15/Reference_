const ll HASH =  257, MOD = 1e9 + 21;
const int N=8e5+5;

//Normal y Reverso
ll poww[MAX];
ll st[N],rst[N];
// x for normal s[i]*p[i] and x1 for reverse s[i]*P[n-i-1]
//If we need to comparate que neeed to multiplace for the first caracter
// query1 for p[n-r-1] and query2 for p[i]
void update(int l, int r, int idx, ll x,ll x1, int i){
    if(l==r) {st[i]=x,rst[i]=x1; return;}
    int m=l+r>>1;
    if(idx<=m) update(l,m,idx,x,x1,i*2+1);
    else update(m+1,r,idx,x,x1,i*2+2);
    st[i]=(st[i*2+1]+st[i*2+2]);
    rst[i]=(rst[i*2+1]+rst[i*2+2]);
}
ll query1(int l, int r, int a, int b, int i){
    if(a>r||b<l) return 0;
    if(a<=l&&r<=b) return st[i];
    int m=l+r>>1;
    return query1(l,m,a,b,2*i+1)+query1(m+1,r,a,b,2*i+2);
}
ll query2(int l, int r, int a, int b, int i){
    if(a>r||b<l) return 0;
    if(a<=l&&r<=b) return rst[i];
    int m=l+r>>1;
    return query2(l,m,a,b,2*i+1)+query2(m+1,r,a,b,2*i+2);
}
const int N=4e5+5;
int st[N], arr[N];
void build(int l, int r, int i){
    if(l==r){st[i]=arr[l]; return;}
    int m=l+r>>1;
    build(l,m,2*i+1); build(m+1,r,2*i+2);
    st[i]=st[2*i+1]+st[2*i+2];
}
void update(int l, int r, int idx, int x, int i){
    if(l==r) {st[i]+=x; return;}
    int m=l+r>>1;
    if(idx<=m) update(l,m,idx,x,i*2+1);
    else update(m+1,r,idx,x,i*2+2);
    st[i]=st[i*2+1]+st[i*2+2];
}
int query(int l, int r, int a, int b, int i){
    if(a>r||b<l) return 0;
    if(a<=l&&r<=b) return st[i];
    int m=l+r>>1;
    return query(l,m,a,b,2*i+1)+query(m+1,r,a,b,2*i+2);
}
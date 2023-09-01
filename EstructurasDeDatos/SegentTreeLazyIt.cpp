const int N=2e5+10;
ll st[4*N+10],lazy[4*N+10],arr[N];
void build(int l, int r, int i){
    lazy[i]=0;
    if(l==r){st[i]=arr[l];return;}
    int m=(l+r)>>1;
    build(l,m,2*i+1);
    build(m+1,r,2*i+2);
    st[i]=st[2*i+1]+st[2*i+2];
}
void push(int l, int r, int i){
    if(!lazy[i])return;
    st[i]+=(r-l+1)*lazy[i];
    if(l!=r){
        lazy[2*i+1]+=lazy[i];
        lazy[2*i+2]+=lazy[i];
    }
    lazy[i]=0;
}
void update(int l, int r, int a, int b, ll x, int i){
    push(l,r,i);
    if(a>r||b<l)return;
    if(a<=l&&r<=b){
        lazy[i]+=x;
        push(l,r,i);
        return;
    }
    int m=(l+r)>>1;
    update(l,m,a,b,x,2*i+1);update(m+1,r,a,b,x,2*i+2);
    st[i]=st[2*i+1]+st[2*i+2];
}
ll query(int l, int r, int a, int b, int i){
    if(a>r||b<l)return 0;
    push(l,r,i);
    if(a<=l&&r<=b) return st[i];
    int m=(l+r)>>1;
    return query(l,m,a,b,2*i+1)+query(m+1,r,a,b,2*i+2);
}
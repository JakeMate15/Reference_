#define inf INT_MAX
const int MAX=5e5+2;
typedef pair<ll, ll> item;
struct node{
    item val;
    node *l, *r;
    node(): l(nullptr),r(nullptr),val({inf,inf}){};
    node(node *_l,node *_r):l(_l),r(_r){
        val=min(l->val,r->val);
    }
    node(ll value,ll pos):r(nullptr),l(nullptr){
        val=make_pair(value,pos);
    }
};
pair<ll,ll>all;
vector<node*>versions(MAX,nullptr);
node* build(int l,int r){
    if(l==r)return  new node(inf,l);
    int m=(l+r)/2;
    return new node(build(l,m),build(m+1,r));
}

node* update(node *root,int l,int r,int pos,int val){
    if(l==r){
        return new node(val,pos);}
    int m=(l+r)/2;
    if(pos<=m) return new node(update(root->l,l,m,pos,val),root->r);
    return new node(root->l,update(root->r,m+1,r,pos,val));
}
item query(node *root,int l,int r,int a,int b){
    if(a>r || b<l) return all;
    if(a<=l && r<=b) return root->val;
    int m=(l+r)/2;
    return min(query(root->l,l,m,a,b),query(root->r,m+1,r,a,b));
}
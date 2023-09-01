struct dinamicStree{
    int l,r;
    dinamicStree *left=nullptr,*right=nullptr;
    ll sum=0;
    dinamicStree(int l1,int r1){
        l=l1,r=r1;
    }
};
void updateD(int l,int r,int idx,ll x,dinamicStree *node){
    if(l==r){ node->sum+=x;return;}
    int m=(l+r)>>1;
    ll sum=0;
    if(idx<=m){
        node->left=(node->left==nullptr?new dinamicStree(l,m):node->left);
        updateD(l,m,idx,x,node->left);
    }
    else{
        node->right=(node->right==nullptr?new dinamicStree(m+1,r):node->right);
        updateD(m+1,r,idx,x,node->right);
    } 
    node->sum=(node->left!=nullptr?node->left->sum:0)+(node->right!=nullptr?node->right->sum:0);
}
ll queryD(int a,int b,dinamicStree *node){
    if(node==nullptr) return 0;
    if(a>node->r || b<node->l) return 0;
    if(a<=node->l && node->r<=b) return node->sum;
    return queryD(a,b,node->left)+queryD(a,b,node->right);
}
struct Node {
	int val=0;
	ll weight, len=1,lazy=0,sum=0;
	Node *l, *r;
	Node(int c) : val(c) ,weight(rand()), l(NULL), r(NULL) {}
} *treap;
int size(Node *root) { return root ? root->len : 0; }
ll sum(Node *root){ return root? root->sum:0;}
void pushDown(Node *&root){
	if(!root || !root->lazy) return;
    if(root->l) root->l->lazy+=root->lazy;
    if(root->r) root->r->lazy+=root->lazy;
	ll num=root->lazy;num*=size(root);
	root->sum+=num;root->lazy=0;
}
void recal(Node *&root){
	if(!root) return;
	root->len=1+size(root->l)+size(root->r);
	root->sum=sum(root->l)+sum(root->r)+root->val;
	root->val+=root->lazy;
	pushDown(root);
}
void split(Node *root, Node *&l, Node *&r, int val) {
	recal(root);
	if (!root) l = r = NULL;
	else if (size(root->l) < val) {
		split(root->r, root->r, r, val - size(root->l) - 1); l = root; recal(l);
	} else {
		split(root->l, l, root->l, val); r = root; recal(r);
	}
	recal(root);
}
void merge(Node *&root, Node *l, Node *r) {
	recal(l);recal(r);
	if (!l || !r ){root = (!(l)?r:l);}
	else if (l->weight < r->weight) {
		merge(l->r, l->r, r); root = l;
	} else {
		merge(r->l, l, r->l); root = r;
	}
	root->len=1+size(root->l)+size(root->r);
}
// Not necesary functions indexed in 1
void insert(Node *&root,Node *nNode,int pos){
    Node *l=NULL,*r=NULL,*aux=NULL;
    split(root,l,r,pos-1);
    merge(aux,l,nNode);
    merge(root,aux,r);
}
void delateRange(Node *&root,int l, int r){
    Node *l1,*r1,*l2,*r2,*aux2;
    split(root,l1,r1,l-1);
    split(r1,r1,r2,r-l+1);
    merge(root,l1,r2);
}
// queries if you dont need this you can delete recal and push-down
// rembember change the size
ll query(Node *&root,int l,int r){
	Node *l1,*r1,*l2,*r2;
	split(root,l1,r1,l-1);
	split(r1,r1,l2,r-l+1);
	ll res=sum(r1);
	merge(root,l1,r1);merge(root,root,l2);
	return res;
}
void update(Node *&root,int l,int r,ll add){
	Node *l1,*r1,*l2,*r2,*aux;
	split(root,l1,r1,l-1);
	split(r1,r1,r2,r-l+1);
	r1->lazy+=add;
	merge(l1,l1,r1);merge(root,l1,r2);
}
// debugging
ostream &operator<<(ostream &os, Node *n) {
	if (!n) return os;
	os << n->l;
	os << n->val;
	os << n->r;
	return os;
}
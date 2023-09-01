struct node{
  map<char,int>edges;
  int link,length,terminal=0;
  node(int link,int length): link(link),length(length){};
};vector<node>sa; 
// init in main with sa.push_back(node(-1,0));
int last=0;
// add one by one chars in order
void addChar(char s, int pos){
    sa.push_back(node(0,pos+1));
    int r=sa.size()-1;
    int p=last;
    while(p >= 0 && sa[p].edges.find(s) == sa[p].edges.end()) {
      sa[p].edges[s] = r;
      p = sa[p].link;
    }
    if(p != -1) {
      int q = sa[p].edges[s];
      if(sa[p].length + 1 == sa[q].length) {
        sa[r].link = q;
      } else {
        sa.push_back(node(sa[q].link,sa[p].length+1));
        sa[sa.size()-1].edges=sa[q].edges;
        int qq = sa.size()-1;
        sa[q].link = qq;
        sa[r].link= qq;
        while(p >= 0 && sa[p].edges[s] == q) {
          sa[p].edges[s] = qq;
          p = sa[p].link;
        }
      }
    }
    last = r;
}
// Not necesary functions
void findTerminals(){
    int p = last;
    while(p > 0) {
       sa[p].terminal=1;
       p = sa[p].link;
    }
}

struct twoSat{
    int s;
    vector<vector<int>> g,gr;
    vector<int> visited,ids,topologic_sort,val;
    twoSat(int n){
        s=n;
        g.assign(n*2+1,vector<int>());
        gr.assign(n*2+1,vector<int>());
        visited.assign(n*2+1,0);
        ids.assign(n*2+1,0);
        val.assign(n+1,0);
    }
    void addEdge(int a,int b){
        g[a].push_back(b);
        gr[b].push_back(a);
    }
    void addOr(int a,bool ba,int b,bool bb){
        addEdge(a+(ba?s:0),b+(bb?0:s));
        addEdge(b+(bb?s:0),a+(ba?0:s));
    }
    void addXor(int a,bool ba,int b,bool bb){
        addOr(a,ba,b,bb);
        addOr(a,!ba,b,!bb);
    }
    void addAnd(int a,bool ba,int b,bool bb){
        addXor(a,!ba,b,bb);
    }
    void dfs(int u){
        if(visited[u]!=0) return;
        visited[u]=1;
        for(int node:g[u])dfs(node);
        topologic_sort.push_back(u);
    }
    void dfsr(int u,int id){
        if(visited[u]!=0) return;
        visited[u]=1;
        ids[u]=id;
        for(int node:gr[u])dfsr(node,id);
    }
    bool algo(){
        for(int i=0;i<s*2;i++) if(visited[i]==0) dfs(i);
        fill(visited.begin(),visited.end(),0);
        reverse(topologic_sort.begin(),topologic_sort.end());
        int id=0;
        for(int i=0;i<topologic_sort.size();i++){
            if(visited[topologic_sort[i]]==0)dfsr(topologic_sort[i],id++);
        }
        for(int i=0;i<s;i++){
            if(ids[i]==ids[i+s]) return false;
            val[i]=(ids[i]>ids[i+s]?0:1);
        }
        return true; 
    }
};
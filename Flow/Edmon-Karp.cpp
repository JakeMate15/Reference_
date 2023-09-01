struct Edmons{
    #define ll long long
    int n;
    vector<int>d;
    vector<tuple<int,ll,ll>>edges;
    vector<vector<int>> adj;
    vector<pair<int,int>>cam;
    Edmons(int _n):adj(_n+1),n(_n){}
    ll sentFlow(int s,int t,ll f){
        if(s==t)return f;
        auto &[u,idx]=cam[t];
        auto cap=get<1>(edges[idx]),&flow=get<2>(edges[idx]);
        ll push=sentFlow(s,u,min(cap-flow,f));
        flow+=push;
        auto &flowr=get<2>(edges[idx^1]);
        flowr-=push;
        return push;
    }
    bool bfs(int s,int t){
        d.assign(n+1,-1); d[s]=0;
        cam.assign(n+1,{-1,-1});
        queue<int> q({s});
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto idx:adj[u]){
                auto &v=get<0>(edges[idx]);auto &cap=get<1>(edges[idx]),&flow=get<2>(edges[idx]);
                if(cap-flow>0 && d[v]==-1) d[v]=d[u]+1,cam[v]={u,idx},q.push(v);
            }
        }
        return d[t]!=-1;    
    }
    ll maxFlow(int s,int t){
        ll flow=0;
        while(bfs(s,t)){
            ll push=sentFlow(s,t,1e18);
            if(!push) return flow;
            flow+=push;
        }
        return flow;
    }
    void addEdge(int u,int v, ll c, bool dire=true){
        if(u==v) return;
        edges.emplace_back(v,c,0);
        adj[u].push_back(edges.size()-1);
        edges.emplace_back(u,(dire?0:c),0);
        adj[v].push_back(edges.size()-1);
    }
};
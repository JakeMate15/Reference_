    // Get path of max flow
    void dfs_max_flow(int u, int v) {
        each(i, g[u]) {
            if (i.f > 0 && i.f < 1e9 && i.f < i.cap && i.to != v) {
                res[u][i.to % n] = i.f;
                i.f = 0;
                dfs_max_flow(i.to, u);
            }
        }
    }
    // Convert a 2D matrix as a bipartite graph with 2 nodes (in/out)
    void matrix_to_bipartite_graph(int n, int m) {
        int s, t, dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        Dinic nf(2 * n * m+2);
        rep(i,0,n) {
            rep(j,0,m) {
                char c = matrix[i][j];
                int u = 2 * (n * j + i), cap = 1e9;
                if(c == '#') continue;
                else if(c == '.') cap = 1;
                else if(c == 'A') s = u;
                else if(c == 'B') t = u;
                nf.add_edge(u, u+1, cap);
                rep(k,0,4) {
                    int x = i+dx[k], y = j+dy[k], v = 2*(n*y+x);
                    if(x<0 || x>=n || y<0 || y>=m) continue;
                    nf.add_edge(u+1, v, cap);
                }
            }
        }
        ll mx=nf.max_flow(s,t+1);
    }
    // Get min cut
    void dfs_min_cut(int u){ // Mark saturated nodes from source
        vis[u] = 1;
        each(i, g[u]) 
            if(!vis[i.to] && i.f < i.cap) 
                dfs_min_cut(i.to);
    }
    void print_min_cut(int s) { 
        dfs_min_cut(s);
        rep(i,0,n) {      // Check for not saturated nodes from 
            rep(j,0,m) {  // saturated nodes and mark them as part 
                int u = 2 * (n * j + i);         // of the answer.
                if(nf.vis[u]) {  
                    each(v, nf.g[u]){
                        if(!nf.vis[v.to] && v.cap > 0)
                            res[i][j] = v.to;
                    }
                }
            }
        }
    }
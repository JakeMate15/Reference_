vector<path> dijkstra(int start){
    priority_queue<edge, vector<edge>, greater<edge>> cola;
    vector<path> paths(V);
    cola.emplace(start, 0);
    paths[start].cost = 0;
    while(!cola.empty()){
        int u = cola.top().dest; cola.pop();
        for(edge & current : adjList[u]){
            int v = current.dest;
            int nuevo = paths[u].cost + current.cost;
            if(nuevo == paths[v].cost && paths[u].size + 1 < paths[v].size){
                paths[v].prev = u;
                paths[v].size = paths[u].size + 1;
            }else if(nuevo < paths[v].cost){
                paths[v].prev = u;
                paths[v].size = paths[u].size + 1;
                cola.emplace(v, nuevo);
                paths[v].cost = nuevo;
            }
        }
    }
    buildPaths(paths); // !# - Copy function from above
    return paths;
}
pair<vb, vector<edge>> articulationBridges(){
	vi low(V), label(V);
	vb points(V);
	vector<edge> bridges;
	int time = 0;
	function<int(int, int)> dfs = [&](int u, int p){
		label[u] = low[u] = ++time;
		int hijos = 0, ret = 0;
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(v == p && !ret++) continue;
			if(!label[v]){
				++hijos;
				dfs(v, u);
				if(label[u] <= low[v])
					points[u] = true;
				if(label[u] < low[v])
					bridges.push_back(current);
				low[u] = min(low[u], low[v]);
			}
			low[u] = min(low[u], label[v]);
		}
		return hijos;
	};
	for(int u = 0; u < V; ++u)
		if(!label[u])
			points[u] = dfs(u, -1) > 1;
	return make_pair(points, bridges);
}
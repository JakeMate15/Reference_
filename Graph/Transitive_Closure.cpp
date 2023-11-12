vector<vb> transitiveClosure(){
	vector<vb> tmp = adjMatrix;
	for(int k = 0; k < V; ++k)
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < V; ++j)
				tmp[i][j] = tmp[i][j] || (tmp[i][k] && tmp[k][j]);
	return tmp;
}

vector<vb> transitiveClosureDFS(){
	vector<vb> tmp(V, vb(V));
	function<void(int, int)> dfs = [&](int start, int u){
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(!tmp[start][v]){
				tmp[start][v] = true;
				dfs(start, v);
			}
		}
	};
	for(int u = 0; u < V; u++)
		dfs(u, u);
	return tmp;
}
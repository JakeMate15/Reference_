bool hasCycle(){
	vi color(V);
	function<bool(int, int)> dfs = [&](int u, int parent){
		color[u] = 1;
		bool ans = false;
		int ret = 0;
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(color[v] == 0)
				ans |= dfs(v, u);
			else if(color[v] == 1 && (dir || v != parent || ret++))
				ans = true;
		}
		color[u] = 2;
		return ans;
	};
	for(int u = 0; u < V; ++u)
		if(color[u] == 0 && dfs(u, -1))
			return true;
	return false;
}
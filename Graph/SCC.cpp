vector<vi> scc(){
	vi low(V), label(V);
	int time = 0;
	vector<vi> ans;
	stack<int> S;
	function<void(int)> dfs = [&](int u){
		label[u] = low[u] = ++time;
		S.push(u);
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(!label[v]) dfs(v);
			low[u] = min(low[u], low[v]);
		}
		if(label[u] == low[u]){
			vi comp;
			while(S.top() != u){
				comp.push_back(S.top());
				low[S.top()] = V + 1;
				S.pop();
			}
			comp.push_back(S.top());
			S.pop();
			ans.push_back(comp);
			low[u] = V + 1;
		}
	};
	for(int u = 0; u < V; ++u)
		if(!label[u]) dfs(u);
	return ans;
}
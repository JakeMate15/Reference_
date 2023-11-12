vector<path> bellmanFord(int start){
	vector<path> paths(V, path());
	vi processed(V);
	vb inQueue(V);
	queue<int> Q;
	paths[start].cost = 0;
	Q.push(start);
	while(!Q.empty()){
		int u = Q.front(); Q.pop(); inQueue[u] = false;
		if(paths[u].cost == inf) continue;
		++processed[u];
		if(processed[u] == V){
			cout << "Negative cycle\n";
			return {};
		}
		for(edge & current : adjList[u]){
			int v = current.dest;
			int nuevo = paths[u].cost + current.cost;
			if(nuevo == paths[v].cost && paths[u].size + 1 < paths[v].size){
				paths[v].prev = u;
				paths[v].size = paths[u].size + 1;
			}else if(nuevo < paths[v].cost){
				if(!inQueue[v]){
					Q.push(v);
					inQueue[v] = true;
				}
				paths[v].prev = u;
				paths[v].size = paths[u].size + 1;
				paths[v].cost = nuevo;
			}
		}
	}
	buildPaths(paths); // !# - Copy function from above
	return paths;
}
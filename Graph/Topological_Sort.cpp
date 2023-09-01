vi topologicalSort(){
	int visited = 0;
	vi order, indegree(V);
	for(auto & node : adjList){
		for(edge & current : node){
			int v = current.dest;
			++indegree[v];
		}
	}
	queue<int> Q;
	for(int i = 0; i < V; ++i){
		if(indegree[i] == 0) Q.push(i);
	}
	while(!Q.empty()){
		int source = Q.front();
		Q.pop();
		order.push_back(source);
		++visited;
		for(edge & current : adjList[source]){
			int v = current.dest;
			--indegree[v];
			if(indegree[v] == 0) Q.push(v);
		}
	}
	if(visited == V) return order;
	else return {};
}
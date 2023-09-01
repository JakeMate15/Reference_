bool isBipartite(){
	vi side(V, -1);
	queue<int> q;
	for (int st = 0; st < V; ++st){
		if(side[st] != -1) continue;
		q.push(st);
		side[st] = 0;
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for (edge & current : adjList[u]){
				int v = current.dest;
				if(side[v] == -1) {
					side[v] = side[u] ^ 1;
					q.push(v);
				}else{
					if(side[v] == side[u]) return false;
				}
			}
		}
	}
	return true;
}
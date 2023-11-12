vector<edge> kruskal(){
	sort(edges.begin(), edges.end());
	vector<edge> MST;
	disjointSet DS(V);
	for(int u = 0; u < V; ++u)
		DS.makeSet(u);
	int i = 0;
	while(i < edges.size() && MST.size() < V - 1){
		edge current = edges[i++];
		int u = current.source, v = current.dest;
		if(DS.findSet(u) != DS.findSet(v)){
			MST.push_back(current);
			DS.unionSet(u, v);
		}
	}
	return MST;
}
struct edge{
	int source, dest, cost;
	edge(): source(0), dest(0), cost(0){}
	edge(int dest, int cost): dest(dest), cost(cost){}
	edge(int source, int dest, int cost): source(source), dest(dest), cost(cost){}
	bool operator==(const edge & b) const{
		return source == b.source && dest == b.dest && cost == b.cost;
	}
	bool operator<(const edge & b) const{
		return cost < b.cost;
	}
	bool operator>(const edge & b) const{
		return cost > b.cost;
	}
};

struct path{
	int cost = inf;
	deque<int> vertices;
	int size = 1;
	int prev = -1;
};

struct graph{
	vector<vector<edge>> adjList;
	vector<vb> adjMatrix;
	vector<vi> costMatrix;
	vector<edge> edges;
	int V = 0;
	bool dir = false;
	graph(int n, bool dir): V(n), dir(dir), adjList(n), edges(n), adjMatrix(n, vb(n)), costMatrix(n, vi(n)){
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				costMatrix[i][j] = (i == j ? 0 : inf);
	}
	void add(int source, int dest, int cost){
		adjList[source].emplace_back(source, dest, cost);
		edges.emplace_back(source, dest, cost);
		adjMatrix[source][dest] = true;
		costMatrix[source][dest] = cost;
		if(!dir){
			adjList[dest].emplace_back(dest, source, cost);
			adjMatrix[dest][source] = true;
			costMatrix[dest][source] = cost;
		}
	}
	void buildPaths(vector<path> & paths){
		for(int i = 0; i < V; i++){
			int u = i;
			for(int j = 0; j < paths[i].size; j++){
				paths[i].vertices.push_front(u);
				u = paths[u].prev;
			}
		}
	}
};
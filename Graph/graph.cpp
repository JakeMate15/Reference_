struct disjointSet{
	int N;
	vector<short int> rank;
	vi parent, count;

	disjointSet(int N): N(N), parent(N), count(N), rank(N){}

	void makeSet(int v){
		count[v] = 1;
		parent[v] = v;
	}

	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}

	void unionSet(int a, int b){
		a = findSet(a), b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
			count[b] += count[a];
		}else{
			parent[b] = a;
			count[a] += count[b];
			if(rank[a] == rank[b]) ++rank[a];
		}
	}
};

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
		buildPaths(paths);
		return paths;
	}

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
		buildPaths(paths);
		return paths;
	}





	vector<vi> floyd(){
		vector<vi> tmp = costMatrix;
		for(int k = 0; k < V; ++k)
			for(int i = 0; i < V; ++i)
				for(int j = 0; j < V; ++j)
					if(tmp[i][k] != inf && tmp[k][j] != inf)
						tmp[i][j] = min(tmp[i][j], tmp[i][k] + tmp[k][j]);
		return tmp;
	}

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

	bool tryKuhn(int u, vb & used, vi & left, vi & right){
		if(used[u]) return false;
		used[u] = true;
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(right[v] == -1 || tryKuhn(right[v], used, left, right)){
				right[v] = u;
				left[u] = v;
				return true;
			}
		}
		return false;
	}

	bool augmentingPath(int u, vb & used, vi & left, vi & right){
		used[u] = true;
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(right[v] == -1){
				right[v] = u;
				left[u] = v;
				return true;
			}
		}
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(!used[right[v]] && augmentingPath(right[v], used, left, right)){
				right[v] = u;
				left[u] = v;
				return true;
			}
		}
		return false;
	}

	//vertices from the left side numbered from 0 to l-1
	//vertices from the right side numbered from 0 to r-1
	//graph[u] represents the left side
	//graph[u][v] represents the right side
	//we can use tryKuhn() or augmentingPath()
	vector<pair<int, int>> maxMatching(int l, int r){
		vi left(l, -1), right(r, -1);
		vb used(l);
		for(int u = 0; u < l; ++u){
			tryKuhn(u, used, left, right);
			fill(used.begin(), used.end(), false);
		}
		vector<pair<int, int>> ans;
		for(int u = 0; u < r; ++u){
			if(right[u] != -1){
				ans.emplace_back(right[u], u);
			}
		}
		return ans;
	}

	void dfs(int u, vi & status, vi & parent){
		status[u] = 1;
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(status[v] == 0){ //not visited
				parent[v] = u;
				dfs(v, status, parent);
			}else if(status[v] == 1){ //explored
				if(v == parent[u]){
					//bidirectional node u<-->v
				}else{
					//back edge u-v
				}
			}else if(status[v] == 2){ //visited
				//forward edge u-v
			}
		}
		status[u] = 2;
	}
};

struct tree{
	vi parent, level, weight;
	vector<vi> dists, DP;
	int n, root;

	void dfs(int u, graph & G){
		for(edge & curr : G.adjList[u]){
			int v = curr.dest;
			int w = curr.cost;
			if(v != parent[u]){
				parent[v] = u;
				weight[v] = w;
				level[v] = level[u] + 1;
				dfs(v, G);
			}
		}
	}

	tree(int n, int root): n(n), root(root), parent(n), level(n), weight(n), dists(n, vi(20)), DP(n, vi(20)){
		parent[root] = root;
	}

	tree(graph & G, int root): n(G.V), root(root), parent(G.V), level(G.V), weight(G.V), dists(G.V, vi(20)), DP(G.V, vi(20)){
		parent[root] = root;
		dfs(root, G);
	}

	void pre(){
		for(int u = 0; u < n; u++){
			DP[u][0] = parent[u];
			dists[u][0] = weight[u];
		}
		for(int i = 1; (1 << i) <= n; ++i){
			for(int u = 0; u < n; ++u){
				DP[u][i] = DP[DP[u][i - 1]][i - 1];
				dists[u][i] = dists[u][i - 1] + dists[DP[u][i - 1]][i - 1];
			}
		}
	}

	int ancestor(int p, int k){
		int h = level[p] - k;
		if(h < 0) return -1;
		int lg;
		for(lg = 1; (1 << lg) <= level[p]; ++lg);
		lg--;
		for(int i = lg; i >= 0; --i){
			if(level[p] - (1 << i) >= h){
				p = DP[p][i];
			}
		}
		return p;
	}

	int lca(int p, int q){
		if(level[p] < level[q]) swap(p, q);
		int lg;
		for(lg = 1; (1 << lg) <= level[p]; ++lg);
		lg--;
		for(int i = lg; i >= 0; --i){
			if(level[p] - (1 << i) >= level[q]){
				p = DP[p][i];
			}
		}
		if(p == q) return p;
	 
		for(int i = lg; i >= 0; --i){
			if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
				p = DP[p][i];
				q = DP[q][i];
			}
		}
		return parent[p];
	}

	int dist(int p, int q){
		if(level[p] < level[q]) swap(p, q);
		int lg;
		for(lg = 1; (1 << lg) <= level[p]; ++lg);
		lg--;
		int sum = 0;
		for(int i = lg; i >= 0; --i){
			if(level[p] - (1 << i) >= level[q]){
				sum += dists[p][i];
				p = DP[p][i];
			}
		}
		if(p == q) return sum;
	 
		for(int i = lg; i >= 0; --i){
			if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
				sum += dists[p][i] + dists[q][i];
				p = DP[p][i];
				q = DP[q][i];
			}
		}
		sum += dists[p][0] + dists[q][0];
		return sum;
	}
};

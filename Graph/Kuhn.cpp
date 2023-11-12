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

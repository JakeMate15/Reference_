ld perimeter(vector<point> & P){
	int n = P.size();
	ld ans = 0;
	for(int i = 0; i < n; i++){
		ans += (P[i] - P[(i + 1) % n]).length();
	}
	return ans;
}

ld area(vector<point> & P){
	int n = P.size();
	ld ans = 0;
	for(int i = 0; i < n; i++){
		ans += P[i].cross(P[(i + 1) % n]);
	}
	return abs(ans / 2);
}

vector<point> convexHull(vector<point> P){
	sort(P.begin(), P.end());
	vector<point> L, U;
	for(int i = 0; i < P.size(); i++){
		while(L.size() >= 2 && leq((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)){
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i = P.size() - 1; i >= 0; i--){
		while(U.size() >= 2 && leq((U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]), 0)){
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	U.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	return L;
}

bool pointInPerimeter(const vector<point> & P, const point & p){
	int n = P.size();
	for(int i = 0; i < n; i++){
		if(pointInSegment(P[i], P[(i + 1) % n], p)){
			return true;
		}
	}
	return false;
}

bool crossesRay(const point & a, const point & b, const point & p){
	return (geq(b.y, p.y) - geq(a.y, p.y)) * sgn((a - p).cross(b - p)) > 0;
}

int pointInPolygon(const vector<point> & P, const point & p){
	if(pointInPerimeter(P, p)){
		return -1; //point in the perimeter
	}
	int n = P.size();
	int rays = 0;
	for(int i = 0; i < n; i++){
		rays += crossesRay(P[i], P[(i + 1) % n], p);
	}
	return rays & 1; //0: point outside, 1: point inside
}

//point in convex polygon in O(log n)
//make sure that P is convex and in ccw
//before the queries, do the preprocess on P:
// rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
// int right = max_element(P.begin(), P.end()) - P.begin();
//returns 0 if p is outside, 1 if p is inside, -1 if p is in the perimeter
int pointInConvexPolygon(const vector<point> & P, const point & p, int right){
	if(p < P[0] || P[right] < p) return 0;
	int orientation = sgn((P[right] - P[0]).cross(p - P[0]));
	if(orientation == 0){
		if(p == P[0] || p == P[right]) return -1;
		return (right == 1 || right + 1 == P.size()) ? -1 : 1;
	}else if(orientation < 0){
		auto r = lower_bound(P.begin() + 1, P.begin() + right, p);
		int det = sgn((p - r[-1]).cross(r[0] - r[-1])) - 1;
		if(det == -2) det = 1;
		return det;
	}else{
		auto l = upper_bound(P.rbegin(), P.rend() - right - 1, p);
		int det = sgn((p - l[0]).cross((l == P.rbegin() ? P[0] : l[-1]) - l[0])) - 1;
		if(det == -2) det = 1;
		return det;
	}
}

vector<point> cutPolygon(const vector<point> & P, const point & a, const point & v){
	//returns the part of the convex polygon P on the left side of line a+tv
	int n = P.size();
	vector<point> lhs;
	for(int i = 0; i < n; ++i){
		if(geq(v.cross(P[i] - a), 0)){
			lhs.push_back(P[i]);
		}
		if(intersectLineSegmentInfo(a, v, P[i], P[(i+1)%n]) == 1){
			point p = intersectLines(a, v, P[i], P[(i+1)%n] - P[i]);
			if(p != P[i] && p != P[(i+1)%n]){
				lhs.push_back(p);
			}
		}
	}
	return lhs;
}
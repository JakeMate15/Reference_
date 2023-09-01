ld distancePointCircle(const point & c, ld r, const point & p){
	//point p, circle with center c and radius r
	return max((ld)0, (p - c).length() - r);
}

point projectionPointCircle(const point & c, ld r, const point & p){
	//point p (outside the circle), circle with center c and radius r
	return c + (p - c).unit() * r;
}

pair<point, point> pointsOfTangency(const point & c, ld r, const point & p){
	//point p (outside the circle), circle with center c and radius r
	point v = (p - c).unit() * r;
	ld d2 = (p - c).norm(), d = sqrt(d2);
	point v1 = v * (r / d), v2 = v.perp() * (sqrt(d2 - r*r) / d);
	return {c + v1 - v2, c + v1 + v2};
}

vector<point> intersectLineCircle(const point & a, const point & v, const point & c, ld r){
	//line a+tv, circle with center c and radius r
	ld h2 = r*r - v.cross(c - a) * v.cross(c - a) / v.norm();
	point p = a + v * v.dot(c - a) / v.norm();
	if(eq(h2, 0)) return {p}; //line tangent to circle
	else if(le(h2, 0)) return {}; //no intersection
	else{
		point u = v.unit() * sqrt(h2);
		return {p - u, p + u}; //two points of intersection (chord)
	}
}

vector<point> intersectSegmentCircle(const point & a, const point & b, const point & c, ld r){
	//segment ab, circle with center c and radius r
	vector<point> P = intersectLineCircle(a, b - a, c, r), ans;
	for(const point & p : P){
		if(pointInSegment(a, b, p)) ans.push_back(p);
	}
	return ans;
}

pair<point, ld> getCircle(const point & m, const point & n, const point & p){
	//find circle that passes through points p, q, r
	point c = intersectLines((n + m) / 2, (n - m).perp(), (p + n) / 2, (p - n).perp());
	ld r = (c - m).length();
	return {c, r};
}

vector<point> intersectionCircles(const point & c1, ld r1, const point & c2, ld r2){
	//circle 1 with center c1 and radius r1
	//circle 2 with center c2 and radius r2
	point d = c2 - c1;
	ld d2 = d.norm();
	if(eq(d2, 0)) return {}; //concentric circles
	ld pd = (d2 + r1*r1 - r2*r2) / 2;
	ld h2 = r1*r1 - pd*pd/d2;
	point p = c1 + d*pd/d2;
	if(eq(h2, 0)) return {p}; //circles touch at one point
	else if(le(h2, 0)) return {}; //circles don't intersect
	else{
		point u = d.perp() * sqrt(h2/d2);
		return {p - u, p + u};
	}
}

int circleInsideCircle(const point & c1, ld r1, const point & c2, ld r2){
	//test if circle 2 is inside circle 1
	//returns "-1" if 2 touches internally 1, "1" if 2 is inside 1, "0" if they overlap
	ld l = r1 - r2 - (c1 - c2).length();
	return (ge(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}

int circleOutsideCircle(const point & c1, ld r1, const point & c2, ld r2){
	//test if circle 2 is outside circle 1
	//returns "-1" if they touch externally, "1" if 2 is outside 1, "0" if they overlap
	ld l = (c1 - c2).length() - (r1 + r2);
	return (ge(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}

int pointInCircle(const point & c, ld r, const point & p){
	//test if point p is inside the circle with center c and radius r
	//returns "0" if it's outside, "-1" if it's in the perimeter, "1" if it's inside
	ld l = (p - c).length() - r;
	return (le(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}

vector<vector<point>> tangents(const point & c1, ld r1, const point & c2, ld r2, bool inner){
	//returns a vector of segments or a single point
	if(inner) r2 = -r2;
	point d = c2 - c1;
	ld dr = r1 - r2, d2 = d.norm(), h2 = d2 - dr*dr;
	if(eq(d2, 0) || le(h2, 0)) return {};
	point v = d*dr/d2;
	if(eq(h2, 0)) return {{c1 + v*r1}};
	else{
		point u = d.perp()*sqrt(h2)/d2;
		return {{c1 + (v - u)*r1, c2 + (v - u)*r2}, {c1 + (v + u)*r1, c2 + (v + u)*r2}};
	}
}

ld signed_angle(const point & a, const point & b){
	return sgn(a.cross(b)) * acosl(a.dot(b) / (a.length() * b.length()));
}

ld intersectPolygonCircle(const vector<point> & P, const point & c, ld r){
	//Gets the area of the intersection of the polygon with the circle
	int n = P.size();
	ld ans = 0;
	for(int i = 0; i < n; ++i){
		point p = P[i], q = P[(i+1)%n];
		bool p_inside = (pointInCircle(c, r, p) != 0);
		bool q_inside = (pointInCircle(c, r, q) != 0);
		if(p_inside && q_inside){
			ans += (p - c).cross(q - c);
		}else if(p_inside && !q_inside){
			point s1 = intersectSegmentCircle(p, q, c, r)[0];
			point s2 = intersectSegmentCircle(c, q, c, r)[0];
			ans += (p - c).cross(s1 - c) + r*r * signed_angle(s1 - c, s2 - c);
		}else if(!p_inside && q_inside){
			point s1 = intersectSegmentCircle(c, p, c, r)[0];
			point s2 = intersectSegmentCircle(p, q, c, r)[0];
			ans += (s2 - c).cross(q - c) + r*r * signed_angle(s1 - c, s2 - c);
		}else{
			auto info = intersectSegmentCircle(p, q, c, r);
			if(info.size() <= 1){
				ans += r*r * signed_angle(p - c, q - c);
			}else{
				point s2 = info[0], s3 = info[1];
				point s1 = intersectSegmentCircle(c, p, c, r)[0];
				point s4 = intersectSegmentCircle(c, q, c, r)[0];
				ans += (s2 - c).cross(s3 - c) + r*r * (signed_angle(s1 - c, s2 - c) + signed_angle(s3 - c, s4 - c));
			}
		}
	}
	return abs(ans)/2;
}
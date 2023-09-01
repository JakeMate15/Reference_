using ld = long double;
const ld eps = 1e-9, inf = numeric_limits<ld>::max(), pi = acos(-1);
// For use with integers, just set eps=0 and everything remains the same
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct point{
	ld x, y;
	point(): x(0), y(0){}
	point(ld x, ld y): x(x), y(y){}

	point operator+(const point & p) const{return point(x + p.x, y + p.y);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}

	point operator+=(const point & p){*this = *this + p; return *this;}
	point operator-=(const point & p){*this = *this - p; return *this;}
	point operator*=(const ld & p){*this = *this * p; return *this;}
	point operator/=(const ld & p){*this = *this / p; return *this;}

	point rotate(const ld & a) const{return point(x*cos(a) - y*sin(a), x*sin(a) + y*cos(a));}
	point perp() const{return point(-y, x);}
	ld ang() const{
		ld a = atan2l(y, x); a += le(a, 0) ? 2*pi : 0; return a;
	}
	ld dot(const point & p) const{return x * p.x + y * p.y;}
	ld cross(const point & p) const{return x * p.y - y * p.x;}
	ld norm() const{return x * x + y * y;}
	ld length() const{return sqrtl(x * x + y * y);}
	point unit() const{return (*this) / length();}

	bool operator==(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool operator>(const point & p) const{return ge(x, p.x) || (eq(x, p.x) && ge(y, p.y));}
	bool half(const point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point & p){return os << "(" << p.x << ", " << p.y << ")";}

int sgn(ld x){
	if(ge(x, 0)) return 1;
	if(le(x, 0)) return -1;
	return 0;
}

void polarSort(vector<point> & P, const point & o, const point & v){
	//sort points in P around o, taking the direction of v as first angle
	sort(P.begin(), P.end(), [&](const point & a, const point & b){
		return point((a - o).half(v), 0) < point((b - o).half(v), (a - o).cross(b - o));
	});
}

bool pointInLine(const point & a, const point & v, const point & p){
	//line a+tv, point p
	return eq((p - a).cross(v), 0);
}

bool pointInSegment(const point & a, const point & b, const point & p){
	//segment ab, point p
	return pointInLine(a, b - a, p) && leq((a - p).dot(b - p), 0);
}

int intersectLinesInfo(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1 and a2+tv2
	ld det = v1.cross(v2);
	if(eq(det, 0)){
		if(eq((a2 - a1).cross(v1), 0)){
			return -1; //infinity points
		}else{
			return 0; //no points
		}
	}else{
		return 1; //single point
	}
}

point intersectLines(const point & a1, const point & v1, const point & a2, const point & v2){
	//lines a1+tv1, a2+tv2
	//assuming that they intersect
	ld det = v1.cross(v2);
	return a1 + v1 * ((a2 - a1).cross(v2) / det);
}

int intersectLineSegmentInfo(const point & a, const point & v, const point & c, const point & d){
	//line a+tv, segment cd
	point v2 = d - c;
	ld det = v.cross(v2);
	if(eq(det, 0)){
		if(eq((c - a).cross(v), 0)){
			return -1; //infinity points
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v.cross(c - a)) != sgn(v.cross(d - a)); //1: single point, 0: no point
	}
}

int intersectSegmentsInfo(const point & a, const point & b, const point & c, const point & d){
	//segment ab, segment cd
	point v1 = b - a, v2 = d - c;
	int t = sgn(v1.cross(c - a)), u = sgn(v1.cross(d - a));
	if(t == u){
		if(t == 0){
			if(pointInSegment(a, b, c) || pointInSegment(a, b, d) || pointInSegment(c, d, a) || pointInSegment(c, d, b)){
				return -1; //infinity points
			}else{
				return 0; //no point
			}
		}else{
			return 0; //no point
		}
	}else{
		return sgn(v2.cross(a - c)) != sgn(v2.cross(b - c)); //1: single point, 0: no point
	}
}

ld distancePointLine(const point & a, const point & v, const point & p){
	//line: a + tv, point p
	return abs(v.cross(p - a)) / v.length();
}
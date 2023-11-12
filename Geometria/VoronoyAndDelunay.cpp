/* 
   Functions required
   getCircle,IntesecLine,sgn
   ConvexHull Lineal and Noraml
*/
//
const point inf_pt(inf, inf);
struct QuadEdge{
	point origin;
	QuadEdge* rot = nullptr;
	QuadEdge* onext = nullptr;
	bool used = false;
	QuadEdge* rev() const{return rot->rot;}
	QuadEdge* lnext() const{return rot->rev()->onext->rot;}
	QuadEdge* oprev() const{return rot->onext->rot;}
	point dest() const{return rev()->origin;}
};
 
QuadEdge* make_edge(const point & from, const point & to){
	QuadEdge* e1 = new QuadEdge;
	QuadEdge* e2 = new QuadEdge;
	QuadEdge* e3 = new QuadEdge;
	QuadEdge* e4 = new QuadEdge;
	e1->origin = from;
	e2->origin = to;
	e3->origin = e4->origin = inf_pt;
	e1->rot = e3;
	e2->rot = e4;
	e3->rot = e2;
	e4->rot = e1;
	e1->onext = e1;
	e2->onext = e2;
	e3->onext = e4;
	e4->onext = e3;
	return e1;
}
 
void splice(QuadEdge* a, QuadEdge* b){
	swap(a->onext->rot->onext, b->onext->rot->onext);
	swap(a->onext, b->onext);
}
 
void delete_edge(QuadEdge* e){
	splice(e, e->oprev());
	splice(e->rev(), e->rev()->oprev());
	delete e->rev()->rot;
	delete e->rev();
	delete e->rot;
	delete e;
}
 
QuadEdge* connect(QuadEdge* a, QuadEdge* b){
	QuadEdge* e = make_edge(a->dest(), b->origin);
	splice(e, a->lnext());
	splice(e->rev(), b);
	return e;
}
 
bool left_of(const point & p, QuadEdge* e){
	return ge((e->origin - p).cross(e->dest() - p), 0);
}
 
bool right_of(const point & p, QuadEdge* e){
	return le((e->origin - p).cross(e->dest() - p), 0);
}
 
__int128_t det3(__int128_t a1, __int128_t a2, __int128_t a3, __int128_t b1, __int128_t b2, __int128_t b3, __int128_t c1, __int128_t c2, __int128_t c3) {
	return a1 * (b2 * c3 - c2 * b3) - a2 * (b1 * c3 - c1 * b3) + a3 * (b1 * c2 - c1 * b2);
}
 
bool in_circle(const point & a, const point & b, const point & c, const point & d) {
	__int128_t det = -det3(b.x, b.y, b.norm(), c.x, c.y, c.norm(), d.x, d.y, d.norm());
	det += det3(a.x, a.y, a.norm(), c.x, c.y, c.norm(), d.x, d.y, d.norm());
	det -= det3(a.x, a.y, a.norm(), b.x, b.y, b.norm(), d.x, d.y, d.norm());
	det += det3(a.x, a.y, a.norm(), b.x, b.y, b.norm(), c.x, c.y, c.norm());
	return det > 0;
}
 
pair<QuadEdge*, QuadEdge*> build_tr(int l, int r, vector<point> & P){
	if(r - l + 1 == 2){
		QuadEdge* res = make_edge(P[l], P[r]);
		return make_pair(res, res->rev());
	}
	if(r - l + 1 == 3){
		QuadEdge *a = make_edge(P[l], P[l + 1]), *b = make_edge(P[l + 1], P[r]);
		splice(a->rev(), b);
		int sg = sgn((P[l + 1] - P[l]).cross(P[r] - P[l]));
		if(sg == 0)
			return make_pair(a, b->rev());
		QuadEdge* c = connect(b, a);
		if(sg == 1)
			return make_pair(a, b->rev());
		else
			return make_pair(c->rev(), c);
	}
	int mid = (l + r) / 2;
	QuadEdge *ldo, *ldi, *rdo, *rdi;
	tie(ldo, ldi) = build_tr(l, mid, P);
	tie(rdi, rdo) = build_tr(mid + 1, r, P);
	while(true){
		if(left_of(rdi->origin, ldi)){
			ldi = ldi->lnext();
			continue;
		}
		if(right_of(ldi->origin, rdi)){
			rdi = rdi->rev()->onext;
			continue;
		}
		break;
	}
	QuadEdge* basel = connect(rdi->rev(), ldi);
	auto valid = [&basel](QuadEdge* e){return right_of(e->dest(), basel);};
	if(ldi->origin == ldo->origin)
		ldo = basel->rev();
	if(rdi->origin == rdo->origin)
		rdo = basel;
	while(true){
		QuadEdge* lcand = basel->rev()->onext;
		if(valid(lcand)){
			while(in_circle(basel->dest(), basel->origin, lcand->dest(), lcand->onext->dest())){
				QuadEdge* t = lcand->onext;
				delete_edge(lcand);
				lcand = t;
			}
		}
		QuadEdge* rcand = basel->oprev();
		if(valid(rcand)){
			while(in_circle(basel->dest(), basel->origin, rcand->dest(), rcand->oprev()->dest())){
				QuadEdge* t = rcand->oprev();
				delete_edge(rcand);
				rcand = t;
			}
		}
		if(!valid(lcand) && !valid(rcand))
			break;
		if(!valid(lcand) || (valid(rcand) && in_circle(lcand->dest(), lcand->origin, rcand->origin, rcand->dest())))
			basel = connect(rcand, basel->rev());
		else
			basel = connect(basel->rev(), lcand->rev());
	}
	return make_pair(ldo, rdo);
}
 
vector<vector<point>> delaunay(vector<point> P){
	sort(P.begin(), P.end());
	auto res = build_tr(0, (int)P.size() - 1, P);
	QuadEdge* e = res.first;
	vector<QuadEdge*> edges = {e};
	while(le((e->dest() - e->onext->dest()).cross(e->origin - e->onext->dest()), 0))
		e = e->onext;
	auto add = [&P, &e, &edges](){
		QuadEdge* curr = e;
		do{
			curr->used = true;
			P.push_back(curr->origin);
			edges.push_back(curr->rev());
			curr = curr->lnext();
		}while(curr != e);
	};
	add();
	P.clear();
	int kek = 0;
	while(kek < (int)edges.size())
		if(!(e = edges[kek++])->used)
			add();
	vector<vector<point>> ans;
	for(int i = 0; i < (int)P.size(); i += 3){
		ans.push_back({P[i], P[i + 1], P[i + 2]});
	}
	return ans;
}
vector<vector<point>> voronoi (vector<point> P) {
	vector<vector<point>> cells(P.size());
	point border[4];
	ld minSizeBorder[4];
	minSizeBorder[0]=minSizeBorder[1]=minSizeBorder[2]=minSizeBorder[3]=1e15;
	rep(i, 0,P.size()) P[i].idx = i;
	auto ch = convexHull(P);
	if (ch.size() > 2) {
		auto dt = delaunay(P);
		for (auto &tri : dt) {
			point c = getCircle(tri[0], tri[1], tri[2]);
			for (auto &p : tri) cells[p.idx].pb(c);
		}
		ch = convexHullWithColinear(P);
		rep (i, 0,ch.size()) {
			point a = ch[i];point b = ch[(i + 1)% ch.size()];
			point mid = (a + b)/2;
			point c = (mid+(a - mid).perp()*inf_coord);
			cells[a.idx].pb(c);
			cells[b.idx].pb(c);
		}
	} else if (ch.size() == 2) {
		sort(all(P));
		rep (i, 0,(int)P.size() - 1) {
			point mid = (P[i + 1] + P[i]) / 2;
			point a =(mid+ (P[i] - mid).perp()*inf_coord);
			point b =(mid+ (P[i] - mid).perp()*-inf_coord);
			rep(j, 0,2) {
				cells[P[i + j].idx].pb(a);
				cells[P[i + j].idx].pb(b);
			}
		}
	} else {
		cells[0] = {
			rec[0],rec[1],rec[2],rec[3]
		};
	}	
	for (auto &cell : cells) {
		cell = convexHull(cell);
	}	
	return cells;
}
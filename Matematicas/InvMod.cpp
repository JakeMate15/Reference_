tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

lli modularInverse(lli a, lli m){
	auto[d, x, y] = extendedGcd(a, m);
	if(d != 1) return -1; // inverse doesn't exist
	if(x < 0) x += m;
	return x;
}
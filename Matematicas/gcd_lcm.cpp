ll gcd(ll a, ll b){
	ll r;
	while(b != 0) r = a % b, a = b, b = r;
	return a;
}

ll lcm(ll a, ll b){
	return b * (a / gcd(a, b));
}

ll gcd(const vector<ll>& nums){
	ll ans = 0;
	for(ll num : nums) ans = gcd(ans, num);
	return ans;
}

ll lcm(const vector<ll>& nums){
	ll ans = 1;
	for(ll num : nums) ans = lcm(ans, num);
	return ans;
}
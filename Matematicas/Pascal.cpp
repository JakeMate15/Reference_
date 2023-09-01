vector<vector<lli>> ncrSieve(int n){
	vector<vector<lli>> Ncr(n+1);
	Ncr[0] = {1};
	for(int i = 1; i <= n; ++i){
		Ncr[i].resize(i + 1);
		Ncr[i][0] = Ncr[i][i] = 1;
		for(int j = 1; j <= i / 2; j++)
			Ncr[i][i - j] = Ncr[i][j] = Ncr[i - 1][j - 1] + Ncr[i - 1][j];
	}
	return Ncr;
}
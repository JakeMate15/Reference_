struct Hash{
  const int mod=1e9+123;
  const int p=257;
  vector<int> prefix;
  static vector<int>pow;
  Hash(string str){
    int n=str.size();
    while(pow.size()<=n){
      pow.push_back(1LL*pow.back()*p%mod);
    }
    vector<int> aux(n+1);
    prefix=aux;
    for(int i=0;i<n;i++){
      prefix[i+1]=(prefix[i]+1LL*str[i]*pow[i])%mod;
    }
  }
  inline int getHashInInerval(int i,int len,int MxPow){
    int hashing=prefix[i+len]-prefix[i];
    if(hashing<0) hashing+=mod;
    hashing=1LL*hashing*pow[MxPow-(len+i-1)]%mod;
    return hashing;
  }
};
vector<int> Hash::pow{1};
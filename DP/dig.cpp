res = solve(b) - solve(a-1);
vector<int>num;
int dp[20][20][2];

int solve(lli b){
    num.clear();
    while(b>0){
        num.push_back(b%10);
        b/=10;
    }
    reverse(num.begin(), num.end());
 
    memset(dp, -1, sizeof(dp));
    lli res = mem(0, 0, 0);
    return res;
}

//Numeros con a los mas 3 digitos distintos de cero
//4, 200000, 10203
int mem(int pos, int cant, int goodAll){
    if(cant>3)  return 0;
    if(pos==num.size()){
        if(cant<=3) return 1;
        return 0;
    }
 
    int &a = dp[pos][cant][goodAll];
    if(a!=-1)   return a;
    a = 0;
 
    int limite = goodAll==0?num[pos]:9;
    fore(dig,0,limite){
        int nG = goodAll;
        int nCant = cant;
        if(goodAll==0 && dig<limite)    nG=1;
        if(dig!=0)  nCant++;
        if(nCant<=3)    a+=mem(pos+1,nCant,nG);
    } 
 
    return a;
}

//Numeros donde el digito d ocurre exactamente k veces
int call(int pos, int cnt, int f){
    if(cnt > k) return 0;

    if(pos == num.size()){
        if(cnt == k)    return 1;
        return 0;
    }

    if(DP[pos][cnt][f] != -1)   return DP[pos][cnt][f];
    int res = 0;

    int LMT;

    if(f == 0)  LMT = num[pos];
    else        LMT = 9;

    for(int dgt = 0; dgt<=LMT; dgt++){
        int nf = f;
        int ncnt = cnt;
        if(f == 0 && dgt < LMT) nf = 1;
        if(dgt == d)    ncnt++;   
        if(ncnt <= k)   res += call(pos+1, ncnt, nf);
    }

    DP[pos][cnt][f] = res;
    return DP[pos][cnt][f];
}
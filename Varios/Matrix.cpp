const int N=100, MOD=1e9+7;
struct Matrix {
	ll a[N][N];
	Matrix() {memset(a,0,sizeof(a));}
	Matrix operator *(Matrix other) {  // Product of a matrix
		Matrix product=Matrix();
        rep(i,0,N) rep(j,0,N) rep(k,0,N) {
            product.a[i][k]+=a[i][j]*other.a[j][k];
            product.a[i][k]%=MOD;
        }
		return product;
	}
};
Matrix expo_power(Matrix a, ll n) {  // Matrix exponentiation
	Matrix res=Matrix();
    rep(i,0,N) res.a[i][i]=1;  // Matriz identidad
	while(n){  
        if(n&1) res=res*a;
        n>>=1;
        a=a*a;
	}
	return res;
} // Ej. Matrix M=Matrix();  M.a[0][0]=1;  M=M*M;   Matrix res=expo_power(M,k);
//Para procesar querys de tipo k-esimo es necesario crear un arbol binario perfector(llenar con 0's)
template<typename T>
struct SegmentTree{
	int N;
	vector<T> ST;
 
	//Creacion a partir de un arreglo O(n)
	SegmentTree(int N, vector<T> & arr): N(N){
		ST.resize(N << 1);
		for(int i = 0; i < N; ++i)
			ST[N + i] = arr[i];     //Dato normal
			ST[N + i] = creaNodo(); //Dato compuesto
		for(int i = N - 1; i > 0; --i)
			ST[i] = ST[i << 1] + ST[i << 1 | 1];        //Dato normal
			ST[i] = merge(ST[i << 1] , ST[i << 1 | 1]); //Dato compuesto
	}
 
	//Actualizacion de un elemento en la posicion i
	void update(int i, T value){
		ST[i += N] = value;     //Dato normal
		ST[i += N] = creaNodo();//Dato compuesto
		while(i >>= 1)
			ST[i] = ST[i << 1] + ST[i << 1 | 1];        //Dato normal  
			ST[i] = merge(ST[i << 1] , ST[i << 1 | 1]); //Dato compuesto
	}
 
	//query en [l, r]
	T query(int l, int r){
		T res = 0;  //Dato normal
		nodo resl = creaNodo(), resr = creaNodo();//Dato compuesto
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1)       res += ST[l++]; //Dato normal
			if(!(r & 1))    res += ST[r--]; //Dato normal

			if(l & 1)       resl = merge(resl,ST[l++]); //Dato compuesto
			if(!(r & 1))    resr = merge(ST[r--],resr); //Dato compuesto
		}
		return res;                 //Dato normal
		return merge(resl,resr);    //Dato compuesto
	}

	//Para estas querys es necesario que el st tenga el tam de la siguiente potencia de 2
	//ll nT = 1;
	// while(nT<n) nT<<=1;
	//vector<int> a(nT,0);	

	//Encontrar k-esimo 1 en un st de 1's
	int Kth_One(int k) {
		int i = 0, s = N >> 1;
		for(int p = 2; p < 2 * N; p <<= 1, s >>= 1) {
			if(k < ST[p])	continue;
			k -= ST[p++];	i += s;
		}
		return i;
	}

	//i del primer elemento >= k en todo el arr
	int atLeastX(int k){
		int i = 0, s = N >> 1;
		for(int p = 2; p < 2 * N; p <<= 1, s >>= 1) {
			if(ST[p] < k)	p++, i += s;
		}
		if(ST[N + i] < k)	i = -1;
		return i;
	}

	//i del primer elemento >= k en [l,fin]
	//Uso atLeastX(k,l,1,nT)
	int atLeastX(int x, int l, int p, int s) {
		if(ST[p] < x or s <= l)	return -1;
		if((p << 1) >= 2 * N)
			return (ST[p] >= x) - 1;
		int i = atLeastX(x, l, p << 1, s >> 1);
		if(i != -1)	return i;
		i = atLeastX(x, l - (s >> 1), p << 1 | 1, s >> 1);
		if(i == -1)	return -1;
		return (s >> 1) + i;
	}
};
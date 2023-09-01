//Lazy propagation con incremento de u en rango y minimo
//Hay varias modificaciones necesarias para suma en ambos
template<typename T>
struct SegmentTreeLazy{
	int N,h;
	vector<T> ST, d;
 
	//Creacion a partir de un arreglo
	SegmentTreeLazy(int n, vector<T> &a): N(n){
		//En caso de inicializar en cero o algo similar, revisar que la construccion tenga su respectivo neutro mult y 1       
		ST.resize(N << 1);
		d.resize(N);
		h = 64 - __builtin_clzll(n);
 
		for(int i = 0; i < N; ++i)
			ST[N + i] = a[i];
		//Construir el st sobre la query que se necesita
		for(int i = N - 1; i > 0; --i)
			ST[i] = min(ST[i << 1] , ST[i << 1 | 1]);
	}

	//Modificar de acuerdo al tipo modificacion requerida, +,*,|,^,etc
	void apply(int p, T value) {
		ST[p] += value;
		if(p<N)	d[p]+= value;
	}
 
	// Modifica valores de los padres de p
	//Modificar de acuerdo al tipo modificacion requerida, +,*,|,^,etc y a la respectiva query
	void build(int p){
		while(p>1){
			p >>= 1;
			ST[p] = min(ST[p << 1], ST[p << 1 | 1]) + d[p];
			//ST[p] = (ST[p << 1] & ST[p << 1 | 1]) | d[p]; Ejemplos con bitwise
		}
	}
 
	// Propagacion desde la raiz a p
	void push(int p){
		for (int s = h; s > 0; --s) {
			int i = p >> s;
			if (d[i] != 0) {
				apply(i << 1, d[i]);
				apply(i << 1 | 1, d[i]);
				d[i] = 0;   //Tener cuidado si estoy haciendo multiplicaciones
			}
		}
	}
 
	// Sumar v a cada elemento en el intervalo [l, r)
	void increment(int l, int r, T value) {	
		l += N, r += N;
		int l0 = l, r0 = r;
		for (; l < r; l >>= 1, r >>= 1) {
			if(l & 1) apply(l++, value);
			if(r & 1) apply(--r, value);
		}
		build(l0);
		build(r0 - 1);
	}
 
	// min en el intervalo [l, r)
	T range_min(int l, int r) { 	
		l += N, r += N;
		push(l);
		push(r - 1);
		T res = LLONG_MAX;
		//T res = (1 << 30) - 1;    Requerir operacion and
		for (; l < r; l >>= 1, r >>= 1) {
			if(l & 1)	res = min(res, ST[l++]);
			//if(res >= mod) res -= mod;
			if(r & 1)	res = min(res, ST[--r]);
			//if(res >= mod) res -= mod;
		}
		return res;
	}
    
};
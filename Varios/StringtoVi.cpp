//Convertir una cadena de numeros separados por " " en vector de enteros
//Leer varias de esas querys
cin.ignore();
while(q--){
	string s;
	getline(cin, s);
	vector<int> qr;
	stringstream ss(s);
	int num;
	while (ss >> num)   qr.push_back(num);
}
string decimalToBaseB(lli n, lli b){
	string ans = "";
	lli d;
	do{
		d = n % b;
		if(0 <= d && d <= 9) ans = (char)(48 + d) + ans;
		else if(10 <= d && d <= 35) ans = (char)(55 + d) + ans;
		n /= b;
	}while(n != 0);
	return ans;
}

lli baseBtoDecimal(const string & n, lli b){
	lli ans = 0;
	for(const char & d : n){
		if(48 <= d && d <= 57) ans = ans * b + (d - 48);
		else if(65 <= d && d <= 90) ans = ans * b + (d - 55);
		else if(97 <= d && d <= 122) ans = ans * b + (d - 87);
	}
	return ans;
}
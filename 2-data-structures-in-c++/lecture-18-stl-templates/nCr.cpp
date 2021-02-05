ll ncr(ll n, ll r){
	ll C=1;
	for(ll i=1;i<=r;i++){
		C*=(n-r+i);
		C/=i;
	}
	return C;
}
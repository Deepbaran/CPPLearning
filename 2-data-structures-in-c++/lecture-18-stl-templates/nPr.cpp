ll npr(ll n, ll r) 
{ 
    ll P = 1; 
  
    // Compute n*(n-1)*(n-2)....(n-k+1) 
    for (ll i = 0; i < r; i++) 
        P *= (n-i) ; 
  
    return P; 
} 
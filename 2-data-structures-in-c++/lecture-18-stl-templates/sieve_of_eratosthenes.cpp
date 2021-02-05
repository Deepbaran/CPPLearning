void sieveOfEratosthenes(int* sieve, int n){
    for(int i=0;i<=n;i++)
            sieve[i]=1; // Initially assume all are Prime
    for(int i=2;i<=n;i++){
        if(!sieve[i]) continue; // Ignore if not a prime
        for(int j=2*i;j<=n;j+=i)
            sieve[j]=0; // Not a Prime
    }
}
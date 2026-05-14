#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    int max = 2*n;
    vector <bool> prime(max+1, true);
    /*
    Sieve Array Precomputation
    Sieve takes O(M log log M) where M = 2*n.
    The nested loop takes O(N * (Primes <= N)). Total Time is roughly O(N^2 / log N), which is blindingly fast for N=1000.
    */
    prime[0] = prime[1] = false;
    for (int i = 2; i*i <=max; i++){
        if (prime[i]){
            for (int j = i*i; j <= max; j+=i){
                prime[j] = false;
            }
        }
    }
    /*
    Avoid Counting double pairs : set p <= i
    if prime[p] && prime[target-p] then ++g(n) translate to ++ f(n) so we increment only 1 variable ++ans
    */
    int ans = 0;
    for (int i = 2; i <= n;i++){
        int target = 2*i; 
        for (int p = 2; p <= i; p++){
            if (prime[p] && prime[target-p]){
                ++ans;
            }
        }
    }
    cout << ans << '\n';
    
}
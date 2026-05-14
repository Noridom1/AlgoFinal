#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int LOG = 20;

int st[MAXN][LOG];
int lg[MAXN];

int query(int L, int R){
    int j = lg[R-L+1];
    return gcd(st[L][j], st[R - (1<<j) +1][j]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> arr;
    for (int i = 0;i < n;i++){
        int a; cin >> a;
        arr.push_back(a);
        st[i][0] = a;
    }
    lg[1] = 0;
    for (int i = 2; i <= n; i++){
        lg[i] = lg[i/2] + 1;
    }
    //Construct the Sparse Table
    /*
    Build Sparse Table

    Transition: st[i][j] = gcd starting from index i of interval length 2^j

    Split interval into two halves:
    each half has length 2^(j-1)
    
    Therefore: st[i][j] = gcd(
        st[i][j-1],
        st[i + 2^(j-1)][j-1]
    )
    */
    for (int j = 1; j <= lg[n] ; j++){
        for (int i = 0; i + (1 << j) <= n;i++){
            st[i][j] = gcd(
                st[i][j-1],
                st[i+(1 << (j-1))][j-1]
            );
        }
    }
    /*
    Iterate through all windows of size k
    Each query is O(1) after sparse table preprocessing
    */
    int ans = 0;
    for (int i = 0;i+k-1 < n;i++){
        ans = max(ans, query(i, i+k-1));
    }
    cout << ans << '\n';
}
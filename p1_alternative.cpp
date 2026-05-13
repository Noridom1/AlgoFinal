#include <bits/stdc++.h>
using namespace std;

struct StackGCD {
    stack<pair<int,int>> st;
    
    void push(int x) {
        if (st.empty())
            st.push({x, x});
        else
            st.push({x, gcd(x, st.top().second)});
    }

    void pop() {
        st.pop();
    }

    bool empty() {
        return st.empty();
    }

    int top() {
        return st.top().first;
    }

    int get_gcd() {
        if (st.empty()) return 0;
        return st.top().second;
    }
};

struct QueueGCD {
    StackGCD s1, s2;

    void push(int x) {
        s1.push(x);
    }

    void transfer() {
        while (!s1.empty()) {
            int val = s1.top();
            s1.pop();

            if (s2.empty())
                s2.push(val);
            else
                s2.push({val, gcd(val, s2.get_gcd())});
        }
    }

    void pop() {
        if (s2.empty())
            transfer();
        s2.pop();
    }

    int get_gcd() {
        return gcd(s1.get_gcd(), s2.get_gcd());
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    QueueGCD q;

    int ans = 0;

    for (int i = 0; i < n; i++) {
        q.push(a[i]);

        if (i >= k)
            q.pop();

        if (i >= k - 1)
            ans = max(ans, q.get_gcd());
    }

    cout << ans << '\n';

    return 0;
}
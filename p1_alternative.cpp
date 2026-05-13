#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Custom fast GCD function
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// A custom Stack that maintains the running GCD of its elements
struct GCDStack {
    // pair stores: {value, running_gcd_up_to_this_element}
    vector<pair<int, int>> s;

    void push(int val) {
        int current_gcd = s.empty() ? val : gcd(val, s.back().second);
        s.push_back({val, current_gcd});
    }

    int pop() {
        int val = s.back().first;
        s.pop_back();
        return val;
    }

    bool empty() const {
        return s.empty();
    }

    int get_gcd() const {
        return s.empty() ? 0 : s.back().second;
    }
};

// A Queue built from Two GCD Stacks
struct GCDQueue {
    GCDStack s1; // Used for adding elements
    GCDStack s2; // Used for removing elements

    void push(int val) {
        s1.push(val);
    }

    void pop() {
        // If s2 is empty, pour everything from s1 into s2
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.pop());
            }
        }
        // Remove the oldest element
        s2.pop();
    }

    int get_current_window_gcd() const {
        if (s1.empty()) return s2.get_gcd();
        if (s2.empty()) return s1.get_gcd();
        return gcd(s1.get_gcd(), s2.get_gcd());
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    GCDQueue window;
    int max_window_gcd = 0;

    for (int i = 0; i < n; ++i) {
        // 1. Add the new element to the window
        window.push(a[i]);

        // 2. If the window is too large, remove the oldest element
        if (i >= k) {
            window.pop();
        }

        // 3. If the window has exactly 'k' elements, check the GCD
        if (i >= k - 1) {
            int current_gcd = window.get_current_window_gcd();
            max_window_gcd = max(max_window_gcd, current_gcd);
        }
    }

    cout << max_window_gcd << "\n";

    return 0;
}
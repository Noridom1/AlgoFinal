#include <bits/stdc++.h>
using namespace std;


struct Point {
    long long x, y;
};

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}

int main() {
    int n;
    cin >> n;

    vector<Point> p(n);

    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    // total doubled area of the polygon:
    //   2S = sum(x_{i} * y_{i+1} - y_{i} * x_{i+1})
    // i and j are 2 consecutive vertices
    long long total = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        total += p[i].x * p[j].y - p[i].y * p[j].x;
    }
    

    total = abs(total);

    int best_i = 0, best_j = 2;
    long long best_diff = total;

    int j = 1;
    long long cur = 0;

    for (int i = 0; i < n; i++) {

        while (true) {
            int nj = (j + 1) % n; // candidate diagonal's endpoint

            // cannot use edges
            if (nj == i || (i + 1) % n == nj)
                break;

            long long add = abs(cross(p[i], p[j], p[nj]));

            long long new_cur = cur + add;

            // Difference between 2 parts: ∣2A − S∣
            // We move j only if the split becomes more balanced.
            // abs(total - 2 * new_cur)
            if (abs(total - 2 * new_cur) < abs(total - 2 * cur)) {
                cur = new_cur;
                j = nj;
            } else {
                break;
            }
        }

        // check if i and j are not adjacent vertices
        if (j != i && (i + 1) % n != j && (j + 1) % n != i) {
            long long diff = abs(total - 2 * cur);
            
            // update the best diff
            if (diff < best_diff) {
                best_diff = diff;
                best_i = i;
                best_j = j;
            }
        }

        // remove triangle when moving i forward
        int ni = (i + 1) % n;

        if (ni != j) {
            cur -= abs(cross(p[i], p[ni], p[j]));
        }
    }

    cout << best_i << " " << best_j << '\n';

    return 0;
}
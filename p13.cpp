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

    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    int need = (n - 2) / 2;

    for (int i = 0; i < n; ++i) {

        // all other points
        vector<int> ord;

        for (int j = 0; j < n; ++j) {
            if (i != j) ord.push_back(j);
        }

        // sort by polar angle around point i
        sort(ord.begin(), ord.end(),
            [&](int a, int b) {

                double A = atan2(
                    p[a].y - p[i].y,
                    p[a].x - p[i].x
                );

                double B = atan2(
                    p[b].y - p[i].y,
                    p[b].x - p[i].x
                );

                return A < B;
            });

        int m = ord.size();

        // duplicate array for circular sweep
        vector<int> ext = ord;
        for (int x : ord) ext.push_back(x);

        int r = 0;

        for (int l = 0; l < m; ++l) {

            if (r < l + 1)
                r = l + 1;

            // expand while angle < 180 degrees
            while (r < l + m &&
                   cross(p[i], p[ext[l]], p[ext[r]]) > 0) {
                r++;
            }

            int leftSide = r - l - 1;

            if (leftSide == need) {
                cout << i + 1 << " "
                     << ext[l] + 1 << '\n';
                return 0;
            }
        }
    }

    return 0;
}
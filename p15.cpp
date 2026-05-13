#include <bits/stdc++.h>
using namespace std;

int main() {
    double x1, y1, x2, y2, R;
    cin >> x1 >> y1 >> x2 >> y2 >> R;

    const double PI = acos(-1.0);

    double dx = x1 - x2;
    double dy = y1 - y2;

    double d = sqrt(dx * dx + dy * dy);

    double area;

    // Same circle
    if (d == 0.0) {
        area = PI * R * R;
    }
    // No overlap
    else if (d >= 2.0 * R) {
        area = 2.0 * PI * R * R;
    }
    // Partial overlap
    else {
        double inter =
            2.0 * R * R * acos(d / (2.0 * R))
            - 0.5 * d * sqrt(4.0 * R * R - d * d);

        area = 2.0 * PI * R * R - inter;
    }

    cout << fixed << setprecision(3) << area << '\n';

    return 0;
}
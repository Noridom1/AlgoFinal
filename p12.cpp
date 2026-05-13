#include <bits/stdc++.h>
using namespace std;

bool isSquare(int x) {
    int root = sqrt(x);
    return root * root == x;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i <= n / 2; ++i) {
        if (isSquare(i) && isSquare(n - i)) {
            cout << i << " " << n - i << endl;
            int dx = sqrt(i);
            int dy = sqrt(n - i);
            int x = 0, y = 0;
            for (int i = 0; i < 4; ++i) {
                cout << x << " " << y << endl;
                x += dx;
                y += dy;
                int tmp = dx;
                dx = -dy;
                dy = tmp;
            }
        }

    }
}
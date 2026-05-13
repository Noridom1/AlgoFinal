#include <bits/stdc++.h>
using namespace std;

struct Point
{
    long long x;
    long long y;
};

int main()
{
    int n;
    if (!(cin >> n))
        return 0;
    vector<Point> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;
    int need = (n - 2) / 2;
    for (int i = 0; i < n; i++)
    {
        vector<pair<double, int>> ang(n - 1);
        for (int j = 0; j < n; j++)
            if (j != i)
            {
                double a = atan2((double)(p[j].y - p[i].y), (double)(p[j].x - p[i].x));
                ang.emplace_back(a, j);
            }
        sort(ang.begin(), ang.end());
        int m = ang.size();
        ang.resize(2 * m);
        for (int t = 0; t < m; t++)
            ang[m + t] = {ang[t].first + 2 * M_PI, ang[t].second};
        int k = 0;
        for (int j = 0; j < m; j++)
        {
            if (k < j + 1)
                k = j + 1;
            while (k < j + m && ang[k].first < ang[j].first + M_PI)
                k++;
            int left = k - j - 1;
            if (left == need)
            {
                cout << (i + 1) << ' ' << (ang[j].second + 1) << '\n';
                return 0;
            }
        }
    }
    return 0;
}
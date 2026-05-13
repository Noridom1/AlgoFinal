#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

// This function checks if we can reach height H within our budget T
bool check(long long H, int n, long long T, const vector<long long> &a)
{
    for (int i = 0; i < n; i++)
    {
        long long current_cost = 0;
        bool possible_at_this_spot = true;

        for (int j = 0; j < n; j++)
        {
            // The "tent" rule: The height at position j must be
            // at most (H + distance from the peak i)
            long long max_allowed = H + abs(i - j);

            if (a[j] > max_allowed)
            {
                current_cost += (a[j] - max_allowed);
            }

            // Optimization: If cost already exceeds budget, stop looking here
            if (current_cost > T)
            {
                possible_at_this_spot = false;
                break;
            }
        }

        if (possible_at_this_spot)
            return true;
    }
    return false;
}

int main()
{
    int n;
    long long T;
    if (!(cin >> n >> T))
        return 0;

    vector<long long> a(n);
    long long low = -2e9, high = 2e9; // Large range for the height search

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] < high)
            high = a[i]; // Start 'high' at the smallest current value
    }

    low = high - T; // The lowest possible height we could ever need
    long long answer = high;

    // Binary Search to find the minimum height
    while (low <= high)
    {
        long long mid = low + (high - low) / 2;
        if (check(mid, n, T, a))
        {
            answer = mid;
            high = mid - 1; // Try to go even lower
        }
        else
        {
            low = mid + 1; // Not enough budget, must go higher
        }
    }

    cout << answer << endl;
    return 0;
}









/*
Overall:
O(n² log A)
Space Complexity:
O(n)
Stores the input array only.
*/
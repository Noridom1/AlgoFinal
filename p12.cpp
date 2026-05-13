#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int S;
    if (!(cin >> S)) return 0;

    // Search for integers a and b such that a^2 + b^2 = S
    for (int a = 0; a * a <= S; ++a) {
        int b2 = S - (a * a);
        int b = round(sqrt(b2));

        if (b * b == b2) {
            // We found a side vector (a, b). 
            // Now construct the 4 vertices of the square.
            // Let vertex 1 be (0, 0)
            // Vertex 2 is (0 + a, 0 + b)
            // To get vertex 3, rotate vector (a, b) by 90 degrees to get (-b, a)
            // and add it to vertex 2.
            
            int x1 = 0, y1 = 0;
            int x2 = a, y2 = b;
            int x3 = a - b, y3 = b + a;
            int x4 = -b, y4 = a;

            cout << x1 << " " << y1 << endl;
            cout << x2 << " " << y2 << endl;
            cout << x3 << " " << y3 << endl;
            cout << x4 << " " << y4 << endl;
            return 0; // Found a solution, exit program
        }
    }

    // If the loop finishes without returning, no solution exists
    cout << "Impossible" << endl;
    return 0;
}
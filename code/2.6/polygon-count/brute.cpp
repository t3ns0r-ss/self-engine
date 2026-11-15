#include <bits/stdc++.h>
using namespace std;

// Brute force: test every lattice point of the bounding box. A point is on the boundary when it is on an edge (dot and cross
// products), and inside when the angles seen from it add up to a full turn. Then twice the area is 2 I + B - 2 (Pick).
int main() {
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    long long lox = *min_element(x.begin(), x.end()), hix = *max_element(x.begin(), x.end());
    long long loy = *min_element(y.begin(), y.end()), hiy = *max_element(y.begin(), y.end());
    long long boundary = 0, inside = 0;
    for (long long qx = lox; qx <= hix; qx++)
        for (long long qy = loy; qy <= hiy; qy++) {
            bool on = false;
            double total = 0;
            for (int i = 0; i < n && !on; i++) {
                int j = (i + 1) % n;
                long long cr = (x[i] - qx) * (y[j] - qy) - (y[i] - qy) * (x[j] - qx);
                long long dot = (x[i] - qx) * (x[j] - qx) + (y[i] - qy) * (y[j] - qy);
                if (cr == 0 && dot <= 0) on = true;
                total += atan2((double)cr, (double)dot);
            }
            if (on) boundary++;
            else if (fabs(total) > M_PI) inside++;
        }
    cout << 2 * inside + boundary - 2 << " " << boundary << " " << inside << "\n";
}

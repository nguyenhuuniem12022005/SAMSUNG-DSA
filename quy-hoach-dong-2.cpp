#include <bits/stdc++.h>
#define endl "\n"
#define int long long

using namespace std;

int a, b, c, d, e;
int sum[6005][6005]; 

bool is_valid(int m) {
    for(int i = 1; i <= a - m + 1; i++) {
        for(int j = 1; j <= b - m + 1; j++) {
            if (sum[i + m - 1][j + m - 1] - sum[i + m - 1][j - 1] - sum[i - 1][j + m - 1] + sum[i - 1][j - 1] <= e) 
                return true;
        }
    }
    return false;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> a >> b >> c >> d >> e;
    for(int i = 1; i <= c; i++) {
        int x, y; cin >> x >> y;
        sum[x][y] = 1;
    }

    for(int i = 1; i <= a; i++) {
        for(int j = 1; j <= b; j++) {
            sum[i][j] = sum[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }
    }

    int l = 0, r = min(a, b) / d;
    int res = 0;

    while(l <= r) {
        int m = (l + r) / 2;

        if (is_valid(m * d)) {
            res = m * d;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    cout << res << endl;
    return 0;
}
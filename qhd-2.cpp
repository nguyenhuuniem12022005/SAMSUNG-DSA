#include <iostream>
#include <vector>
#include <algorithm>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;
int m, n, e, d,k;
vector<vector<int>> preSum;

bool check(int side) {
    for (int i = 1; i <= m - side + 1; ++i) {
        for (int j = 1; j <= n - side + 1; ++j) {
            int r2 = i + side - 1;
            int c2 = j + side - 1;
            int count = preSum[r2][c2] - preSum[i - 1][c2] - preSum[r2][j - 1] + preSum[i - 1][j - 1];
            if (count <= k) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> m >> n >> e >> d >> k;

    preSum.assign(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> board(m + 1,vector<int>(n + 1, 0));

    for (int i = 0; i < e; ++i) {
        int r, c;
        cin >> r >> c;
        board[r][c] = 1;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            preSum[i][j] = board[i][j] + preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1];
        }
    }

    int low = 0;
    int high = min(m, n) / d;
    int ans_k = 0;

    while (low <= high) {
        int mid_k = low + (high - low) / 2;
        int curr = mid_k * d;
        
        if (check(curr)) {
            ans_k = mid_k;
            low = mid_k + 1;
        } else {
            high = mid_k - 1;
        }
    }

    cout << ans_k * d << endl;

    return 0;
}
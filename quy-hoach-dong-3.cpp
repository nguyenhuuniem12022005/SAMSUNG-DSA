#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    // Bước 1: Sắp xếp
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    // Khởi tạo DP table
    // dp[i][j][t]
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, 0)));

    // Bước 2: Quy hoạch động
    // Khởi tạo
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j][0] = 1;
        }
    }

    // Lặp để tính các trạng thái
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int t = 1; t <= k; ++t) {
                // Trường hợp 1: Không tạo cặp đấu (a[i-1], b[j-1])
                // Sử dụng index i-1 và j-1 vì mảng a, b là 0-based
                dp[i][j][t] = (dp[i - 1][j][t] + dp[i][j - 1][t]) % MOD;
                dp[i][j][t] = (dp[i][j][t] - dp[i - 1][j - 1][t] + MOD) % MOD;

                // Trường hợp 2: Tạo cặp đấu (a[i-1], b[j-1])
                if (a[i - 1] > b[j - 1]) {
                    dp[i][j][t] = (dp[i][j][t] + dp[i - 1][j - 1][t - 1]) % MOD;
                }
            }
        }
    }

    // Bước 3: In kết quả
    cout << dp[n][m][k] << endl;

    return 0;
}
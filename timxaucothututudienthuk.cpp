#include <iostream>
#include <vector>
#include <string>

long long C[61][61];
void combinations() {
    for (int i = 0; i <= 60; ++i) {
        // C(i, 0) = 1
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            // C(i, j) = C(i-1, j-1) + C(i-1, j)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

void solve() {
    long long a, b, k;
    std::cin >> a >> b >> k;

    std::string result = "";
    while (a > 0 || b > 0) {
        if (a == 0) {
            result += 'b';
            b--;
            continue;
        }

        if (b == 0) {
            result += 'a';
            a--;
            continue;
        }
        long long combinations_with_a = C[a - 1 + b][b];

        if (k <= combinations_with_a) {
            result += 'a';
            a--;
        } else {
            result += 'b';
            b--;
            k -= combinations_with_a;
        }
    }

    std::cout << result << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    combinations();

    solve();

    return 0;
}

#include <iostream>
#include <vector>
#include <unordered_map>

void solve() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int k = 0; k < q; ++k) {
        int l, r;
        std::cin >> l >> r;
 
        l--; 
        r--;

        long long count = 0;

        for (int i = l; i <= r; ++i) {
            std::unordered_map<int, int> freq;
            for (int j = i + 1; j <= r; ++j) {

                int target = -a[i] - a[j];
                if (freq.count(target)) {
                    count += freq[target];
                }
                freq[a[j]]++;
            }
        }
        std::cout << count << "\n";
    }
}

int main() {
    solve();
    return 0;
}

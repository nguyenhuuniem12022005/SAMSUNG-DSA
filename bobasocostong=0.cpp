// Cho N số nguyên A[i] (-10^6 ≤ A[i] ≤ 10^6).

// Có Q truy vấn, mỗi truy vấn gồm 2 số nguyên L và R. Nhiệm vụ của bạn là hãy đếm số bộ 3 chỉ số i, j, k (L ≤ i < j < k ≤ R) sao cho A[i] + A[j] + A[k] = 0.

// Input

// Dòng đầu tiên chứa số nguyên N và Q ( Q ≤ 100 000).
// Dòng thứ hai gồm N số nguyên A[i].
// Q dòng tiếp theo, mỗi dòng gồm 2 số nguyên L, R  mô tả một truy vấn.
// Output

// Với mỗi truy vấn, in ra số bộ ba thỏa mãn yêu cầu của đề bài.
// Giới hạn:

// Subtask 1 (30%): N ≤ 500.

// Subtask 2 (20%): N ≤ 2000.

// Subtask 3 (50%): N ≤ 5000.

// Test ví dụ:

// Input
// 7 3
// 2 0 -1 1 3 -2 3
// 1 6
// 2 4
// 1 7

// output
// 3
// 1
// 4

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

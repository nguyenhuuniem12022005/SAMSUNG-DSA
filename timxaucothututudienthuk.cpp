// Cho 3 số nguyên A, B và K. Trong các xâu có độ dài bằng A + B, gồm A kí tự ‘a’ và B kí tự ‘b’, hãy tìm xâu có thứ tự từ điển bằng K.

// Input

// Dữ liệu đầu vào gồm 3 số nguyên A, B và K (1 ≤ A, B ≤ 30, 1 ≤ K ≤ S với S là số lượng xâu có A kí tự ‘a’ và B kí tự ‘b’, S có giá trị không vượt quá phạm vi số nguyên 64 bit).

// 30% test có giá trị A + B ≤ 20.

// Output

// In ra xâu tìm được

// Test ví dụ:

// Input
// 2 2 4
//output
// baab

//input
// 2 2 6
//output
// bbaa

//input
// 26 26 371326006850843
//output
// babbbbbaaaaabbbaabbabbbbbbaaabaababbaaababbaaabaaaab

// Giải thích test 1 và 2: Thứ tự 6 xâu lần lượt là
// aabb, abab, abba, baab, baba, bbaa.
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

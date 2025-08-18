
// Cho số nguyên dương N, đếm số cách chia các số từ 1 đến 2N thành N nhóm, mỗi nhóm gồm 2 số mà hiệu hai số trong một nhóm bằng hiệu hai số trong nhóm khác.

// IInput:

// Dòng đầu tiên chứa số lượng bộ test T.

// Mỗi test gồm 1 số nguyên dương N.

// Giới hạn:

// Subtask 1 (50%): T, N <= 10000

// Subtask 2 (50%): T <= 10^5, N <= 10^6.

// Output:

// Với mỗi test, hãy in ra đáp án tìm được trên một dòng.

// Example:

// Input

// Output

// 2

// 1

// 2
// out
// 1

// 2

// Giải thích test 2: Có 2 cách chia nhóm là:

// (1, 2) và (3, 4)

// (1, 3) và (2, 4)

#include <iostream>
#include <vector>
#include <ios> 

const int MAX_N = 1000001;
std::vector<int> divisors_count(MAX_N);
void sieve_divisors() {
    for (int i = 1; i < MAX_N; ++i) {
        for (int j = i; j < MAX_N; j += i) {
            divisors_count[j]++;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    sieve_divisors();

    int t;
    std::cin >> t; 

    while (t--) {
        int n;
        std::cin >> n;
        std::cout << divisors_count[n] << "\n";
    }

    return 0;
}
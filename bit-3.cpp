// Cho dãy số A[] có N phần tử. Hãy đếm số bộ ba các số thứ tự ngược, tức là A[i] > A[j] > A[k] với i < j < k.

// Input

// Dòng đầu tiên là số lượng bộ test (<= 20).
// Mỗi test gồm một số nguyên dương N (N <= 10^5)
// Dòng tiếp theo gồm N số nguyên dương A[i] (1 <= A[i] <= N).
// Output

// Với mỗi test, in ra đáp án tìm được trên một dòng.
// Test ví dụ:

// Input



// 2

// 3

// 1 2 3

// 4

// 4 4 2 1
// Output
// 0

// 2

#include <iostream>
#include <vector>
#include <algorithm>

const int MAX = 100005; 
long long bit[MAX];
int N_curr;

void update(int idx, int val) {
    for (; idx < MAX; idx += idx & (-idx)) {
        bit[idx] += val;
    }
}

long long query(int idx) {
    long long sum = 0;
    for (; idx > 0; idx -= idx & (-idx)) {
        sum += bit[idx];
    }
    return sum;
}

void reset_bit() {
    for (int i = 0; i < MAX; ++i) {
        bit[i] = 0;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int num_tests;
    std::cin >> num_tests;

    while (num_tests--) {
        std::cin >> N_curr;
        std::vector<int> A(N_curr);
        std::vector<long long> count_l_r(N_curr);

        for (int i = 0; i < N_curr; ++i) {
            std::cin >> A[i];
        }

        reset_bit();
        for (int j = N_curr - 1; j >= 0; --j) {
            count_l_r[j] = query(A[j] - 1);
            update(A[j], 1);
        }

        long long total = 0;
        reset_bit();
        for (int j = 0; j < N_curr; ++j) {
            long long count_g_l = query(MAX - 1) - query(A[j]);
            
            total += count_g_l * count_l_r[j];
            
            update(A[j], 1);
        }

        std::cout << total << "\n";
    }

    return 0;
}
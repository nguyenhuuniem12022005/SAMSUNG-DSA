// # Cho dãy số A[] có N phần tử. Có Q truy vấn:

// # Loại 1: 1 u K
// # Tăng giá trị phần tử A[u] lên K đơn vị

// # Lọai 2: 2 u v
// # Yêu cầu in ra tổng A[u] + A[u+1] + … + A[v].

// # Input

// # Dòng đầu tiên là số nguyên N (1 <= N <= 100 000).
// # Dòng tiếp theo gồm N số nguyên A[i] (1 <= A[i] <= 10^9).
// # Tiếp theo là số lượng truy vấn Q (1 <= Q <= 100 000).
// # Q dòng tiếp theo, mỗi dòng gồm một loại truy vấn.
// # Giới hạn: 1 <= u <= v <= N, 1 <= K <= 10^9.
// # Output

// # Với mỗi truy vấn, in ra đáp án tìm được trên một dòng.
// # Test ví dụ:

// # Input
// # 5
// # 1 2 3 4 5
// # 3
// # 2 1 5
// # 1 2 5
// # 2 1 5
// # Output
// # 15
// # 20

#include <iostream>
#include <vector>
const int MAXN = 100005;

long long bit[MAXN];
int N_global; 
void update(int idx, long long val) {
    for (; idx <= N_global; idx += idx & (-idx)) {
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

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> N_global; 

    for (int i = 1; i <= N_global; ++i) {
        long long val;
        std::cin >> val;
        update(i, val); 
    }

    int Q; 
    std::cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int u;
            long long K;
            std::cin >> u >> K;
            update(u, K);
        } else {
            int u, v;
            std::cin >> u >> v;
            long long result = query(v) - query(u - 1);
            std::cout << result << "\n"; 
        }
    }

    return 0; 
}
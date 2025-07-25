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
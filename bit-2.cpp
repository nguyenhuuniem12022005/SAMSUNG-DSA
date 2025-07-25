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
    cin >> N_global;

    long long prev_A_val = 0;

    for (int i = 1; i <= N_global; ++i) {
        long long current_A_val;
        cin >> current_A_val;
        update(i, current_A_val - prev_A_val);
        prev_A_val = current_A_val;
    }

    int Q;
    cin >> Q;

    for (int q_idx = 0; q_idx < Q; ++q_idx) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v;
            long long K;
            cin >> u >> v >> K;
            
            update(u, K);
            if (v + 1 <= N_global) {
                update(v + 1, -K);
            }
        } else {
            int u;
            cin >> u;
            long long result = query(u);
            cout << result << "\n";
        }
    }

    return 0;
}
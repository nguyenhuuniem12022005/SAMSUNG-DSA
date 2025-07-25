#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

const int MAX_COMPRESSED_COORD = 200005; 
long long bit[MAX_COMPRESSED_COORD];
int bit_size; 

void update(int idx, int val) {
    for (; idx <= bit_size; idx += idx & (-idx)) {
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

struct Household {
    long long d1_sq;
    long long d2_sq;
};

struct Query {
    long long R1_sq;
    long long R2_sq;
    int original_idx;
};

long long dist_sq(long long x1, long long y1, long long x2, long long y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void solve() {
    int N;
    std::cin >> N;

    std::vector<std::pair<long long, long long>> coords(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> coords[i].first >> coords[i].second;
    }

    long long ax, ay, bx, by;
    int Q;
    std::cin >> ax >> ay >> bx >> by >> Q;

    std::vector<Household> households(N);
    std::vector<long long> all_d2_sq_values; 

    for (int i = 0; i < N; ++i) {
        households[i].d1_sq = dist_sq(coords[i].first, coords[i].second, ax, ay);
        households[i].d2_sq = dist_sq(coords[i].first, coords[i].second, bx, by);
        all_d2_sq_values.push_back(households[i].d2_sq);
    }

    std::sort(all_d2_sq_values.begin(), all_d2_sq_values.end());
    all_d2_sq_values.erase(std::unique(all_d2_sq_values.begin(), all_d2_sq_values.end()), all_d2_sq_values.end());
    bit_size = all_d2_sq_values.size();

    for (int i = 0; i <= bit_size; ++i) {
        bit[i] = 0;
    }

    std::vector<Query> queries(Q);
    for (int i = 0; i < Q; ++i) {
        long long R1, R2;
        std::cin >> R1 >> R2;
        queries[i] = {R1 * R1, R2 * R2, i};
    }

    std::vector<long long> ans(Q);
    std::vector<long long> count_A(Q);
    std::vector<long long> count_B(Q);
    std::vector<long long> count_A_AND_B(Q);

    std::vector<std::pair<long long, int>> households_sorted_by_d1(N);
    std::vector<std::pair<long long, int>> households_sorted_by_d2(N);
    for (int i = 0; i < N; ++i) {
        households_sorted_by_d1[i] = {households[i].d1_sq, i};
        households_sorted_by_d2[i] = {households[i].d2_sq, i};
    }
    std::sort(households_sorted_by_d1.begin(), households_sorted_by_d1.end());
    std::sort(households_sorted_by_d2.begin(), households_sorted_by_d2.end());

    for (int i = 0; i < Q; ++i) {
        count_A[queries[i].original_idx] = std::upper_bound(households_sorted_by_d1.begin(), households_sorted_by_d1.end(), std::make_pair(queries[i].R1_sq, N)) - households_sorted_by_d1.begin();
    }

    for (int i = 0; i < Q; ++i) {
        count_B[queries[i].original_idx] = std::upper_bound(households_sorted_by_d2.begin(), households_sorted_by_d2.end(), std::make_pair(queries[i].R2_sq, N)) - households_sorted_by_d2.begin();
    }

    std::vector<Household> households_for_sweep = households; 
    std::sort(households_for_sweep.begin(), households_for_sweep.end(), [](const Household& a, const Household& b) {
        return a.d1_sq < b.d1_sq;
    });

    std::sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        return a.R1_sq < b.R1_sq;
    });

    int household_ptr = 0;
    for (int i = 0; i < Q; ++i) {
        while (household_ptr < N && households_for_sweep[household_ptr].d1_sq <= queries[i].R1_sq) {
            int compressed_d2_idx = std::upper_bound(all_d2_sq_values.begin(), all_d2_sq_values.end(), households_for_sweep[household_ptr].d2_sq) - all_d2_sq_values.begin();
            update(compressed_d2_idx + 1, 1); 
            household_ptr++;
        }
        int compressed_R2_idx = std::upper_bound(all_d2_sq_values.begin(), all_d2_sq_values.end(), queries[i].R2_sq) - all_d2_sq_values.begin();
        count_A_AND_B[queries[i].original_idx] = query(compressed_R2_idx);
    }

    for (int i = 0; i < Q; ++i) {
        ans[i] = count_A[i] + count_B[i] - count_A_AND_B[i];
        std::cout << ans[i] << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
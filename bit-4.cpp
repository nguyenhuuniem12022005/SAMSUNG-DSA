// Cho ma trận 3D có kích thước N x N x N, ban đầu, tất cả các phần tử có giá trị bằng 0. Có 2 loại truy vấn:

// (1) UPDATE x y z W                 à cập nhật giá trị phần tử A[x][y][z] = W (|W| ≤ 109).

// (2) QUERY x1 y1 z1 x2 y2 z2 à yêu cầu tính tổng các phần tử nằm trong khối hộp từ (x1, y1, z1) tới vị trí (x2, y2, z2).

// Input

// Dòng đầu tiên là số lượng bộ test T (T ≤ 50).
// Mỗi test bắt đầu bởi 2 số nguyên N và M (N ≤ 100, M ≤ 100000).
// M dòng tiếp theo, mỗi dòng gồm một truy vấn.
// Output

// Với mỗi truy vấn loại 2, hãy in ra đáp án tìm được trên một dòng.
// Test ví dụ:

// Input

// Output

// 2

// 4 5

// UPDATE 1 1 1 5

// QUERY 1 1 1 3 3 3

// UPDATE 1 1 1 23

// QUERY 2 2 2 4 4 4

// QUERY 1 1 1 3 3 3

// 2 4

// UPDATE 2 2 1 1

// QUERY 1 1 1 1 1 1

// QUERY 1 1 1 2 2 2

// QUERY 2 2 2 2 2 2

 

// 5

// 0

// 23

// 0

// 1

// 0

 

 

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

const int MAX_DIM = 101; 

long long bit[MAX_DIM][MAX_DIM][MAX_DIM];
long long val_matrix[MAX_DIM][MAX_DIM][MAX_DIM];

int N_current;

void init_data_structures() {
    memset(bit, 0, sizeof(bit));
    memset(val_matrix, 0, sizeof(val_matrix));
}

void update_bit(int x, int y, int z, long long delta) {
    for (int i = x; i <= N_current; i += i & (-i)) {
        for (int j = y; j <= N_current; j += j & (-j)) {
            for (int k = z; k <= N_current; k += k & (-k)) {
                bit[i][j][k] += delta;
            }
        }
    }
}

long long query_prefix_sum(int x, int y, int z) {
    long long sum = 0;
    for (int i = x; i > 0; i -= i & (-i)) {
        for (int j = y; j > 0; j -= j & (-j)) {
            for (int k = z; k > 0; k -= k & (-k)) {
                sum += bit[i][j][k];
            }
        }
    }
    return sum;
}

void solve_test_case() {
    int M;
    std::cin >> N_current >> M;

    init_data_structures();

    for (int q = 0; q < M; ++q) {
        std::string command;
        std::cin >> command;

        if (command == "UPDATE") {
            int x, y, z;
            long long W;
            std::cin >> x >> y >> z >> W;

            long long delta = W - val_matrix[x][y][z];
            
            update_bit(x, y, z, delta);
            
            val_matrix[x][y][z] = W;

        } else if (command == "QUERY") {
            int x1, y1, z1, x2, y2, z2;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

            long long total_sum = 0;
            total_sum += query_prefix_sum(x2, y2, z2);
            total_sum -= query_prefix_sum(x1 - 1, y2, z2);
            total_sum -= query_prefix_sum(x2, y1 - 1, z2);
            total_sum -= query_prefix_sum(x2, y2, z1 - 1);
            total_sum += query_prefix_sum(x1 - 1, y1 - 1, z2);
            total_sum += query_prefix_sum(x1 - 1, y2, z1 - 1);
            total_sum += query_prefix_sum(x2, y1 - 1, z1 - 1);
            total_sum -= query_prefix_sum(x1 - 1, y1 - 1, z1 - 1);

            std::cout << total_sum << "\n";
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;

    while (T--) {
        solve_test_case();
    }

    return 0;
}
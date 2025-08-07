#include <iostream>
#include <vector>

using namespace std;

// Sử dụng kiểu dữ liệu không dấu để tránh tràn số với BASE lớn
using ull = unsigned long long;

// Biến toàn cục để lưu BASE cho các hàm
ull current_base;

// Hàm nhân hai số a và b theo modulo m
// Dùng phương pháp nhân bình phương lặp để tránh tràn số
ull multiply_mod(ull a, ull b) {
    ull res = 0;
    a %= current_base;
    while (b > 0) {
        if (b % 2 == 1) {
            res = (res + a) % current_base;
        }
        a = (a * 2) % current_base;
        b /= 2;
    }
    return res;
}

// Định nghĩa ma trận 2x2
using Matrix = vector<vector<ull>>;

// Hàm nhân hai ma trận 2x2
Matrix multiply_matrix(const Matrix& A, const Matrix& B) {
    Matrix C(2, vector<ull>(2, 0));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                C[i][j] = (C[i][j] + multiply_mod(A[i][k], B[k][j])) % current_base;
            }
        }
    }
    return C;
}

// Hàm tính lũy thừa ma trận bằng phương pháp lũy thừa nhị phân
Matrix matrix_power(Matrix A, ull n) {
    Matrix res = {{1, 0}, {0, 1}}; // Ma trận đơn vị
    while (n > 0) {
        if (n % 2 == 1) {
            res = multiply_matrix(res, A);
        }
        A = multiply_matrix(A, A);
        n /= 2;
    }
    return res;
}

// Hàm giải quyết từng test case
void solve() {
    ull n;
    cin >> n >> current_base;

    if (n == 0 || n == 1) {
        cout << 1 % current_base << endl;
        return;
    }
    
    // Ma trận chuyển đổi
    Matrix T = {{1, 1}, {1, 0}};
    
    // Tính T^(n-1)
    Matrix result_matrix = matrix_power(T, n - 1);
    
    // F_n = (T^(n-1))[0][0] * F_1 + (T^(n-1))[0][1] * F_0
    //     = result_matrix[0][0] * 1 + result_matrix[0][1] * 1
    ull f0 = 1, f1 = 1;
    ull fn = (multiply_mod(result_matrix[0][0], f1) + multiply_mod(result_matrix[0][1], f0)) % current_base;
    
    cout << fn << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
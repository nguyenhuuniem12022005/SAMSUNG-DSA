#include <iostream>
#include <vector>

using namespace std;
using ull = unsigned long long;
ull base;
ull nhan_mod(ull a, ull b) {
    ull res = 0;
    a %= base;
    while (b > 0) {
        if (b % 2 == 1) {
            res = (res + a) % base;
        }
        a = (a * 2) % base;
        b /= 2;
    }
    return res;
}

using Matrix = vector<vector<ull>>;

Matrix nhan_matran(const Matrix& A, const Matrix& B) {
    Matrix C(3, vector<ull>(3, 0));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                C[i][j] = (C[i][j] + nhan_mod(A[i][k], B[k][j])) % base;
            }
        }
    }
    return C;
}


Matrix mu_matran(Matrix A, ull n) {
     Matrix res = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    while (n > 0) {
        if (n % 2 == 1) {
            res = nhan_matran(res, A);
        }
        A = nhan_matran(A, A);
        n /= 2;
    }
    return res;
}


void solve() {
    ull n;
    cin >> n >> base;

    if (n == 1) {
        cout << 1 % base << endl;
        return;
    }
    if (n == 2) {
        cout << 2 % base << endl;
        return;
    }
    if (n == 3) {
        cout << 3 % base << endl;
        return;
    }
    

    Matrix T = {{1, 2, 3}, {1, 0, 0}, {0, 1, 0}};

     Matrix result_matrix = mu_matran(T, n - 3);
    
    // Vector ban đầu: V = {T(3), T(2), T(1)} = {3, 2, 1}
    // T(n) = (T^(n-3) * V)[0]
    ull T3 = 3, T2 = 2, T1 = 1;
    ull T_n = (nhan_mod(result_matrix[0][0], T3) +
               nhan_mod(result_matrix[0][1], T2) +
               nhan_mod(result_matrix[0][2], T1)) % base;
    
    cout << T_n << endl;
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
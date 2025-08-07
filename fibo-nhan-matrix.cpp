#include <iostream>
#include <vector>

using namespace std;

long long MOD = 1e9 + 7;

// Struct đại diện cho ma trận 2x2
struct Matrix {
    long long mat[2][2];

    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
};

// Hàm nhân hai ma trận 2x2
Matrix multiply(Matrix a, Matrix b) {
    Matrix c;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
            }
        }
    }
    return c;
}

// Hàm tính lũy thừa ma trận bằng phương pháp lũy thừa nhị phân
Matrix matrix_power(Matrix a, long long n) {
    Matrix res;
    res.mat[0][0] = res.mat[1][1] = 1; // Ma trận đơn vị

    while (n > 0) {
        if (n % 2 == 1) {
            res = multiply(res, a);
        }
        a = multiply(a, a);
        n /= 2;
    }
    return res;
}

// Hàm giải quyết từng test case
void solve() {
    long long n;
    cin >> n;

    if (n == 0) {
        cout << 0 << endl;
        return;
    }
    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    Matrix T;
    T.mat[0][0] = 1;
    T.mat[0][1] = 1;
    T.mat[1][0] = 1;
    T.mat[1][1] = 0;

    T = matrix_power(T, n - 1);
    
    // F_n = T.mat[0][0] * F_1 + T.mat[0][1] * F_0
    // F_n = T.mat[0][0] * 1 + T.mat[0][1] * 0 = T.mat[0][0]
    cout << T.mat[0][0] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
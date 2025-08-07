#include <iostream>
#include <vector>

using namespace std;

const unsigned long long MOD = 1e15 + 7;
unsigned long long nhan_mod(unsigned long long a, unsigned long long b) {
    unsigned long long res = 0;
    a %= MOD;
    while (b > 0) {
        if (b % 2 == 1) {
            res = (res + a) % MOD;
        }
        a = (a * 2) % MOD;
        b /= 2;
    }
    return res;
}

using Matrix = vector<vector<unsigned long long>>;


Matrix nhan_matrix(const Matrix& A, const Matrix& B) {
    Matrix C(4, vector<unsigned long long>(4, 0));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                C[i][j] = (C[i][j] + nhan_mod(A[i][k], B[k][j])) % MOD;
            }
        }
    }
    return C;
}
Matrix matrix_mu(Matrix A, unsigned long long n) {
    Matrix res = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}; 
    while (n > 0) {
        if (n % 2 == 1) {
            res = nhan_matrix(res, A);
        }
        A = nhan_matrix(A, A);
        n /= 2;
    }
    return res;
}

void solve() {
    unsigned long long n;
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    if (n == 2) {
        cout << 3 << endl;
        return;
    }
    if (n == 3) {
        cout << 6 << endl;
        return;
    }
    Matrix M = {{1, 1, 1, 1}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 1, 0}};
    Matrix result_matrix = matrix_mu(M, n - 3);

    vector<unsigned long long> base_vector = {6, 3, 2, 1};
    
    // F(n) = (result_matrix * base_vector)[0]
    unsigned long long Fn = (nhan_mod(result_matrix[0][0], base_vector[0]) +
                             nhan_mod(result_matrix[0][1], base_vector[1]) +
                             nhan_mod(result_matrix[0][2], base_vector[2]) +
                             nhan_mod(result_matrix[0][3], base_vector[3])) % MOD;
    
    cout << Fn << endl;
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
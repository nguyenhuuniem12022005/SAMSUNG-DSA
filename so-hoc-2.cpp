// Cho dãy số {A[1], A[2], …, A[N]} và M dãy số {B[i][1], B[i][2], …, B[i][N]}.

// Với mỗi truy vấn, bạn cần trả lời xem tích A[1]*A[2]*…*A[N] có chia hết cho tích B[i][1]*B[i][2]*…*B[i][N] hay không?

// Input:

// Dòng đầu tiên là hai số nguyên N và M (N, M <= 100).

// Dòng tiếp theo gồm N số nguyên A[i].

// M dòng tiếp, mỗi dòng là một truy vấn gồm N số nguyên B[i][1], B[i][2], ..., B[i][N].

// Output: 

// Dòng đầu tiên in ra số bộ dãy số B[] thỏa mãn. Dòng thứ 2 in ra lần lượt chỉ số bộ dãy thứ i thỏa mãn yêu cầu.

// Giới hạn:

// Subtask 1 (50%): Các số có giá trị không vượt quá 10000.

// Subtask 2 (50%): Các số có giá trị không vượt quá 1015.

// Test ví dụ:          

// Input

// Output

// 3 4

// 7 10 2011

// 1 3 5

// 2 2 7

// 7 2 5

// 14 1 2011
// output
// 2

// 3 4
// input
// 3 2
// 10000000000000061 10000000000000069 10000000000000079
// 10000000000000099 10000000000000453 10000000000000481
// 10000000000000597 10000000000000613 10000000000000639	
// output
// 0

#include <iostream>
#include <vector>
#include <numeric> // For std::gcd in C++17
#include <map>
#include <algorithm>

// Sử dụng kiểu __int128_t để tránh tràn số khi nhân hai số long long
using int128 = __int128_t;

// Hàm nhân và lũy thừa với modulo để xử lý số lớn
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    int128 b = base;
    b %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (int128)res * b % mod;
        b = b * b % mod;
        exp /= 2;
    }
    return res;
}

// Hàm kiểm tra số nguyên tố Miller-Rabin
bool is_prime(long long n) {
    if (n < 2) return false;
    // Các cơ số kiểm tra hiệu quả cho số tới 10^16
    std::vector<long long> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if (n < 38) {
        for (long long p : bases) {
            if (n == p) return true;
        }
        return false;
    }
    
    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (long long a : bases) {
        if (n == a) return true;
        long long x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = (int128)x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

// Thuật toán Pollard's Rho tìm ước số
long long pollard_rho(long long n) {
    if (n % 2 == 0) return 2;
    if (is_prime(n)) return n;
    
    int128 x = rand() % (n - 2) + 2;
    int128 y = x;
    long long c = rand() % (n - 1) + 1;
    long long d = 1;

    while (d == 1) {
        x = (x * x + c) % n;
        y = (y * y + c) % n;
        y = (y * y + c) % n;
        d = std::gcd(std::abs((long long)(x - y)), n);
        if (d == n) {
            // Nếu không tìm được, thử lại với x, y, c khác
            return pollard_rho(n); 
        }
    }
    return d;
}

// Cache để lưu kết quả phân tích
std::map<long long, std::map<long long, int>> factor_cache;

// Hàm đệ quy phân tích thừa số nguyên tố
void get_prime_factorization(long long n, std::map<long long, int>& factors) {
    if (n <= 1) return;
    
    // Sử dụng cache nếu đã tính
    if (factor_cache.count(n)) {
        for (auto const& [prime, count] : factor_cache[n]) {
            factors[prime] += count;
        }
        return;
    }
    
    if (is_prime(n)) {
        factors[n]++;
        return;
    }

    long long divisor = pollard_rho(n);
    get_prime_factorization(divisor, factors);
    get_prime_factorization(n / divisor, factors);
}

// Hàm chính để giải quyết bài toán
void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<long long> a_list(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a_list[i];
    }

    // 1. Phân tích thừa số nguyên tố cho tích của A
    std::map<long long, int> a_prime_factors;
    for (long long num : a_list) {
        if (factor_cache.count(num)) {
             for (auto const& [prime, count] : factor_cache[num]) {
                a_prime_factors[prime] += count;
            }
        } else {
            std::map<long long, int> temp_factors;
            get_prime_factorization(num, temp_factors);
            factor_cache[num] = temp_factors;
            for (auto const& [prime, count] : temp_factors) {
                a_prime_factors[prime] += count;
            }
        }
    }

    std::vector<int> valid_indices;
    for (int i = 1; i <= m; ++i) {
        std::vector<long long> b_list(n);
        std::map<long long, int> b_prime_factors;
        
        // 2. Phân tích thừa số nguyên tố cho tích của B
        for (int j = 0; j < n; ++j) {
            std::cin >> b_list[j];
            if (factor_cache.count(b_list[j])) {
                 for (auto const& [prime, count] : factor_cache[b_list[j]]) {
                    b_prime_factors[prime] += count;
                }
            } else {
                std::map<long long, int> temp_factors;
                get_prime_factorization(b_list[j], temp_factors);
                factor_cache[b_list[j]] = temp_factors;
                for (auto const& [prime, count] : temp_factors) {
                    b_prime_factors[prime] += count;
                }
            }
        }

        // 3. So sánh
        bool is_divisible = true;
        for (auto const& [prime, count] : b_prime_factors) {
            if (!a_prime_factors.count(prime) || a_prime_factors.at(prime) < count) {
                is_divisible = false;
                break;
            }
        }

        if (is_divisible) {
            valid_indices.push_back(i);
        }
    }

    // 4. In kết quả
    std::cout << valid_indices.size() << std::endl;
    if (!valid_indices.empty()) {
        for (int i = 0; i < valid_indices.size(); ++i) {
            std::cout << valid_indices[i] << (i == valid_indices.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }
}

int main() {
    // Tăng tốc độ nhập xuất
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    // Khởi tạo seed cho hàm random
    srand(time(0));

    solve();

    return 0;
}
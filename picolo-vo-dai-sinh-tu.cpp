#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring> // For memset

using namespace std;

// --- Hằng Số Toàn Cục và Mảng ---
const int MAX_COORD = 1000000; // Giá trị lớn nhất cho tọa độ x, y
const int MAX_QUERY = 100005;   // Số lượng đề xuất/truy vấn tối đa

// Mảng sàng số nguyên tố và thông tin liên quan
bool is_prime_sieve[MAX_COORD + 1];     // is_prime_sieve[i] = true nếu i là số nguyên tố
int min_prime_factor[MAX_COORD + 1];    // min_prime_factor[i] = ước số nguyên tố nhỏ nhất của i

// Mảng đếm tiền tố cho số nguyên tố và số nửa nguyên tố
long long pi_count[MAX_COORD + 1];       // pi_count[k] = số lượng số nguyên tố <= k
long long semiprime_count[MAX_COORD + 1]; // semiprime_count[k] = số lượng số nửa nguyên tố <= k

// --- Hàm Tiền Xử Lý (Sàng Eratosthenes và Tính Toán) ---
void sieve_precompute() {
    fill(is_prime_sieve, is_prime_sieve + MAX_COORD + 1, true); // Khởi tạo tất cả là nguyên tố
    memset(min_prime_factor, 0, sizeof(min_prime_factor));     // Khởi tạo ước số nhỏ nhất là 0

    is_prime_sieve[0] = is_prime_sieve[1] = false; // 0 và 1 không phải số nguyên tố
    
    // Sàng Eratosthenes
    for (int p = 2; p <= MAX_COORD; ++p) {
        if (is_prime_sieve[p]) { // Nếu p là số nguyên tố
            min_prime_factor[p] = p; // Ước số nhỏ nhất của p là chính nó
            // Đánh dấu bội số của p không phải số nguyên tố
            // Bắt đầu từ p*p vì các bội nhỏ hơn đã được đánh dấu bởi các ước số nhỏ hơn p
            for (long long multiple = (long long)p * p; multiple <= MAX_COORD; multiple += p) {
                is_prime_sieve[multiple] = false;
                if (min_prime_factor[multiple] == 0) { // Đặt ước số nguyên tố nhỏ nhất (SPF) chỉ một lần
                    min_prime_factor[multiple] = p;
                }
            }
        }
    }
    
    // Tính toán mảng đếm tiền tố pi_count và semiprime_count
    pi_count[0] = pi_count[1] = 0;
    semiprime_count[0] = semiprime_count[1] = 0;
    
    for (int i = 2; i <= MAX_COORD; ++i) {
        pi_count[i] = pi_count[i-1];           // Copy giá trị từ phần tử trước
        semiprime_count[i] = semiprime_count[i-1]; // Copy giá trị từ phần tử trước

        if (is_prime_sieve[i]) { // Nếu i là số nguyên tố
            pi_count[i]++;     // Tăng bộ đếm số nguyên tố
        } else {
            // Nếu i không phải số nguyên tố, kiểm tra xem nó có phải số nửa nguyên tố không
            // Một số i là số nửa nguyên tố (p1*p2, p1!=p2) nếu:
            // 1. Nó là số không nguyên tố.
            // 2. Ước số nguyên tố nhỏ nhất của nó là p = min_prime_factor[i].
            // 3. Phần còn lại (i/p) phải là một số nguyên tố khác p.
            int p = min_prime_factor[i]; // Ước số nguyên tố nhỏ nhất của i
            int remaining_val = i / p;   // Phần còn lại sau khi chia cho p

            // Nếu phần còn lại là số nguyên tố VÀ khác với p
            if (is_prime_sieve[remaining_val] && p != remaining_val) {
                semiprime_count[i]++; // Tăng bộ đếm số nửa nguyên tố
            }
        }
    }
}

// Hàm tính S(X,Y) = Sum_{x=1..X, y=1..Y} [x*y là số nửa nguyên tố]
// Đây là hàm chính để tính số điểm trong một hình chữ nhật từ (1,1) đến (X,Y).
// Dựa trên phân tích 3 trường hợp: (prime, prime), (1, semiprime), (semiprime, 1).
long long calculate_S(int X, int Y) {
    if (X <= 0 || Y <= 0) return 0; // Nếu X hoặc Y không hợp lệ, không có điểm nào.

    // Phần 1: (x là số nguyên tố VÀ y là số nguyên tố VÀ x ≠ y)
    // Tổng số cặp (x,y) với x<=X, y<=Y, x nguyên tố, y nguyên tố là pi_count[X] * pi_count[Y].
    // Trừ đi trường hợp x=y (tức là x*y = x^2, không phải số nửa nguyên tố theo định nghĩa)
    // Số trường hợp x=y là số lượng số nguyên tố nhỏ hơn hoặc bằng min(X, Y).
    long long count_prime_prime = pi_count[X] * pi_count[Y];
    count_prime_prime -= min(pi_count[X], pi_count[Y]); 

    // Phần 2: (x=1 VÀ y là số nửa nguyên tố)
    long long count_one_semiprime = semiprime_count[Y]; 

    // Phần 3: (y=1 VÀ x là số nửa nguyên tố)
    long long count_semiprime_one = semiprime_count[X]; 

    // Tổng số điểm là tổng của 3 phần. Không có sự trùng lặp giữa các phần này
    // vì (1, semiprime) không trùng với (prime, prime) (vì 1 không phải nguyên tố).
    // Và (semiprime, 1) cũng không trùng với (prime, prime).
    return count_prime_prime + count_one_semiprime + count_semiprime_one;
}

// --- Hàm Giải Quyết Một Bộ Đề Xuất (Từng Test Case) ---
void solve_proposals() {
    int N_proposals; // Số lượng đề xuất (N)
    scanf("%d", &N_proposals);

    // Duyệt qua từng đề xuất
    for (int i = 0; i < N_proposals; ++i) {
        int a, b, c, d; // Tọa độ hình chữ nhật (góc trái dưới (a,b), góc phải trên (c,d))
        scanf("%d%d%d%d", &a, &b, &c, &d);

        // Áp dụng nguyên lý Bao hàm - Loại trừ cho tổng 2D:
        // Sum(a..c, b..d) = S(c,d) - S(a-1,d) - S(c,b-1) + S(a-1,b-1)
        long long result = calculate_S(c, d) 
                         - calculate_S(a - 1, d) 
                         - calculate_S(c, b - 1) 
                         + calculate_S(a - 1, b - 1);
        
        printf("%lld\n", result); // In kết quả cho đề xuất hiện tại
    }
}

// --- Hàm Main Chính ---
int main() {
    // Tối ưu hóa luồng nhập xuất của C++ để tăng tốc độ.
    // Rất quan trọng cho các bài toán có lượng dữ liệu lớn.
    ios_base::sync_with_stdio(false); // Tắt đồng bộ hóa giữa C++ streams và C stdio
    cin.tie(NULL); // Hủy liên kết cin với cout, giúp cin không chờ cout

    // Gọi hàm sàng và tiền xử lý một lần duy nhất khi chương trình bắt đầu
    sieve_precompute();

    // Gọi hàm giải quyết các đề xuất
    // (Đề bài này có vẻ chỉ có 1 test case lớn chứa N đề xuất, không có T bộ test nhỏ)
    solve_proposals();

    return 0; // Chương trình kết thúc thành công
}
// Xét dãy số vô hạn gồm các số tự nhiên 1, 2, 3, 4, …. Và dãy số a[] gồm có N phần tử. Trên dãy vô hạn các số tự nhiên này, tiến hành xóa các số chia hết cho a[1], sau đó xóa các số chia hết cho a[2] mà chưa được xóa, …, cuối cùng xóa hết các số chia hết cho a[N].

// Hãy tìm phần tử thứ K trên dãy số còn lại thu được.

// Input:

// Dòng đầu tiên là số lượng bộ test T (T <= 100).

// Mỗi test bắt đầu bằng hai số nguyên dương N và K (1 <= K <= 10^15).

// Dòng thứ hai gồm N số nguyên dương a[1], a[2], …, a[K] (1 < a[i] <= 10^15).

// Subtask 1: n <= 3 (60%)

// Subtask 2: n <= 10 (40%)

// Output: 

// Với mỗi test, hãy in ra đáp án tìm được trên một dòng.

// Example:            

// Input



// 2

// 1 5

// 2

// 2 2

// 2 3

 
// Output
// 9

// 5

 

// Giải thích test 1: Dãy số còn lại là: 1, 3, 5, 7, 9, 11, 13, …

// Giải thích test 2: Dãy số còn lại là: 1, 4, 5, 7, 11, 13, 17, 19, 23, 25…
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Sử dụng kiểu __int128_t để tránh tràn số khi tính BCNN
using int128 = __int128_t;

// Hàm tìm ước chung lớn nhất
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

// Hàm đếm số lượng số còn lại trong đoạn [1, x]
long long count_remaining(long long x, const std::vector<long long>& a) {
    int n = a.size();
    long long removed_count = 0;

    // Duyệt qua tất cả các tập con không rỗng của a[] bằng bitmask
    for (int i = 1; i < (1 << n); ++i) {
        int128 current_lcm = 1;
        int subset_size = 0;

        for (int j = 0; j < n; ++j) {
            // Nếu bit thứ j được bật, a[j] có trong tập con hiện tại
            if ((i >> j) & 1) {
                subset_size++;
                long long current_a = a[j];
                // Tính BCNN, kiểm tra tràn số cẩn thận
                // lcm(A, B) = (A / gcd(A, B)) * B
                current_lcm = (current_lcm / gcd((long long)current_lcm, current_a)) * current_a;
                
                // Nếu BCNN vượt quá x, các bội của nó cũng vậy, ta có thể dừng sớm
                if (current_lcm > x) {
                    current_lcm = x + 1; // Đánh dấu là đã tràn
                    break;
                }
            }
        }

        if (current_lcm > x) {
            continue;
        }

        // Áp dụng Nguyên lý bù trừ
        if (subset_size % 2 == 1) { // Tập con có số lẻ phần tử thì cộng
            removed_count += x / (long long)current_lcm;
        } else { // Tập con có số chẵn phần tử thì trừ
            removed_count -= x / (long long)current_lcm;
        }
    }

    return x - removed_count;
}

void solve() {
    int n;
    long long k;
    std::cin >> n >> k;
    std::vector<long long> a_raw(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a_raw[i];
    }

    // Tiền xử lý: loại bỏ các số thừa
    std::sort(a_raw.begin(), a_raw.end());
    std::vector<long long> a;
    for (int i = 0; i < n; ++i) {
        bool is_redundant = false;
        for (int j = 0; j < i; ++j) {
            if (a_raw[i] % a_raw[j] == 0) {
                is_redundant = true;
                break;
            }
        }
        if (!is_redundant) {
            a.push_back(a_raw[i]);
        }
    }

    // Tìm kiếm nhị phân câu trả lời
    long long low = 1, high = 4e15, ans = high;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (count_remaining(mid, a) >= k) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    std::cout << ans << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
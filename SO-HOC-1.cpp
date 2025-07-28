#include <bits/stdc++.h>
using namespace std;
// Cho số nguyên dương N. Hãy phân tích N thành tích của các thừa số nguyên tố.

// Input:

// Dòng đầu tiên là số lượng bộ test T (T <= 10).

// Mỗi test gồm một số nguyên dương N (2 <= N <= 10^14).

// Output: 

// Với mỗi test, liệt kê các thừa số và số mũ theo thứ tự tăng dần. Sau mỗi test, in ra một dấu xuống dòng.

// Example:            

// Input

// Output

// 2

// 4

// 168

// 2 2

 

// 2 3

// 3 1

// 7 1
void solve(long long n) {
    
    map<long long, int> factors; // Lưu trữ các thừa số và số mũ
    while (n% 2==0)
    {
        factors[2]++;
        n /= 2;
    }
    for (long long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors[i]++;
            n /= i;
        }
    }
    if (n > 1) {
        factors[n]++; // Nếu n là một số nguyên tố lớn hơn 1
    }
    for (const auto& factor : factors) {
        cout << factor.first << " " << factor.second << endl; // In thừa số và số mũ
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T; // Số lượng bộ test
    cin >> T;
    
    while (T--) {
        long long N; // Số nguyên dương N
        cin >> N;
        
        solve(N); // Gọi hàm giải quyết cho từng bộ test
        
        cout << endl; // In dấu xuống dòng sau mỗi test
    }
    
    return 0; // Kết thúc chương trình
}

 
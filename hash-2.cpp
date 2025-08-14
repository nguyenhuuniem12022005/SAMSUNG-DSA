// Cho xâu S. Hãy tìm xâu đối xứng dài nhất gồm các kí tự liên tiếp trong S.

// Input:

// Dòng đầu tiên là số lượng bộ test T (T <= 20).

// Mỗi test bắt đầu bởi  số nguyên N (N <= 100 000) là độ dài của xâu.

// Dòng tiếp theo là xâu S.

// Output: 

// Với mỗi test, in ra đáp án tìm được trên một dòng.

// Test ví dụ:

// Input:
// 2
// 5
// abacd
// 5
// abcde

 
// OUPUT:
// 3
// 1

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll BASE = 31;
const ll MOD = 1e9 + 7;
const int MAXN = 100005;

ll pow_val[MAXN];
ll hash_s[MAXN];
ll hash_rev_s[MAXN];

void precompute_hashes(const string& s) {
    int n = s.length();
    pow_val[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow_val[i] = (pow_val[i - 1] * BASE) % MOD;
    }

    // Thêm dấu cách vào đầu xâu S để chỉ số bắt đầu từ 1
    string S_padded = " " + s;
    hash_s[0] = 0;
    for (int i = 1; i <= n; i++) {
        hash_s[i] = (hash_s[i - 1] * BASE + (S_padded[i] - 'a' + 1)) % MOD;
    }

    // Thêm dấu cách vào đầu xâu đảo ngược của S
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    string rev_S_padded = " " + rev_s;
    hash_rev_s[0] = 0;
    for (int i = 1; i <= n; i++) {
        hash_rev_s[i] = (hash_rev_s[i - 1] * BASE + (rev_S_padded[i] - 'a' + 1)) % MOD;
    }
}

ll get_hash(const ll h[], int i, int j) {
    int len = j - i + 1;
    ll result = (h[j] - (h[i - 1] * pow_val[len]) % MOD + MOD) % MOD;
    return result;
}

bool is_palindrome_of_length(int len, const string& s) {
    int n = s.length();
    if (len == 0) return true;
    for (int i = 1; i <= n - len + 1; i++) {
        int j = i + len - 1;
        
        ll sub_hash = get_hash(hash_s, i, j);

        int rev_i = n - j + 1;
        int rev_j = n - i + 1;
        ll rev_sub_hash = get_hash(hash_rev_s, rev_i, rev_j);
        
        if (sub_hash == rev_sub_hash) {
            return true;
        }
    }
    return false;
}

int solve() {
    int N;
    cin >> N;
    string S;
    cin >> S;

    precompute_hashes(S);
    
    int max_len = 0;
    
    // Tìm kiếm nhị phân cho độ dài lẻ
    int left = 1, right = N;
    int ans_odd = 0;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (mid % 2 == 0) mid++;
        if (mid > N) {
            right = mid - 2;
            continue;
        }
        if (is_palindrome_of_length(mid, S)) {
            ans_odd = mid;
            left = mid + 2;
        } else {
            right = mid - 2;
        }
    }

    // Tìm kiếm nhị phân cho độ dài chẵn
    left = 2, right = N;
    int ans_even = 0;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (mid % 2 != 0) mid++;
        if (mid > N) {
            right = mid - 2;
            continue;
        }
        if (is_palindrome_of_length(mid, S)) {
            ans_even = mid;
            left = mid + 2;
        } else {
            right = mid - 2;
        }
    }

    return max(ans_odd, ans_even);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cout << solve() << endl;
    }

    return 0;
}
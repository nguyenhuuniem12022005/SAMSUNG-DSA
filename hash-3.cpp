// Cho xâu S gồm N kí tự và số nguyên dương K. Hãy xác định xâu con dài nhất và xuất hiện ít nhất K lần trong S.

// Input:

// Dòng đầu tiên là số lượng bộ test (T <= 20).

// Mỗi bộ test bắt đầu bởi 2 số N và K (N <= 100 000 và 1 <= K <= 200).

// Dòng tiếp theo là xâu S chỉ gồm các kí tự thường.

// Output: 

// Với mỗi test, in ra độ dài xâu con xuất hiện ít nhất K lần trong xâu S. Nếu không có đáp án, in ra 0.

// Ví dụ:

// Input:



// 2

// 5 2

// aaaaa

// 6 2

// abcdef

 
// Output
// 4

// 0

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

const ll BASE = 31;
const ll MOD = 1e9 + 7;

ll pow_val[100005];
ll hash_val[100005];

void xu_ly(const string& s, int n) {
    pow_val[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow_val[i] = (pow_val[i - 1] * BASE) % MOD;
    }

    hash_val[0] = 0;
    for (int i = 1; i <= n; i++) {
        hash_val[i] = (hash_val[i - 1] * BASE + (s[i - 1] - 'a' + 1)) % MOD;
    }
}

ll get_hash(int i, int j) {
    int len = j - i + 1;
    ll h = (hash_val[j] - (hash_val[i - 1] * pow_val[len]) % MOD + MOD) % MOD;
    return h;
}
//Hàm này kiểm tra xem có tồn tại xâu con nào có độ dài len xuất hiện ít nhất k lần hay không.
bool check(int len, int n, int k) {
    if (len == 0) return true;
    vector<ll> hashes;
    for (int i = 1; i <= n - len + 1; i++) {
        hashes.push_back(get_hash(i, i + len - 1));
    }
    sort(hashes.begin(), hashes.end());

    int count = 1;
    for (size_t i = 1; i < hashes.size(); i++) {
        if (hashes[i] == hashes[i-1]) {
            count++;
        } else {
            count = 1;
        }
        if (count >= k) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        string S;
        cin >> S;

        xu_ly(S, N);

        int low = 0, high = N, ans = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid, N, K)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
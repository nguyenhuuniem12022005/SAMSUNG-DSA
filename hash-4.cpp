// Cho số nguyên S gồm N chữ số. Có Q truy vấn, mỗi truy vấn thuộc một trong hai loại sau:

// q L R: yêu cầu xác định xâu con S[L, L+1, …, R] có phải là một xâu đối xứng hay không?

// c U x: thay đổi kí tự thứ U thành kí tự x.

// Input:

// Dòng đầu tiên chứa số nguyên S gồm N kí tự.

// Tiếp theo là số lượng truy vấn Q.

// Q dòng tiếp theo, mỗi dòng gồm một loại truy vấn.

// Output:

// Với mỗi truy vấn loại 1, nếu xâu con là một số đối xứng, hãy in ra “YES”, ngược lại in ra “NO”.

// Giới hạn:

// Subtask 1 (40%): 1 ≤ N, Q ≤ 1000.
// Subtask 2 (60%): 1 ≤ N, Q ≤ 200000.
// Test ví dụ:     

// Input
// 12345
// 5
// q 1 5
// q 5 5
// c 4 3
// q 3 5
// q 3 4

// output
// NO
// YES
// NO
// YES


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll BASE = 31;
const ll MOD = 1e9 + 7;
const int MAXN = 200005;

ll pow_val[MAXN];
char s_global[MAXN];
int N;

// Cây phân đoạn cho xâu S
ll seg_tree_s[4 * MAXN];

// Cây phân đoạn cho xâu S đảo ngược
ll seg_tree_s_rev[4 * MAXN];

// Hàm kết hợp các giá trị Hash
ll combine_hashes(ll h1, ll h2, int len2) {
    return (h1 * pow_val[len2] + h2) % MOD;
}

// Xây dựng cây phân đoạn cho xâu S
void build_s(int node, int start, int end) {
    if (start == end) {
        seg_tree_s[node] = (s_global[start] - '0' + 1);
        return;
    }
    int mid = (start + end) / 2;
    build_s(2 * node, start, mid);
    build_s(2 * node + 1, mid + 1, end);
    int len_right = end - (mid + 1) + 1;
    seg_tree_s[node] = combine_hashes(seg_tree_s[2 * node], seg_tree_s[2 * node + 1], len_right);
}

// Xây dựng cây phân đoạn cho xâu S đảo ngược
void build_s_rev(int node, int start, int end) {
    if (start == end) {
        seg_tree_s_rev[node] = (s_global[N - start + 1] - '0' + 1);
        return;
    }
    int mid = (start + end) / 2;
    build_s_rev(2 * node, start, mid);
    build_s_rev(2 * node + 1, mid + 1, end);
    int len_right = end - (mid + 1) + 1;
    seg_tree_s_rev[node] = combine_hashes(seg_tree_s_rev[2 * node], seg_tree_s_rev[2 * node + 1], len_right);
}

// Cập nhật cây phân đoạn cho xâu S
void update_s(int node, int start, int end, int idx, char val) {
    if (start == end) {
        s_global[idx] = val;
        seg_tree_s[node] = (val - '0' + 1);
        return;
    }
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid) {
        update_s(2 * node, start, mid, idx, val);
    } else {
        update_s(2 * node + 1, mid + 1, end, idx, val);
    }
    int len_right = end - (mid + 1) + 1;
    seg_tree_s[node] = combine_hashes(seg_tree_s[2 * node], seg_tree_s[2 * node + 1], len_right);
}

// Cập nhật cây phân đoạn cho xâu S đảo ngược
void update_s_rev(int node, int start, int end, int idx, char val) {
    if (start == end) {
        seg_tree_s_rev[node] = (val - '0' + 1);
        return;
    }
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid) {
        update_s_rev(2 * node, start, mid, idx, val);
    } else {
        update_s_rev(2 * node + 1, mid + 1, end, idx, val);
    }
    int len_right = end - (mid + 1) + 1;
    seg_tree_s_rev[node] = combine_hashes(seg_tree_s_rev[2 * node], seg_tree_s_rev[2 * node + 1], len_right);
}

// Truy vấn Hash từ cây phân đoạn cho xâu S
pair<ll, int> query_s(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return {0, 0};
    }
    if (l <= start && end <= r) {
        return {seg_tree_s[node], end - start + 1};
    }
    int mid = (start + end) / 2;
    pair<ll, int> p1 = query_s(2 * node, start, mid, l, r);
    pair<ll, int> p2 = query_s(2 * node + 1, mid + 1, end, l, r);
    
    if (p1.second == 0) return p2;
    if (p2.second == 0) return p1;
    
    return {combine_hashes(p1.first, p2.first, p2.second), p1.second + p2.second};
}

// Truy vấn Hash từ cây phân đoạn cho xâu S đảo ngược
pair<ll, int> query_s_rev(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return {0, 0};
    }
    if (l <= start && end <= r) {
        return {seg_tree_s_rev[node], end - start + 1};
    }
    int mid = (start + end) / 2;
    pair<ll, int> p1 = query_s_rev(2 * node, start, mid, l, r);
    pair<ll, int> p2 = query_s_rev(2 * node + 1, mid + 1, end, l, r);
    
    if (p1.second == 0) return p2;
    if (p2.second == 0) return p1;
    
    return {combine_hashes(p1.first, p2.first, p2.second), p1.second + p2.second};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s_input;
    cin >> s_input;
    N = s_input.length();
    
    // Thêm ký tự đệm để chỉ số bắt đầu từ 1
    for (int i = 0; i < N; i++) {
        s_global[i + 1] = s_input[i];
    }
    
    pow_val[0] = 1;
    for (int i = 1; i <= N; i++) {
        pow_val[i] = (pow_val[i - 1] * BASE) % MOD;
    }
    
    build_s(1, 1, N);
    build_s_rev(1, 1, N);

    int Q;
    cin >> Q;
    while (Q--) {
        char type;
        cin >> type;
        if (type == 'q') {
            int L, R;
            cin >> L >> R;
            ll hash_s_val = query_s(1, 1, N, L, R).first;
            
            int L_rev = N - R + 1;
            int R_rev = N - L + 1;
            ll hash_s_rev_val = query_s_rev(1, 1, N, L_rev, R_rev).first;
            
            if (hash_s_val == hash_s_rev_val) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else if (type == 'c') {
            int U;
            char x;
            cin >> U >> x;
            
            update_s(1, 1, N, U, x);
            
            int U_rev = N - U + 1;
            update_s_rev(1, 1, N, U_rev, x);
        }
    }
    
    return 0;
}
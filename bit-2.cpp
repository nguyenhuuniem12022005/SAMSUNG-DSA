// Cho dãy số A[] có N phần tử. Có Q truy vấn:

// Loại 1: 1 u v K
//               Tăng giá trị các phần tử A[u], A[u+1], …, A[v] lên K đơn vị

// Lọai 2: 2 u
//               Yêu cầu in ra giá trị phần tử A[u].

// Input

// Dòng đầu tiên là số nguyên N (1 <= N <= 100 000).
// Dòng tiếp theo gồm N số nguyên A[i] (1 <= A[i] <= 10^9).
// Tiếp theo là số lượng truy vấn Q (1 <= Q <= 100 000).
// Q dòng tiếp theo, mỗi dòng gồm một loại truy vấn.
// Giới hạn: 1 <= u <= v <= N, 1 <= K <= 10^9.
// Output

// Với mỗi truy vấn, in ra đáp án tìm được trên một dòng.
// Test ví dụ:

// Input

// 5

// 5 1 2 3 4

// 4

// 1 2 4 5

// 1 1 3 10

// 2 5

// 2 3

 
// Output
// 4

// 17

 

// Giải thích test:

// Dãy số sau truy vấn thứ hai là 15 16 17 8 4.

#include <iostream>
#include <vector>

const int MAXN = 100005;
long long bit[MAXN];
int N_global; 

void update(int idx, long long val) {
    for (; idx <= N_global; idx += idx & (-idx)) {
        bit[idx] += val;
    }
}

long long query(int idx) {
    long long sum = 0;
    for (; idx > 0; idx -= idx & (-idx)) {
        sum += bit[idx];
    }
    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> N_global;

    long long prev_A_val = 0;

    for (int i = 1; i <= N_global; ++i) {
        long long current_A_val;
        std::cin >> current_A_val;
        update(i, current_A_val - prev_A_val);
        prev_A_val = current_A_val;
    }

    int Q;
    std::cin >> Q;

    for (int q_idx = 0; q_idx < Q; ++q_idx) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int u, v;
            long long K;
            std::cin >> u >> v >> K;
            
            update(u, K);
            if (v + 1 <= N_global) {
                update(v + 1, -K);
            }
        } else {
            int u;
            std::cin >> u;
            long long result = query(u);
            std::cout << result << "\n";
        }
    }

    return 0;
}
// Giả sử bạn có một mảng gốc A. Mảng hiệu D được định nghĩa như sau:

// D[1]=A[1]

// D[i]=A[i]−A[i−1] với i1

// Từ định nghĩa này, bạn có thể dễ dàng thấy rằng:
// A[u]=D[1]+D[2]+
// dots+D[u]=
// sum_i=1 
// u
//  D[i]

// Tức là, giá trị của A[u] chính là tổng tiền tố của mảng hiệu D đến vị trí u.

// Làm thế nào để cập nhật đoạn trên mảng hiệu?
// Khi bạn muốn tăng tất cả các phần tử từ A[u] đến A[v] lên K:

// Phần tử A[u]: Tăng thêm K. Điều này làm cho hiệu A[u]−A[u−1] thay đổi. Cụ thể, D[u] phải tăng thêm K.

// Các phần tử A[i] trong đoạn (u,v]: A[i] và A[i−1] đều tăng thêm K. Do đó, hiệu A[i]−A[i−1] (tức D[i]) không thay đổi.

// Phần tử A[v+1]: Phần tử này không được tăng, nhưng A[v] thì có. Do đó, hiệu A[v+1]−A[v] sẽ thay đổi. Cụ thể, D[v+1] phải giảm đi K. (Nếu v=N, không có A[v+1] thì không cần xử lý D[v+1]).

// Tóm lại, để tăng A[u],
// dots,A[v] lên K đơn vị, bạn chỉ cần thực hiện 2 thao tác trên mảng hiệu:

// Tăng D[u] lên K.

// Giảm D[v+1] đi K. (Chỉ khi $v \< N$).

// Kết hợp BIT và mảng hiệu
// Vì giá trị A[u] là tổng tiền tố của mảng hiệu D đến vị trí u, và các thao tác cập nhật trên mảng hiệu (tăng/giảm một điểm) là chính xác những gì BIT xử lý hiệu quả.

// Chúng ta sẽ xây dựng một BIT trên mảng hiệu D.

// Khởi tạo BIT: Ban đầu, chúng ta cần chuyển đổi mảng A thành mảng hiệu D và sau đó xây dựng BIT từ D.

// D[1]=A[1]

// D[i]=A[i]−A[i−1] cho i=2
// dotsN.

// Sau đó, dùng các giá trị D[i] này để update vào BIT.

// Truy vấn loại 1 (1 u v K):

// Gọi update(u, K) trên BIT.

// Nếu $v \< N$, gọi update(v + 1, -K) trên BIT.

// Mỗi lần cập nhật này mất O(
// logN).

// Truy vấn loại 2 (2 u):

// Giá trị của A[u] chính là tổng tiền tố của mảng hiệu D đến vị trí u.

// Gọi query(u) trên BIT.

// Thao tác này mất O(
// logN).

// Vậy, cả hai loại truy vấn đều được xử lý trong O(
// logN) thời gian, tổng cộng O(Q
// logN) cho toàn bộ bài toán, đủ nhanh để vượt qua giới hạn thời gian.
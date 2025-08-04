// Cho dãy số A[] có N phần tử. Có Q truy vấn:

// Loại 1: 1 u K
// Tăng giá trị phần tử A[u] lên K đơn vị

// Lọai 2: 2 u v
// Yêu cầu in ra tổng A[u] + A[u+1] + … + A[v].

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

// 1 2 3 4 5

// 3

// 2 1 5

// 1 2 5

// 2 1 5

 
// Output
// 15

// 20

 

// Giải thích test:

// Dãy số sau truy vấn thứ hai là 6 2 3 4 5.

#include <iostream>
#include <vector>

// Định nghĩa một kiểu dữ liệu long long để chứa tổng lớn, tránh tràn số
typedef long long ll;

// Mảng chứa dữ liệu gốc A[] (dùng 1-based indexing cho dễ theo dõi)
std::vector<ll> A;
// Mảng chứa Segment Tree. Kích thước khoảng 4*N là an toàn.
std::vector<ll> tree;

// Kích thước của mảng A
int N_size; 

// Hàm xây dựng Segment Tree
// node: chỉ số của nút hiện tại trong mảng tree[]
// start, end: khoảng (chỉ số) mà nút node đại diện trong mảng A[]
void build(int node, int start, int end) {
    // Nếu đây là nút lá (khoảng chỉ có một phần tử)
    if (start == end) {
        tree[node] = A[start]; // Gán giá trị của phần tử A[start] vào nút lá
    } else {
        // Tìm điểm giữa để chia khoảng
        int mid = (start + end) / 2;
        // Xây dựng nút con trái (bao phủ khoảng [start, mid])
        build(2 * node, start, mid);
        // Xây dựng nút con phải (bao phủ khoảng [mid + 1, end])
        build(2 * node + 1, mid + 1, end);
        // Nút cha (node) lưu tổng của hai nút con
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

// Hàm cập nhật giá trị của một phần tử trong mảng A[] và Segment Tree
// node: chỉ số của nút hiện tại
// start, end: khoảng mà nút node đại diện
// idx: chỉ số của phần tử A[idx] cần cập nhật (trong mảng A[])
// val: giá trị muốn thêm vào A[idx]
void update(int node, int start, int end, int idx, ll val) {
    // Nếu đã tìm thấy nút lá tương ứng với A[idx]
    if (start == end) {
        A[idx] += val;      // Cập nhật giá trị trong mảng gốc A[] (tùy chọn, không bắt buộc)
        tree[node] += val;  // Cập nhật giá trị trong nút lá của Segment Tree
    } else {
        int mid = (start + end) / 2;
        // Kiểm tra xem idx nằm ở nửa trái hay nửa phải của khoảng hiện tại
        if (start <= idx && idx <= mid) {
            // Nếu idx nằm bên trái, đi xuống nút con trái
            update(2 * node, start, mid, idx, val);
        } else {
            // Nếu idx nằm bên phải, đi xuống nút con phải
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        // Sau khi nút con được cập nhật, cập nhật lại tổng cho nút cha
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

// Hàm truy vấn tổng các phần tử trong một khoảng [L, R]
// node: chỉ số của nút hiện tại
// start, end: khoảng mà nút node đại diện
// L, R: khoảng truy vấn (từ L đến R)
ll query(int node, int start, int end, int L, int R) {
    // Trường hợp 1: Khoảng của nút hiện tại hoàn toàn nằm ngoài khoảng truy vấn [L, R]
    if (end < L || start > R) {
        return 0; // Trả về 0 vì không có đóng góp vào tổng
    }

    // Trường hợp 2: Khoảng của nút hiện tại hoàn toàn nằm trong khoảng truy vấn [L, R]
    if (L <= start && end <= R) {
        return tree[node]; // Trả về giá trị đã tính sẵn của nút này
    }

    // Trường hợp 3: Khoảng của nút hiện tại giao một phần với khoảng truy vấn
    // Chia đôi khoảng và gọi đệ quy cho cả hai nút con
    int mid = (start + end) / 2;
    ll p1 = query(2 * node, start, mid, L, R);         // Tổng từ con trái
    ll p2 = query(2 * node + 1, mid + 1, end, L, R);   // Tổng từ con phải

    return p1 + p2; // Cộng tổng của hai phần
}

int main() {
    // Tối ưu hóa I/O cho C++ để đọc/ghi nhanh hơn
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> N_size;

    // Thay đổi kích thước mảng A (cộng thêm 1 để dùng 1-based indexing dễ hơn)
    A.resize(N_size + 1);
    // Thay đổi kích thước mảng tree (4 * N là an toàn cho cây nhị phân đầy đủ)
    tree.resize(4 * N_size + 1); 

    // Đọc N phần tử của mảng A
    for (int i = 1; i <= N_size; ++i) {
        std::cin >> A[i];
    }

    // Xây dựng Segment Tree từ mảng A ban đầu
    build(1, 1, N_size);

    int Q;
    std::cin >> Q; // Đọc số lượng truy vấn

    // Xử lý Q truy vấn
    for (int q = 0; q < Q; ++q) {
        int type;
        std::cin >> type;
        if (type == 1) {
            // Truy vấn loại 1: Cập nhật
            int u;
            ll K;
            std::cin >> u >> K;
            update(1, 1, N_size, u, K); // Bắt đầu cập nhật từ gốc (node 1)
        } else {
            // Truy vấn loại 2: Tổng khoảng
            int u, v;
            std::cin >> u >> v;
            // In ra tổng tìm được
            std::cout << query(1, 1, N_size, u, v) << "\n"; // Bắt đầu truy vấn từ gốc (node 1)
        }
    }

    return 0;
}
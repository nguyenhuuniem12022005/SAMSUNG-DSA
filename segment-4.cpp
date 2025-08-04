// Cho dãy số A = A[1], A[2], …, A[N] (0 <= A[i] <= 10^8). Có 2 loại truy vấn như sau:
// +) U u val: Thay giá trị A[u] = val (val <= 10^8).

// +) Q u v: Yêu cầu tìm ra 2 phần tử i, j nằm trong đoạn [u, v] (i khác j) sao cho tổng A[i] + A[j] là lớn nhất có thể.

// Input:

// Dòng đầu tiên là số lượng phần tử N và số lượng truy vấn M (N, M <= 100 000).

// M dòng tiếp, mỗi dòng gồm 1 dạng truy vấn.

// Output: 

// Với mỗi truy vấn loại 1, hãy in ra đáp án tìm được trên một dòng.

// Test ví dụ:

// Input:
// 5 4
// 1 2 3 4 5
// Q 2 5
// Q 2 4
// U 1 8
// Q 1 5


// Output
// 9
// 7
// 13

#include <iostream>
#include <vector>
#include <algorithm> // For std::sort, std::max
#include <climits>   // For LLONG_MIN

typedef long long ll;

// Cấu trúc lưu trữ hai giá trị lớn nhất tại mỗi nút Segment Tree
struct NodeInfo {
    ll max1; // Giá trị lớn nhất
    ll max2; // Giá trị lớn thứ hai

    // Hàm tạo mặc định: dùng cho các nút rỗng hoặc ngoài phạm vi truy vấn
    // Khởi tạo bằng giá trị rất nhỏ để đảm bảo mọi số hợp lệ đều lớn hơn
    NodeInfo() : max1(LLONG_MIN), max2(LLONG_MIN) {} // Sử dụng LLONG_MIN từ <climits>
    
    // Hàm tạo khi chỉ có một phần tử (nút lá hoặc sau cập nhật)
    NodeInfo(ll val) : max1(val), max2(LLONG_MIN) {}
};

// Mảng gốc A[] (sử dụng 1-based indexing)
std::vector<ll> A;
// Mảng lưu trữ Segment Tree
std::vector<NodeInfo> tree;

// Kích thước mảng A
int N_size;

// Hàm gộp thông tin từ hai nút con
NodeInfo combine(const NodeInfo& lc, const NodeInfo& rc) {
    std::vector<ll> temp_values;
    
    // Thêm các giá trị hợp lệ từ con trái vào mảng tạm
    if (lc.max1 != LLONG_MIN) temp_values.push_back(lc.max1);
    if (lc.max2 != LLONG_MIN) temp_values.push_back(lc.max2);
    
    // Thêm các giá trị hợp lệ từ con phải vào mảng tạm
    if (rc.max1 != LLONG_MIN) temp_values.push_back(rc.max1);
    if (rc.max2 != LLONG_MIN) temp_values.push_back(rc.max2);

    // Sắp xếp mảng tạm theo thứ tự giảm dần
    std::sort(temp_values.rbegin(), temp_values.rend()); 

    NodeInfo res;
    // Lấy giá trị lớn nhất (max1)
    if (!temp_values.empty()) {
        res.max1 = temp_values[0];
    }
    // Lấy giá trị lớn thứ hai (max2)
    if (temp_values.size() >= 2) {
        res.max2 = temp_values[1];
    }
    // Nếu temp_values có ít hơn 2 phần tử, max2 sẽ vẫn là LLONG_MIN
    // (đã được khởi tạo mặc định)

    return res;
}

// Hàm xây dựng Segment Tree
void build(int node, int start, int end) {
    if (start == end) { // Nếu là nút lá
        tree[node] = NodeInfo(A[start]); // Khởi tạo với 1 phần tử
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
}

// Hàm cập nhật giá trị A[idx] = val
void update(int node, int start, int end, int idx, ll val) {
    if (start == end) { // Nếu đến nút lá cần cập nhật
        A[idx] = val; // Cập nhật mảng gốc
        tree[node] = NodeInfo(val); // Cập nhật nút lá
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) { // Nếu idx nằm bên trái
            update(2 * node, start, mid, idx, val);
        } else { // Nếu idx nằm bên phải
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]); // Cập nhật lại nút cha
    }
}

// Hàm truy vấn để tìm hai phần tử lớn nhất trong đoạn [L, R]
NodeInfo query(int node, int start, int end, int L, int R) {
    // Trường hợp 1: Nút nằm hoàn toàn ngoài khoảng truy vấn
    if (end < L || start > R) {
        return NodeInfo(); // Trả về NodeInfo rỗng
    }

    // Trường hợp 2: Nút nằm hoàn toàn trong khoảng truy vấn
    if (L <= start && end <= R) {
        return tree[node]; // Trả về thông tin của nút này
    }

    // Trường hợp 3: Nút giao một phần với khoảng truy vấn
    int mid = (start + end) / 2;
    NodeInfo p1 = query(2 * node, start, mid, L, R);
    NodeInfo p2 = query(2 * node + 1, mid + 1, end, L, R);

    return combine(p1, p2); // Gộp kết quả từ hai con
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int M;
    std::cin >> N_size >> M;

    A.resize(N_size + 1);
    tree.resize(4 * N_size + 1); // Kích thước an toàn cho Segment Tree

    for (int i = 1; i <= N_size; ++i) {
        std::cin >> A[i];
    }

    build(1, 1, N_size); // Xây dựng cây

    for (int q = 0; q < M; ++q) {
        char type_char;
        int u, v; // u, v dùng cho cả U và Q
        std::cin >> type_char >> u;
        
        if (type_char == 'U') { // Truy vấn loại U: Update
            ll val;
            std::cin >> val; // val là tham số thứ 3 cho U
            update(1, 1, N_size, u, val);
        } else { // Truy vấn loại Q: Query
            std::cin >> v; // v là tham số thứ 3 cho Q
            NodeInfo result = query(1, 1, N_size, u, v);
            // Tổng lớn nhất là max1 + max2.
            // max2 có thể là LLONG_MIN nếu đoạn chỉ có 1 phần tử hoặc tất cả các phần tử còn lại là LLONG_MIN (không hợp lệ)
            // Tuy nhiên đề bài nói "tìm 2 phần tử i, j nằm trong đoạn [u, v] (i khác j)" nên
            // cần đảm bảo có ít nhất 2 phần tử hợp lệ trong đoạn.
            // Nếu có ít hơn 2 phần tử, max2 sẽ là LLONG_MIN, và tổng sẽ không chính xác.
            // Với N <= 100 000, chắc chắn có đủ 2 phần tử trong mọi đoạn hợp lệ.
            std::cout << result.max1 + result.max2 << "\n";
        }
    }

    return 0;
}
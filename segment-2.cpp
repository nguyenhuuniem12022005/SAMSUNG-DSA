// Cho dãy số A[] có N phần tử. Có 2 loại truy vấn như sau:

// 1 u val: Cập nhật giá trị A[u] = val
// 2 u v: Yêu cầu in ra chỉ số i sao cho A[i] là phần tử nhỏ nhất trong đoạn [u, v]. Nếu có nhiều đáp án, hãy tìm chỉ số i nhỏ nhất.
// Input:

// Dòng đầu tiên gồm 2 số nguyên, số lượng phần tử N và số lượng truy vấn M (N, M ≤ 200000).

// Dòng tiếp theo gồm N số nguyên mô tả dãy số A[i] (-109 ≤ A[i] ≤ 109).

// M dòng tiếp, mỗi dòng gồm 1 truy vấn.

// Output: 

// Với mỗi truy vấn loại 2, hãy in ra đáp án tìm được trên một dòng.

// Test ví dụ:

// Input:


// 5 4

// 1 2 3 4 5

// 2 2 5

// 1 3 1

// 2 1 5

// 2 2 5

// Output
// 2

// 1

// 3

#include <iostream>
#include <vector>
#include <algorithm> // Để sử dụng std::min và std::pair

// Định nghĩa một kiểu dữ liệu long long cho giá trị, và int cho chỉ số
typedef long long ll;

// Cặp (giá trị_nhỏ_nhất, chỉ_số_của_giá_trị_nhỏ_nhất)
struct NodeInfo {
    ll min_val;
    int min_idx;

    // Hàm tạo mặc định cho trường hợp không có giá trị (ví dụ, ngoài khoảng)
    // Dùng giá trị lớn nhất có thể và chỉ số không hợp lệ để đảm bảo
    // mọi giá trị hợp lệ khác đều nhỏ hơn
    NodeInfo() : min_val(2e9 + 7), min_idx(-1) {} // 2e9+7 là giá trị lớn hơn 10^9
    NodeInfo(ll val, int idx) : min_val(val), min_idx(idx) {}
};

// Mảng chứa dữ liệu gốc A[] (dùng 1-based indexing)
std::vector<ll> A;
// Mảng chứa Segment Tree, mỗi phần tử là một NodeInfo
std::vector<NodeInfo> tree;

// Kích thước của mảng A
int N_size; 

// Hàm kết hợp thông tin từ hai nút con
NodeInfo combine(const NodeInfo& left_child, const NodeInfo& right_child) {
    if (left_child.min_val < right_child.min_val) {
        return left_child;
    } else if (right_child.min_val < left_child.min_val) {
        return right_child;
    } else { // Nếu giá trị nhỏ nhất bằng nhau, chọn chỉ số nhỏ hơn
        return (left_child.min_idx < right_child.min_idx) ? left_child : right_child;
    }
}

// Hàm xây dựng Segment Tree
// node: chỉ số của nút hiện tại trong mảng tree[]
// start, end: khoảng (chỉ số) mà nút node đại diện trong mảng A[]
void build(int node, int start, int end) {
    if (start == end) { // Nếu đây là nút lá
        tree[node] = NodeInfo(A[start], start); // Lưu giá trị và chỉ số của nó
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid); // Xây dựng con trái
        build(2 * node + 1, mid + 1, end); // Xây dựng con phải
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]); // Kết hợp kết quả từ con
    }
}

// Hàm cập nhật giá trị của một phần tử A[idx]
// node: chỉ số của nút hiện tại
// start, end: khoảng mà nút node đại diện
// idx: chỉ số của phần tử A[idx] cần cập nhật
// val: giá trị mới cho A[idx]
void update(int node, int start, int end, int idx, ll val) {
    if (start == end) { // Nếu đã đến nút lá tương ứng với A[idx]
        A[idx] = val; // Cập nhật giá trị trong mảng gốc A[]
        tree[node] = NodeInfo(val, idx); // Cập nhật thông tin trong nút lá
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) { // idx nằm bên trái
            update(2 * node, start, mid, idx, val);
        } else { // idx nằm bên phải
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        // Sau khi nút con được cập nhật, cập nhật lại nút cha
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
}

// Hàm truy vấn phần tử nhỏ nhất trong khoảng [L, R]
// node: chỉ số của nút hiện tại
// start, end: khoảng mà nút node đại diện
// L, R: khoảng truy vấn
NodeInfo query(int node, int start, int end, int L, int R) {
    // Trường hợp 1: Khoảng của nút hiện tại hoàn toàn nằm ngoài khoảng truy vấn [L, R]
    if (end < L || start > R) {
        return NodeInfo(); // Trả về NodeInfo mặc định (min_val rất lớn, không hợp lệ)
    }

    // Trường hợp 2: Khoảng của nút hiện tại hoàn toàn nằm trong khoảng truy vấn [L, R]
    if (L <= start && end <= R) {
        return tree[node]; // Trả về thông tin đã tính sẵn của nút này
    }

    // Trường hợp 3: Khoảng của nút hiện tại giao một phần với khoảng truy vấn
    int mid = (start + end) / 2;
    // Lấy kết quả từ con trái
    NodeInfo p1 = query(2 * node, start, mid, L, R);
    // Lấy kết quả từ con phải
    NodeInfo p2 = query(2 * node + 1, mid + 1, end, L, R);

    // Kết hợp hai kết quả và trả về
    return combine(p1, p2);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int M; // Số lượng truy vấn
    std::cin >> N_size >> M;

    A.resize(N_size + 1);
    tree.resize(4 * N_size + 1); 

    for (int i = 1; i <= N_size; ++i) {
        std::cin >> A[i];
    }

    build(1, 1, N_size); // Xây dựng cây

    for (int q = 0; q < M; ++q) {
        int type;
        std::cin >> type;
        if (type == 1) { // Truy vấn loại 1: Cập nhật A[u] = val
            int u;
            ll val;
            std::cin >> u >> val;
            update(1, 1, N_size, u, val);
        } else { // Truy vấn loại 2: Tìm min trong [u, v]
            int u, v;
            std::cin >> u >> v;
            NodeInfo result = query(1, 1, N_size, u, v);
            std::cout << result.min_idx << "\n"; // In ra chỉ số nhỏ nhất
        }
    }

    return 0;
}
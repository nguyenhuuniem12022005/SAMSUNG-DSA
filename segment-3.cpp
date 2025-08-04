// Cho một dãy ngoặc độ dài N, cho M truy vấn có dạng L[i], R[i]. Yêu cầu của bài toán là với mỗi truy vấn tìm một chuỗi con (không cần liên tiếp) của chuỗi từ vị trí L[i] đến R[i] dài nhất mà tạo thành một dãy ngoặc đúng.

// Input:

// Dòng đầu tiên là một xâu mô tả dãy ngoặc có độ dài không quá 1000000. Chỉ số của xâu bắt đầu từ 1.

// Tiếp theo là số lượng truy vấn M (M ≤ 100000).

// M dòng tiếp, mỗi dòng gồm 2 số nguyên L[i], R[i] mô tả một truy vấn (1 ≤ L[i], R[i] ≤ N).

// Output: 

// Với mỗi truy vấn, hãy in ra độ dài của chuỗi con là dãy ngoặc đúng dài nhất tìm được.

// Test ví dụ:

// Input:
// (())((())()())(
// 5
// 2 2
// 2 3
// 1 6
// 2 9
// 1 13

// Output
// 0
// 2
// 4
// 6
// 12
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::min

// Kích thước tối đa của chuỗi
const int MAXN = 1000005;

// Chuỗi ngoặc đầu vào
std::string S; 
// Mảng lưu trữ Segment Tree
std::vector<struct NodeInfo> tree;

// Cấu trúc thông tin cho mỗi nút của Segment Tree
struct NodeInfo {
    int matched_pairs; // Số cặp ngoặc đúng đã được ghép hoàn chỉnh
    int open_needed;   // Số dấu '(' còn lại chưa được ghép (cần ')' ở bên phải)
    int close_needed;  // Số dấu ')' còn lại chưa được ghép (cần '(' ở bên trái)

    // Hàm tạo mặc định (cho nút rỗng hoặc ngoài phạm vi)
    NodeInfo() : matched_pairs(0), open_needed(0), close_needed(0) {}
    // Hàm tạo với các giá trị cụ thể
    NodeInfo(int m, int o, int c) : matched_pairs(m), open_needed(o), close_needed(c) {}
};

// Hàm gộp thông tin từ hai nút con
NodeInfo combine(const NodeInfo& left_child, const NodeInfo& right_child) {
    NodeInfo res;

    // Số cặp mới có thể được hình thành từ '(' của con trái và ')' của con phải
    int new_matches = std::min(left_child.open_needed, right_child.close_needed);

    // Tổng số cặp đã ghép:
    //   - Từ con trái
    //   - Từ con phải
    //   - Từ các cặp mới hình thành giữa hai con
    res.matched_pairs = left_child.matched_pairs + right_child.matched_pairs + new_matches;

    // Số dấu '(' còn lại chưa ghép:
    //   - Từ con trái (những cái chưa ghép với ')' của nó hoặc ')' của con phải)
    //   - Từ con phải (những cái chưa ghép với ')' của nó)
    res.open_needed = left_child.open_needed + right_child.open_needed - new_matches;

    // Số dấu ')' còn lại chưa ghép:
    //   - Từ con trái (những cái chưa ghép với '(' của nó)
    //   - Từ con phải (những cái chưa ghép với '(' của nó hoặc '(' của con trái)
    res.close_needed = left_child.close_needed + right_child.close_needed - new_matches;
    
    return res;
}

// Hàm xây dựng Segment Tree
// node: chỉ số nút hiện tại trong mảng tree
// start, end: phạm vi chỉ số của chuỗi S mà nút này đại diện
void build(int node, int start, int end) {
    if (start == end) { // Đây là nút lá (đại diện cho một ký tự)
        if (S[start] == '(') {
            tree[node] = NodeInfo(0, 1, 0); // Ký tự '(': 0 cặp, 1 mở, 0 đóng
        } else { // S[start] == ')'
            tree[node] = NodeInfo(0, 0, 1); // Ký tự ')': 0 cặp, 0 mở, 1 đóng
        }
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);         // Xây dựng con trái
        build(2 * node + 1, mid + 1, end); // Xây dựng con phải
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]); // Gộp kết quả
    }
}

// Hàm truy vấn
// node: chỉ số nút hiện tại
// start, end: phạm vi của nút hiện tại
// L, R: phạm vi truy vấn
NodeInfo query(int node, int start, int end, int L, int R) {
    // Trường hợp 1: Khoảng của nút hiện tại hoàn toàn nằm ngoài khoảng truy vấn
    if (end < L || start > R) {
        return NodeInfo(); // Trả về NodeInfo rỗng (không có cặp, không mở, không đóng)
    }

    // Trường hợp 2: Khoảng của nút hiện tại hoàn toàn nằm trong khoảng truy vấn
    if (L <= start && end <= R) {
        return tree[node]; // Trả về thông tin đã tính sẵn của nút này
    }

    // Trường hợp 3: Khoảng của nút hiện tại giao một phần với khoảng truy vấn
    int mid = (start + end) / 2;
    NodeInfo p1 = query(2 * node, start, mid, L, R);         // Truy vấn con trái
    NodeInfo p2 = query(2 * node + 1, mid + 1, end, L, R);   // Truy vấn con phải

    return combine(p1, p2); // Gộp kết quả từ hai truy vấn con
}

int main() {
    // Tối ưu hóa I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> S;
    // Chuỗi S được cấp chỉ số từ 0 theo mặc định, nhưng đề bài nói từ 1.
    // Để khớp với 1-based indexing của đề bài, mình sẽ bỏ qua S[0]
    // và dùng S[1]...S[N]. Hoặc đơn giản hơn là thêm một ký tự dummy vào đầu chuỗi.
    // Cách 1: Thêm dummy.
    S = " " + S; // Thêm một ký tự trống vào vị trí 0, để chỉ số từ 1 trở đi
    int N = S.length() - 1; // Độ dài thực tế của chuỗi (từ S[1] đến S[N])

    // Thay đổi kích thước mảng tree cho phù hợp (4*N là an toàn)
    tree.resize(4 * N + 1); 

    // Xây dựng Segment Tree
    build(1, 1, N);

    int M;
    std::cin >> M; // Đọc số lượng truy vấn

    for (int q = 0; q < M; ++q) {
        int L, R;
        std::cin >> L >> R; // Đọc L, R cho truy vấn
        NodeInfo result = query(1, 1, N, L, R);
        // Độ dài chuỗi con là dãy ngoặc đúng dài nhất = 2 * số cặp đã ghép
        std::cout << result.matched_pairs * 2 << "\n";
    }

    return 0;
}
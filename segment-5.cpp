// Trên trục tọa độ Ox vẽ lần lượt N điểm A[1], A[2], …, A[N].

// Có 2 loại truy vấn:

// 1 P: vẽ thêm điểm P lên trục tọa độ
// 2 L R: yêu cầu in ra khoảng cách gần nhất giữa 2 điểm trong đoạn [L, R]. Nếu như trong đoạn này có 1 điểm hoặc không có điểm nào, in ra -1.
// Input:

// Dòng đầu tiên chứa 2 số nguyên N và M (1 <= N, M <= 200 000).

// Dòng tiếp theo gồm N số nguyên A[i] (0 <= A[i] <= 10^9).

// M dòng tiếp theo, mỗi dòng một truy vấn (0 <= P, L, R <= 10^9).

// Output: 

// Với mỗi truy vấn loại 2, hãy in ra đáp án tìm được trên một dòng.

// Test ví dụ:

// Input:
// 2 4
// 2 6
// 1 3
// 2 2 2
// 2 2 3
// 2 3 6

// output
// -1
// 1
// 3

 
// input
// 3 3
// 2 4 8
// 2 2 8
// 1 2
// 2 2 8

// output
// 2
// 0

 

#include <iostream>
#include <vector>
#include <algorithm> // for std::sort, std::unique, std::lower_bound
#include <map>       // for mapping coordinates to compressed indices
#include <set>       // for collecting unique coordinates efficiently

// Dùng LLONG_MAX cho khoảng cách vô cực, để tránh tràn số và so sánh dễ dàng
#include <climits> 
const long long INF_DIST = LLONG_MAX;

// Cấu trúc thông tin cho mỗi nút Segment Tree
struct NodeInfo {
    long long min_dist;  // Khoảng cách nhỏ nhất giữa 2 điểm trong đoạn này
    long long leftmost;  // Tọa độ điểm xa nhất bên trái trong đoạn này
    long long rightmost; // Tọa độ điểm xa nhất bên phải trong đoạn này
    int count;           // Số lượng điểm trong đoạn này

    // Hàm tạo mặc định cho nút rỗng hoặc ngoài phạm vi
    NodeInfo() : min_dist(INF_DIST), leftmost(INF_DIST), rightmost(-INF_DIST), count(0) {}
};

// Mảng Segment Tree
std::vector<NodeInfo> tree;
// Mảng lưu trữ các tọa độ đã nén, theo thứ tự tăng dần
std::vector<long long> compressed_coords;
// Ánh xạ tọa độ thực sang chỉ số nén
std::map<long long, int> coord_to_idx;

// Hàm gộp thông tin từ hai nút con
NodeInfo combine(const NodeInfo& lc, const NodeInfo& rc) {
    NodeInfo res;

    res.count = lc.count + rc.count;

    // Khoảng cách nhỏ nhất từ con trái, con phải
    res.min_dist = std::min(lc.min_dist, rc.min_dist);

    // Khoảng cách mới có thể hình thành giữa điểm xa nhất bên phải của con trái
    // và điểm xa nhất bên trái của con phải (nếu cả hai con đều có điểm)
    if (lc.count > 0 && rc.count > 0) {
        res.min_dist = std::min(res.min_dist, rc.leftmost - lc.rightmost);
    }

    // leftmost của nút cha là leftmost của con trái (nếu có điểm), ngược lại là con phải
    res.leftmost = lc.leftmost;
    if (lc.count == 0) { // Nếu con trái rỗng, lấy leftmost từ con phải
        res.leftmost = rc.leftmost;
    }

    // rightmost của nút cha là rightmost của con phải (nếu có điểm), ngược lại là con trái
    res.rightmost = rc.rightmost;
    if (rc.count == 0) { // Nếu con phải rỗng, lấy rightmost từ con trái
        res.rightmost = lc.rightmost;
    }
    
    return res;
}

// Hàm cập nhật điểm
// idx_comp: chỉ số nén của tọa độ cần cập nhật
// val_coord: tọa độ thực của điểm
// change: +1 nếu thêm điểm, -1 nếu xóa điểm
void update(int node, int start, int end, int idx_comp, long long val_coord, int change) {
    if (start == end) { // Đến nút lá
        tree[node].count += change;
        if (tree[node].count > 0) { // Nếu có điểm tại đây
            tree[node].min_dist = INF_DIST; // Khoảng cách min cho 1 điểm là vô cực
            tree[node].leftmost = val_coord;
            tree[node].rightmost = val_coord;
        } else { // Nếu không còn điểm tại đây (đã bị xóa hết hoặc chưa có)
            tree[node].min_dist = INF_DIST;
            tree[node].leftmost = INF_DIST;
            tree[node].rightmost = -INF_DIST;
        }
    } else {
        int mid = (start + end) / 2;
        if (idx_comp <= mid) {
            update(2 * node, start, mid, idx_comp, val_coord, change);
        } else {
            update(2 * node + 1, mid + 1, end, idx_comp, val_coord, change);
        }
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
}

// Hàm truy vấn
NodeInfo query(int node, int start, int end, int L_comp, int R_comp) {
    if (end < L_comp || start > R_comp) { // Nút hoàn toàn nằm ngoài khoảng truy vấn
        return NodeInfo(); // Trả về NodeInfo rỗng
    }
    if (L_comp <= start && end <= R_comp) { // Nút hoàn toàn nằm trong khoảng truy vấn
        return tree[node];
    }

    int mid = (start + end) / 2;
    NodeInfo p1 = query(2 * node, start, mid, L_comp, R_comp);
    NodeInfo p2 = query(2 * node + 1, mid + 1, end, L_comp, R_comp);

    return combine(p1, p2);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, M;
    std::cin >> N >> M;

    std::vector<long long> initial_A(N);
    std::vector<std::pair<char, std::pair<long long, long long>>> queries(M);
    std::set<long long> unique_coords_set; // Dùng set để thu thập tọa độ duy nhất

    // Đọc các điểm A ban đầu và thu thập tọa độ
    for (int i = 0; i < N; ++i) {
        std::cin >> initial_A[i];
        unique_coords_set.insert(initial_A[i]);
    }

    // Đọc các truy vấn và thu thập tọa độ từ chúng
    for (int i = 0; i < M; ++i) {
        char type;
        long long p_or_l, r;
        std::cin >> type >> p_or_l;
        if (type == '1') { // Loại 1: Thêm điểm
            queries[i] = {'1', {p_or_l, -1}}; // -1 là placeholder
            unique_coords_set.insert(p_or_l);
        } else { // Loại 2: Truy vấn khoảng
            std::cin >> r;
            queries[i] = {'2', {p_or_l, r}};
            unique_coords_set.insert(p_or_l); // L và R cũng là tọa độ quan trọng
            unique_coords_set.insert(r);
        }
    }

    // Chuyển set sang vector để sắp xếp và nén tọa độ
    for (long long coord : unique_coords_set) {
        compressed_coords.push_back(coord);
    }
    // Gán chỉ số nén cho từng tọa độ
    for (int i = 0; i < compressed_coords.size(); ++i) {
        coord_to_idx[compressed_coords[i]] = i;
    }

    int num_unique_coords = compressed_coords.size();
    tree.resize(4 * num_unique_coords + 1); // Kích thước Segment Tree

    // Khởi tạo Segment Tree với các điểm A ban đầu
    for (long long coord : initial_A) {
        int idx_comp = coord_to_idx[coord];
        update(1, 0, num_unique_coords - 1, idx_comp, coord, 1); // Thêm điểm
    }

    // Xử lý các truy vấn
    for (int i = 0; i < M; ++i) {
        char type = queries[i].first;
        long long val1 = queries[i].second.first;
        long long val2 = queries[i].second.second;

        if (type == '1') { // Truy vấn loại 1: Thêm điểm P
            int idx_comp = coord_to_idx[val1];
            update(1, 0, num_unique_coords - 1, idx_comp, val1, 1); // Thêm điểm P
        } else { // Truy vấn loại 2: Tìm khoảng cách gần nhất trong [L, R]
            int L_comp = coord_to_idx[val1];
            int R_comp = coord_to_idx[val2];
            
            NodeInfo result = query(1, 0, num_unique_coords - 1, L_comp, R_comp);

            if (result.count < 2) { // Nếu ít hơn 2 điểm trong đoạn
                std::cout << -1 << "\n";
            } else {
                std::cout << result.min_dist << "\n";
            }
        }
    }

    return 0;
}
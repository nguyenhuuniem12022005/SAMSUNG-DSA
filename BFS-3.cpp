// Cho một bảng ký tự kích thước N x M, các hàng được đánh số từ 1 đến N (từ trên xuống), các cột được đánh số từ 1 đến M (từ trái sang phải). Ô nằm giao giữa hàng 𝑖 và cột 𝑗 là ô (𝑖, 𝑗). Mỗi ô chứa một ký tự thuộc tập [‘A’..’Z’, ‘*’].

// Nhiệm vụ của người chơi là: xuất phát từ một ô (𝑥, 𝑦) cần tìm đường đi tới một ô chứa ký tự ‘*’ theo quy tắc di chuyển như sau:

// - Chỉ được di chuyển sang các ô chung cạnh;

// - Nếu di chuyển sang ô mới chứa ký tự giống với ký tự trong ô hiện tại thì không mất chi phí di chuyển, còn nếu di chuyển sang ô mới chứa ký tự khác với ký tự trong ô hiện tại thì mất chi phí là 1.

// Cho bảng ký tự và ô (𝑥, 𝑦), hãy tính chi phí của đường đi từ ô (𝑥, 𝑦) đến một ô chứa ký tự ‘*’.

// Input:

// - Dòng đầu chứa ba số nguyên N, M, Q.

// - N dòng tiếp theo, mỗi dòng chứa một xâu độ dài M mô tả bảng ký tự.

// - Q dòng tiếp theo, mỗi dòng chứa hai số nguyên 𝑥, 𝑦.

// Output: 

// Gồm 𝑄 dòng, mỗi dòng ghi một số là chi phí của đường đi từ ô (𝑥, 𝑦) đến một ô chứa ký tự ‘*’.

// Giới hạn:

// Subtask 1 (50%): N, M ≤ 100, Q ≤ 3;

// Subtask 2 (25%): N, M ≤ 1000, Q ≤ 3;

// Subtask 3 (25%): N, M ≤ 1000, Q ≤ N x M.

// Test ví dụ:          

// Input

// Output

// 4 5 3

// *ACCB

// AACCB

// AACBA

// AAAAA

// 3 5

// 1 5

// 3 3

// OUTPUT
// 1

// 2

// 2


#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <utility>

using namespace std;

// Sử dụng một giá trị lớn để biểu thị vô cùng
const int INF = 1e9;

int main() {
    // Tăng tốc độ nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    cin >> n >> m >> q;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    // Mảng lưu chi phí nhỏ nhất từ mỗi ô đến ô '*' gần nhất
    vector<vector<int>> dist(n, vector<int>(m, INF));
    // Hàng đợi hai đầu cho thuật toán BFS 0-1
    deque<pair<int, int>> dq;

    // Khởi tạo các nguồn: tất cả các ô '*'
    // Đây là bước "đa nguồn" (multi-source)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '*') {
                dist[i][j] = 0;
                dq.push_front({i, j});
            }
        }
    }

    // Các hướng di chuyển: lên, xuống, trái, phải
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Bắt đầu thuật toán BFS 0-1
    while (!dq.empty()) {
        pair<int, int> current = dq.front();
        dq.pop_front();
        int r = current.first;
        int c = current.second;

        // Xét 4 ô hàng xóm
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // Kiểm tra xem ô hàng xóm có nằm trong bảng không
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                // Tính chi phí di chuyển
                int cost = (grid[r][c] == grid[nr][nc]) ? 0 : 1;

                // Nếu tìm thấy đường đi tốt hơn
                if (dist[r][c] + cost < dist[nr][nc]) {
                    dist[nr][nc] = dist[r][c] + cost;
                    
                    // Nếu chi phí là 1, đẩy vào cuối hàng đợi
                    if (cost == 1) {
                        dq.push_back({nr, nc});
                    } 
                    // Nếu chi phí là 0, đẩy vào đầu hàng đợi để ưu tiên xử lý
                    else {
                        dq.push_front({nr, nc});
                    }
                }
            }
        }
    }

    // Xử lý và trả lời các truy vấn
    for (int i = 0; i < q; ++i) {
        int r, c;
        cin >> r >> c;
        // Chuyển đổi từ tọa độ 1-based sang 0-based
        cout << dist[r - 1][c - 1] << "\n";
    }

    return 0;
}

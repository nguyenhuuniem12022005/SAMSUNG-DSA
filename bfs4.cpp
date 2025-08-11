// Trên cánh đồng có N hàng rào. Mỗi hàng rào được mô tả bằng một đoạn thẳng đứng hoặc ngang trong mặt phẳng hai chiều. Nếu hai hàng rào gặp nhau, chúng chỉ có thể giao nhau ở đầu mút của đoạn thẳng.

// Có M chú bò đang ăn cỏ trên cánh đồng. Mỗi chú bò được thể hiện bằng một điểm trên mặt phẳng tọa độ hai chiều. Input đảm bảo không có chú bò nào nằm trên đoạn thẳng đại diện cho các hàng rào, và không có hai chú bò có cùng tọa độ. Các chú bò có thể di chuyển tự do trong vùng bao quanh bởi các hàng rào và tạo thành bầy đàn.

// Bạn hãy xác định xem đàn bò nào có số lượng nhiều nhất?

// Input:

// Dòng đầu tiên là 2 số N, M (1 <= N, M <= 500).

// N dòng tiếp theo, mỗi dòng gồm 4 số nguyên Ax, Ay, Bx, By mô tả tọa độ của một hàng rào.

// M dòng tiếp theo, mỗi dòng gồm 2 số nguyên Cx, Cy mô tả tọa độ của một chú bò.

// Các tọa độ có giá trị trong khoảng từ 0 tới 10^6.

// Output: 

// In ra số lượng lớn nhất có thể của một đàn bò.

// Test ví dụ:

// Input:

// Output:

// 7 3

// 0 0 10 0

// 10 0 10 5

// 12 5 10 5

// 10 5 1 5

// 12 5 12 7

// 0 7 12 7

// 0 7 0 0

// 4 3

// 6 6

// 15 3

 
// output
// 2


#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

struct Fence {
    int x1, y1, x2, y2;
};

struct Cow {
    int x, y;
};

void bfs(int r, int c, int component_id, vector<vector<int>>& component_grid, const vector<vector<bool>>& is_fence) {
    int rows = component_grid.size();
    int cols = component_grid[0].size();

    if (r < 0 || r >= rows || c < 0 || c >= cols || is_fence[r][c] || component_grid[r][c] != 0) {
        return;
    }

    queue<pair<int, int>> q;
    q.push({r, c});
    component_grid[r][c] = component_id;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = curr.first + dr[i];
            int nc = curr.second + dc[i];

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !is_fence[nr][nc] && component_grid[nr][nc] == 0) {
                component_grid[nr][nc] = component_id;
                q.push({nr, nc});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    if (m == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<Fence> fences(n);
    vector<Cow> cows(m);
    set<int> x_set, y_set;

    for (int i = 0; i < n; ++i) {
        cin >> fences[i].x1 >> fences[i].y1 >> fences[i].x2 >> fences[i].y2;
        x_set.insert(fences[i].x1);
        x_set.insert(fences[i].x2);
        y_set.insert(fences[i].y1);
        y_set.insert(fences[i].y2);
    }

    for (int i = 0; i < m; ++i) {
        cin >> cows[i].x >> cows[i].y;
        x_set.insert(cows[i].x);
        y_set.insert(cows[i].y);
    }
    
    // Thêm một "hộp bao" để xử lý các trường hợp biên một cách an toàn
    x_set.insert(-1);
    x_set.insert(1000001);
    y_set.insert(-1);
    y_set.insert(1000001);

    vector<int> x_coords(x_set.begin(), x_set.end());
    vector<int> y_coords(y_set.begin(), y_set.end());

    map<int, int> x_map, y_map;
    for (int i = 0; i < x_coords.size(); ++i) {
        x_map[x_coords[i]] = i * 2;
    }
    for (int i = 0; i < y_coords.size(); ++i) {
        y_map[y_coords[i]] = i * 2;
    }

    int grid_rows = y_coords.size() * 2 - 1;
    int grid_cols = x_coords.size() * 2 - 1;
    
    vector<vector<bool>> is_fence(grid_rows, vector<bool>(grid_cols, false));

    for (const auto& f : fences) {
        int cx1 = x_map[f.x1];
        int cy1 = y_map[f.y1];
        int cx2 = x_map[f.x2];
        int cy2 = y_map[f.y2];

        if (cx1 == cx2) { // Hàng rào dọc
            for (int y = min(cy1, cy2); y <= max(cy1, cy2); ++y) {
                is_fence[y][cx1] = true;
            }
        } else { // Hàng rào ngang
            for (int x = min(cx1, cx2); x <= max(cx1, cx2); ++x) {
                is_fence[cy1][x] = true;
            }
        }
    }

    vector<vector<int>> component_grid(grid_rows, vector<int>(grid_cols, 0));
    int component_id = 1;
    for (int i = 0; i < grid_rows; ++i) {
        for (int j = 0; j < grid_cols; ++j) {
            if (!is_fence[i][j] && component_grid[i][j] == 0) {
                bfs(i, j, component_id, component_grid, is_fence);
                component_id++;
            }
        }
    }

    map<int, int> herd_sizes;
    for (const auto& cow : cows) {
        // Sử dụng upper_bound để tìm đúng khu vực cho bò
        auto it_x = upper_bound(x_coords.begin(), x_coords.end(), cow.x);
        auto it_y = upper_bound(y_coords.begin(), y_coords.end(), cow.y);
        
        int idx_x = distance(x_coords.begin(), it_x) - 1;
        int idx_y = distance(y_coords.begin(), it_y) - 1;

        // Khu vực (area) nằm ở các chỉ số lẻ
        int cow_grid_x = idx_x * 2 + 1;
        int cow_grid_y = idx_y * 2 + 1;

        int id = component_grid[cow_grid_y][cow_grid_x];
        herd_sizes[id]++;
    }

    int max_herd = 0;
    for (auto const& [id, size] : herd_sizes) {
        if (size > max_herd) {
            max_herd = size;
        }
    }

    cout << max_herd << endl;

    return 0;
}

#include <iostream>
#include <algorithm> // For std::max
#include <cmath>     // Not strictly needed for this logic, but good practice for math functions

// Hàm xác định giá trị tại ô (x, y) theo quy luật bảng Zigzag
long long get_value(long long x, long long y) {
    // 'diag_num' là chỉ số của đường chéo mà ô (x, y) thuộc về
    // Theo quy luật: đường chéo thứ i có các ô (x, y) thỏa mãn x + y - 1 = i
    long long diag_num = x + y - 1;

    // 'first_value_on_diag' là giá trị bắt đầu của đường chéo 'diag_num' (tại ô (diag_num, 1))
    // Công thức: A(i, 1) = i * (i - 1) / 2 + 1
    long long first_value_on_diag = diag_num * (diag_num - 1) / 2 + 1;

    // Giá trị tại ô (x, y) là giá trị bắt đầu của đường chéo cộng với vị trí của nó trên đường chéo (y - 1)
    // Ví dụ: (diag_num, 1) là vị trí thứ 1, (diag_num-1, 2) là vị trí thứ 2, ..., (1, diag_num) là vị trí thứ diag_num
    // Vị trí của ô (x, y) trên đường chéo được xác định bởi tọa độ y của nó.
    long long value = first_value_on_diag + (y - 1);

    return value;
}

// Hàm xác định hàng và cột của ô chứa giá trị z
std::pair<long long, long long> get_coordinates(long long z) {
    long long diag_num = 0; // Khởi tạo chỉ số đường chéo

    // Tìm chỉ số đường chéo 'diag_num' mà giá trị 'z' thuộc về
    // 'diag_num' là số nhỏ nhất sao cho giá trị cuối cùng trên đường chéo 'diag_num' >= z
    // Công thức giá trị cuối cùng trên đường chéo i: A(1, i) = i * (i + 1) / 2
    while (diag_num * (diag_num + 1) / 2 < z) {
        diag_num++;
    }

    // 'first_value_on_diag' là giá trị bắt đầu của đường chéo 'diag_num'
    // Công thức: A(i, 1) = i * (i - 1) / 2 + 1
    long long first_value_on_diag = diag_num * (diag_num - 1) / 2 + 1;

    // Xác định tọa độ y của ô chứa giá trị 'z'
    // 'y' là vị trí của 'z' trên đường chéo, tính từ giá trị bắt đầu của đường chéo
    // z = first_value_on_diag + (y - 1)  =>  y = z - first_value_on_diag + 1
    long long y_coord = z - first_value_on_diag + 1;

    // Xác định tọa độ x của ô chứa giá trị 'z'
    // Vì x + y - 1 = diag_num  =>  x + y = diag_num + 1  =>  x = diag_num + 1 - y
    long long x_coord = diag_num + 1 - y_coord;

    return {x_coord, y_coord};
}

int main() {
    std::ios_base::sync_with_stdio(false); // Tối ưu hóa nhập xuất
    std::cin.tie(NULL); // Ngắt kết nối cin và cout

    long long x, y;
    std::cin >> x >> y; // Đọc tọa độ x, y

    long long z;
    std::cin >> z; // Đọc giá trị z

    // Yêu cầu 1: Xác định giá trị ghi trên ô (x, y)
    std::cout << get_value(x, y) << std::endl;

    // Yêu cầu 2: Xác định hàng và cột của ô chứa giá trị z
    std::pair<long long, long long> coords = get_coordinates(z);
    std::cout << coords.first << " " << coords.second << std::endl;

    return 0;
}

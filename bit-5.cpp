// // SOLVE: https://oj.vnoi.info/problem/nuclear/editorial
// Hai nhà máy điện nguyên tử sẽ được xây dựng tại Byteland trong tương lai gần. Nhà máy điện thứ nhất có bán kính nguy hiểm là R1 và nhà máy điện thứ hai có bán kính nguy hiểm là R2. Tất cả các hộ gia đình cách nhà máy thứ nhất <= R1 km hoặc cách nhà máy thứ hai <=R2 km đều đang trong tình trạng nguy hiểm. Các gia đình nằm trong khu vực nguy hiểm này sẽ bắt buộc phải di chuyển chỗ ở.

// Hai nhà máy sẽ được xây dựng cũng như các hộ gia đình đều nằm trên mặt phẳng với hệ tọa độ Descartes vuông góc Oxy , trong đó khoảng cách giữa hai điểm (x1, y1) và (x2, y2) được tính theo công thức: sqrt((x1 – x2 )^2 + (y1 – y2 )^2).

// Nhiều phương án xây dựng được đưa ra với kích thước 2 nhà máy là khác nhau, gọi thông số bán kính nguy hiểm của hai nhà máy lần lượt là (R1, R2). Nhiệm vụ của bạn là xác định số lượng gia đình bắt buộc phải chuyển chỗ ở ứng với mỗi phương án.

// Input

// Dòng đầu tiên chứa số nguyên dương N là số hộ gia đình (1 <= N <= 200 000)
// N dòng tiếp, mỗi dòng chứa hai số nguyên là tọa độ (x[i], y[i]) của một hộ gia đình
// Dòng N+2 chứa 5 số nguyên ax, ay, bx, by và Q, lần lượt là tọa độ của nhà máy thứ nhất (ax, ay), tọa độ của nhà máy thứ hai (bx, by) và số lượng phương án Q (Q <= 200 000).
// Q dòng tiếp theo, dòng thứ j chứa hai số nguyên R1, R2 lần lượt là bán kính nguy hiểm của nhà máy thứ nhất và bán kính nguy hiểm của nhà máy thứ hai trong phương án thứ j.
// Tất cả tọa độ là số nguyên không âm và không lớn hơn 10^5.
// Output

// In ra Q dòng, dòng thứ j ghi một số nguyên duy nhất là số hộ gia đình buộc phải di chuyển chỗ ở nếu đề án thứ j được thực hiện.
// Test ví dụ:

// Input



// 11

// 95 75

// 27 6

// 93 5

// 124 13

// 34 49

// 65 61

// 81 49

// 77 33

// 110 50

// 91 22

// 110 25

// 57 42 97 36 2

// 31 25

// 25 25

 // Output

// 7

// 7

 
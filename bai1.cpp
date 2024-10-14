#include <iostream>

// Hàm hoán đổi giá trị giữa hai biến
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void sortColors(int colors[], int n) {
    int low = 0, mid = 0, high = n - 1;

    while (mid <= high) {
        if (colors[mid] == 0) { // Đỏ
            swap(colors[low], colors[mid]);
            low++;
            mid++;
        } else if (colors[mid] == 1) { // Trắng
            mid++;
        } else { // Xanh
            swap(colors[mid], colors[high]);
            high--;
        }
    }
}

int main() {
    int n;
    std::cout << "Nhập số lượng đối tượng: ";
    std::cin >> n;

    int colors[100]; // Giả sử tối đa 100 đối tượng
    std::cout << "Nhập các đối tượng (0: đỏ, 1: trắng, 2: xanh): ";
    for (int i = 0; i < n; ++i) {
        std::cin >> colors[i];
    }

    sortColors(colors, n);

    std::cout << "Kết quả sắp xếp: ";
    for (int i = 0; i < n; ++i) {
        std::cout << colors[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
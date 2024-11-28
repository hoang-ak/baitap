#include <iostream>
#include <string>
using namespace std;

// Cấu trúc Node trong hàng đợi (giỏ hàng của mỗi khách hàng)
struct Node {
    string tenKhachHang;  // Tên khách hàng
    float tongTien;       // Tổng tiền của giỏ hàng
    int soLuongA;         // Số lượng sản phẩm A
    Node* next;           // Con trỏ tới node tiếp theo trong hàng đợi

    // Khởi tạo node với thông tin khách hàng và giỏ hàng
    Node(string ten, float tien, int slA) : tenKhachHang(ten), tongTien(tien), soLuongA(slA), next(nullptr) {}
};

// Cấu trúc Hàng đợi
class Queue {
private:
    Node* front;  // Con trỏ tới node đầu tiên trong hàng đợi
    Node* rear;   // Con trỏ tới node cuối cùng trong hàng đợi

public:
    // Khởi tạo hàng đợi
    Queue() : front(nullptr), rear(nullptr) {}

    // Thêm một khách hàng vào hàng đợi (thêm giỏ hàng của họ)
    void enqueue(string ten, float tien, int slA) {
        Node* newNode = new Node(ten, tien, slA);
        if (rear) {
            rear->next = newNode;  // Nếu hàng đợi không rỗng, gán newNode vào cuối
        } else {
            front = newNode;  // Nếu hàng đợi rỗng, newNode là cả front và rear
        }
        rear = newNode;  // Cập nhật rear
    }

    // Loại bỏ khách hàng khỏi hàng đợi sau khi thanh toán
    void dequeue() {
        if (front) {
            Node* temp = front;  // Lưu trữ node đầu tiên
            front = front->next;  // Cập nhật front để trỏ tới node tiếp theo
            if (!front) {  // Nếu hàng đợi trống, cập nhật rear = nullptr
                rear = nullptr;
            }
            // In ra thông tin của khách hàng đã thanh toán
            cout << "Khach hang " << temp->tenKhachHang << " thanh toan xong!" << endl;
            cout << "San pham: " << temp->soLuongA << " San pham A, Tong tien: " << temp->tongTien << " VNĐ" << endl;
            delete temp;  // Giải phóng bộ nhớ cho khách hàng đã thanh toán
        } else {
            cout << "Hang doi rong, khong co khach hang!" << endl;
        }
    }

    // Tính tổng số tiền thu được từ tất cả khách hàng
    float tongTienThuDuoc() {
        float tongTien = 0;
        Node* current = front;
        while (current) {
            tongTien += current->tongTien;  // Cộng dồn tổng tiền từ tất cả khách hàng
            current = current->next;       // Di chuyển đến khách hàng tiếp theo
        }
        return tongTien;
    }

    // Tính tổng số lượng sản phẩm A đã bán
    int soLuongSanPhamA() {
        int soLuong = 0;
        Node* current = front;
        while (current) {
            soLuong += current->soLuongA;  // Cộng dồn số lượng sản phẩm A
            current = current->next;       // Di chuyển đến khách hàng tiếp theo
        }
        return soLuong;
    }

    // Kiểm tra xem hàng đợi có rỗng hay không
    bool isEmpty() {
        return front == nullptr;
    }
};

// Hàm main để kiểm tra các thao tác với hàng đợi
int main() {
    Queue q;

    // Thêm khách hàng vào hàng đợi với thông tin giỏ hàng
    q.enqueue("A", 150, 3);  // Khách hàng 1, giỏ hàng trị giá 150, mua 3 sản phẩm A
    q.enqueue("B", 200, 5);    // Khách hàng 2, giỏ hàng trị giá 200, mua 5 sản phẩm A
    q.enqueue("C", 50, 2);       // Khách hàng 3, giỏ hàng trị giá 50, mua 2 sản phẩm A

    // Tính tổng số tiền thu được từ tất cả khách hàng trong hàng đợi
    cout << "Tong tien thu duoc trong mot phien lam viec: " << q.tongTienThuDuoc() << " VNĐ" << endl;

    // Tính tổng số lượng sản phẩm A đã bán
    cout << "Tong so luong san pham A da ban: " << q.soLuongSanPhamA() << endl;

    // Loại bỏ khách hàng khỏi hàng đợi sau khi thanh toán
    cout << "\nKhach hang thanh toan xong:" << endl;
    q.dequeue();  // Khách hàng đầu tiên thanh toán xong

    // Kiểm tra nếu còn khách hàng trong hàng đợi và loại bỏ tiếp
    if (!q.isEmpty()) {
        cout << "\nKhach hang thanh toan tiep theo:" << endl;
        q.dequeue();  // Khách hàng thứ 2 thanh toán xong
    }

    // Kiểm tra và loại bỏ khách hàng còn lại
    if (!q.isEmpty()) {
        cout << "\nKhach hang thanh toan tiep theo:" << endl;
        q.dequeue();  // Khách hàng cuối cùng thanh toán xong
    }

    return 0;
}

#include<bits/stdc++.h>
using namespace std;


////Khai báo lớp Node
// Lớp đại diện cho một nút trong cây
class Node {
public:
    string value; // Giá trị của nút (toán tử hoặc toán hạng)
    Node* left;   // Con trái
    Node* right;  // Con phải

    // Constructor
    Node(string val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};




//// Hàm khởi tạo cây
class ExpressionTree {
private:
    Node* root; // Gốc của cây

public:
    // Constructor
    ExpressionTree() {
        root = nullptr;
    }

    // Kiểm tra cây rỗng
    bool isEmpty() {
        return root == nullptr;
    }

    // Thêm một phần tử vào cây (hàm tạo nút mới)
    Node* insert(string value, Node* left = nullptr, Node* right = nullptr) {
        Node* newNode = new Node(value);
        newNode->left = left;
        newNode->right = right;
        return newNode;
    }

    // Đặt gốc cho cây
    void setRoot(Node* node) {
        root = node;
    }

    // Duyệt cây theo trung tố (In-order)
    void inorder(Node* node) {
        if (node) {
            if (node->left) cout << "("; // Mở ngoặc
            inorder(node->left);
            cout << node->value << " ";
            inorder(node->right);
            if (node->right) cout << ")"; // Đóng ngoặc
        }
    }

    // Duyệt cây theo tiền tố (Pre-order)
    void preorder(Node* node) {
        if (node) {
            cout << node->value << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    // Duyệt cây theo hậu tố (Post-order)
    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->value << " ";
        }
    }

    // Truy cập gốc cây
    Node* getRoot() {
        return root;
    }
};




/// Xây dựng cây biểu thức 
int main() {
    ExpressionTree tree;

    // Tạo các nút từ dưới lên
    Node* sqrt_e = tree.insert("sqrt", nullptr, tree.insert("e"));
    Node* h_minus_f = tree.insert("-", tree.insert("h"), tree.insert("f"));
    Node* term3 = tree.insert("*", h_minus_f, sqrt_e);

    Node* b_c6 = tree.insert("^", tree.insert("c"), tree.insert("6"));
    Node* b_c6_div_d = tree.insert("/", tree.insert("*", tree.insert("b"), b_c6), tree.insert("d"));
    Node* a_times_5 = tree.insert("*", tree.insert("a"), tree.insert("5"));

    Node* term1_minus_term2 = tree.insert("-", a_times_5, b_c6_div_d);

    // Gốc của cây là tổng của term1_minus_term2 và term3
    Node* root = tree.insert("+", term1_minus_term2, term3);
    tree.setRoot(root);

    // In kết quả theo các cách duyệt
    cout << "Trung tố (In-order): ";
    tree.inorder(tree.getRoot());
    cout << endl;

    cout << "Tiền tố (Pre-order): ";
    tree.preorder(tree.getRoot());
    cout << endl;

    cout << "Hậu tố (Post-order): ";
    tree.postorder(tree.getRoot());
    cout << endl;

    return 0;
}













































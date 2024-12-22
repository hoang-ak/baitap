#include <iostream>
#include <algorithm>
using namespace std;

// Cấu trúc node của cây AVL
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Hàm lấy chiều cao của một node
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Hàm lấy hệ số cân bằng của một node
int getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Hàm xoay phải đơn giản
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // Node mới sau khi xoay phải
}

// Hàm xoay trái đơn giản
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // Node mới sau khi xoay trái
}

// Hàm chèn một node mới vào cây AVL
Node* insertNode(Node* root, int key) {
    if (!root) // Nếu cây rỗng, tạo node mới
        return new Node(key);

    if (key < root->key) // Chèn vào cây con bên trái
        root->left = insertNode(root->left, key);
    else if (key > root->key) // Chèn vào cây con bên phải
        root->right = insertNode(root->right, key);
    else // Không cho phép các giá trị trùng nhau
        return root;

    // Cập nhật chiều cao của node hiện tại
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Kiểm tra hệ số cân bằng
    int balanceFactor = getBalanceFactor(root);

    // Trường hợp mất cân bằng
    if (balanceFactor > 1 && key < root->left->key) // Mất cân bằng trái-trái
        return rotateRight(root);

    if (balanceFactor < -1 && key > root->right->key) // Mất cân bằng phải-phải
        return rotateLeft(root);

    if (balanceFactor > 1 && key > root->left->key) { // Mất cân bằng trái-phải
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balanceFactor < -1 && key < root->right->key) { // Mất cân bằng phải-trái
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root; // Trả về root sau khi đã cân bằng
}

// Hàm duyệt cây theo thứ tự in-order
void inOrderTraversal(Node* root) {
    if (root) {
        inOrderTraversal(root->left);
        cout << root->key << " ";
        inOrderTraversal(root->right);
    }
}

// Hàm duyệt cây theo thứ tự pre-order
void preOrderTraversal(Node* root) {
    if (root) {
        cout << root->key << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Hàm in cây AVL bằng cách duyệt in-order và pre-order
void printAVL(Node* root) {
    cout << "In-order Traversal: ";
    inOrderTraversal(root); // In cây theo thứ tự in-order
    cout << endl;

    cout << "Pre-order Traversal: ";
    preOrderTraversal(root); // In cây theo thứ tự pre-order
    cout << endl;
}

int main() {
    Node* root = nullptr;
    int n;

    cout << "Enter the number of elements: ";
    cin >> n; // Nhập số lượng phần tử

    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        int key;
        cin >> key; // Nhập từng phần tử
        root = insertNode(root, key); // Chèn phần tử vào cây
    }

    printAVL(root); // In cây AVL

    return 0;
}

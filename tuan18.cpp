#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct GraphAdjMatrix {
    int vertices;
    vector<vector<int>> adj_matrix;

    GraphAdjMatrix(int v) : vertices(v), adj_matrix(v, vector<int>(v, 0)) {}

    // Thêm cạnh vào đồ thị
    void add_edge(int u, int v) {
        if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
            adj_matrix[u][v] = 1;
            adj_matrix[v][u] = 1; // Xóa dòng này nếu là đồ thị có hướng
        } else {
            cout << "Canh khong hop le!" << endl;
        }
    }

    // Hiển thị ma trận kề
    void display() {
        cout << "Ma tran ke:" << endl;
        for (const auto& row : adj_matrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};

struct GraphAdjList {
    int vertices;
    map<int, vector<int>> adj_list;

    GraphAdjList(int v) : vertices(v) {}

    // Thêm cạnh vào đồ thị
    void add_edge(int u, int v) {
        if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
            adj_list[u].push_back(v);
            adj_list[v].push_back(u); // Xóa dòng này nếu là đồ thị có hướng
        } else {
            cout << "Canh khong hop le!" << endl;
        }
    }

    // Hiển thị danh sách kề
    void display() {
        cout << "Danh sach ke:" << endl;
        for (const auto& pair : adj_list) {
            cout << pair.first << ": ";
            for (int val : pair.second) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "Bieu dien do thi bang ma tran ke" << endl;
    int v;
    cout << "Nhap so dinh: ";
    cin >> v;
    GraphAdjMatrix g_matrix(v);
    int e;
    cout << "Nhap so canh: ";
    cin >> e;
    for (int i = 0; i < e; ++i) {
        int u, v;
        cout << "Nhap canh (u v): ";
        cin >> u >> v;
        g_matrix.add_edge(u, v);
    }
    g_matrix.display();

    cout << "\nBieu dien do thi bang danh sach ke" << endl;
    GraphAdjList g_list(v);
    for (int i = 0; i < e; ++i) {
        int u, v;
        cout << "Nhap canh (u v): ";
        cin >> u >> v;
        g_list.add_edge(u, v);
    }
    g_list.display();

    return 0;
}

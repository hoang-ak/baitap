#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for max_element

using namespace std;

struct TreeNode {
    string title;          // Tên của mục
    int pages;             // Số trang của mục
    vector<TreeNode*> children; // Danh sách các mục con

    TreeNode(string t, int p) : title(t), pages(p) {}
};

// Hàm thêm mục con vào một node
void addChild(TreeNode* parent, TreeNode* child) {
    parent->children.push_back(child);
}

// 1. Xác định số chương của cuốn sách (giả định chương là node gốc có các mục con)
int countChapters(TreeNode* root) {
    return root->children.size();
}

// 2. Tìm chương dài nhất của cuốn sách (dựa trên tổng số trang của mỗi chương)
TreeNode* findLongestChapter(TreeNode* root) {
    TreeNode* longestChapter = nullptr;
    int maxPages = 0;

    for (auto chapter : root->children) {
        int chapterPages = chapter->pages;
        for (auto section : chapter->children) {
            chapterPages += section->pages;
            for (auto subsection : section->children) {
                chapterPages += subsection->pages;
            }
        }

        if (chapterPages > maxPages) {
            maxPages = chapterPages;
            longestChapter = chapter;
        }
    }

    return longestChapter;
}

// 3. Tìm một mục và xoá mục đó (bao gồm cả mục con nếu có)
bool findAndRemove(TreeNode* parent, const string& titleToDelete) {
    for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
        if ((*it)->title == titleToDelete) {
            delete *it; // Giải phóng bộ nhớ của node bị xóa
            parent->children.erase(it);
            return true;
        }
        if (findAndRemove(*it, titleToDelete)) {
            return true;
        }
    }
    return false;
}

// Hàm in cây để kiểm tra
void printTree(TreeNode* root, int depth = 0) {
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << root->title << " (" << root->pages << " pages)\n";
    for (auto child : root->children) {
        printTree(child, depth + 1);
    }
}

int main() {
    // Tạo một cây mẫu
    TreeNode* book = new TreeNode("Book Title", 0);

    TreeNode* chapter1 = new TreeNode("Chapter 1", 10);
    TreeNode* section1_1 = new TreeNode("Section 1.1", 5);
    TreeNode* subsection1_1_1 = new TreeNode("Subsection 1.1.1", 3);
    addChild(section1_1, subsection1_1_1);
    addChild(chapter1, section1_1);
    addChild(book, chapter1);

    TreeNode* chapter2 = new TreeNode("Chapter 2", 15);
    TreeNode* section2_1 = new TreeNode("Section 2.1", 7);
    addChild(chapter2, section2_1);
    addChild(book, chapter2);

    // 1. Đếm số chương
    cout << "Number of chapters: " << countChapters(book) << endl;

    // 2. Tìm chương dài nhất
    TreeNode* longest = findLongestChapter(book);
    if (longest) {
        cout << "Longest chapter: " << longest->title << endl;
    }

    // 3. Xoá mục
    cout << "Before deletion:\n";
    printTree(book);
    if (findAndRemove(book, "Section 2.1")) {
        cout << "After deletion:\n";
        printTree(book);
    } else {
        cout << "Section not found!\n";
    }

    // Dọn dẹp bộ nhớ
    delete book;
    return 0;
}

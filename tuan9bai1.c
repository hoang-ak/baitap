//1.Khai bao cau truc danh sach liên ket don  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct FileNode {
    char fileName[100];        
    long fileSize;             
    time_t timestamp;          
    struct FileNode* next;     
} FileNode;


FileNode* createFileNode(const char* name, long size, time_t time) {
    FileNode* newNode = (FileNode*)malloc(sizeof(FileNode));
    strcpy(newNode->fileName, name);
    newNode->fileSize = size;
    newNode->timestamp = time;
    newNode->next = NULL;
    return newNode;
}
//2. Chen vao file danh sach theo trat tu thoi gian 
void insertFile(FileNode** head, FileNode* newFile) {
    if (*head == NULL || (*head)->timestamp > newFile->timestamp) {
        newFile->next = *head;
        *head = newFile;
    } else {
        FileNode* current = *head;
        while (current->next != NULL && current->next->timestamp < newFile->timestamp) {
            current = current->next;
        }
        newFile->next = current->next;
        current->next = newFile;
    }
}
//3.Tinh tong kich thuoc cua file trong danh sach
long calculateTotalSize(FileNode* head) {
    long totalSize = 0;
    while (head != NULL) {
        totalSize += head->fileSize;
        head = head->next;
    }
    return totalSize;
}
//4.Loai bo file kich thuoc nho nhat
void removeSmallestFile(FileNode** head) {
    if (*head == NULL) return;

    FileNode *current = *head, *prev = NULL;
    FileNode *smallest = *head, *smallestPrev = NULL;

    while (current != NULL) {
        if (current->fileSize < smallest->fileSize) {
            smallest = current;
            smallestPrev = prev;
        }
        prev = current;
        current = current->next;
    }

   
    if (smallestPrev == NULL) {
        *head = smallest->next;  
    } else {
        smallestPrev->next = smallest->next;
    }
    free(smallest);
}
//5.Ham in danh sach file
void printFiles(FileNode* head) {
    while (head != NULL) {
        printf("File: %s, Size: %ld bytes, Time: %s", head->fileName, head->fileSize, ctime(&head->timestamp));
        head = head->next;
    }
}
//6.Ham chinh
int main() {
    FileNode* fileList = NULL;

  
    insertFile(&fileList, createFileNode("file1.txt", 500, time(NULL) - 3600));
    insertFile(&fileList, createFileNode("file2.txt", 200, time(NULL) - 7200));
    insertFile(&fileList, createFileNode("file3.txt", 800, time(NULL)));

    printf("Danh sach cac file:\n");
    printFiles(fileList);

    
    long totalSize = calculateTotalSize(fileList);
    printf("\nTinh kich thuoc: %ld bytes\n", totalSize);

    
    long usbCapacity = 32L * 1024 * 1024 * 1024; 
    while (calculateTotalSize(fileList) > usbCapacity) {
        removeSmallestFile(&fileList);
    }

    printf("\nDanh sach file sau khi loc:\n");
    printFiles(fileList);

    
    while (fileList != NULL) {
        FileNode* temp = fileList;
        fileList = fileList->next;
        free(temp);
    }

    return 0;
}
//1.Khai bao cau truc danh sach lien ket don
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WordNode {
    char word[50];            
    int count;                
    struct WordNode* next;    
} WordNode;


WordNode* createWordNode(const char* word) {
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
    strcpy(newNode->word, word);
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}
//2.Them tu vao danh sach lien ket
void addWord(WordNode** head, const char* word) {
    WordNode* current = *head;
    WordNode* prev = NULL;

    
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            current->count++; 
            return;
        }
        prev = current;
        current = current->next;
    }


    WordNode* newNode = createWordNode(word);
    if (prev == NULL) {
        *head = newNode; 
    } else {
        prev->next = newNode;
    }
}
//3.Xac dinh tu xuat hien nhieu nhat
void findMostFrequentWord(WordNode* head) {
    if (head == NULL) {
        printf("Danh sach rong!/n");
        return;
    }

    WordNode* mostFrequent = head;
    while (head != NULL) {
        if (head->count > mostFrequent->count) {
            mostFrequent = head;
        }
        head = head->next;
    }

    printf("Tu xuat hien nhieu nhat: '%s' voi  %d lan\n", mostFrequent->word, mostFrequent->count);
}
//4.Loai bo tu lay
void removeDuplicateWords(WordNode** head) {
    WordNode* current = *head;
    WordNode* prev = NULL;

    while (current != NULL) {
       
        char firstPart[50], secondPart[50];
        if (sscanf(current->word, "%s %s", firstPart, secondPart) == 2 && strcmp(firstPart, secondPart) == 0) {
            printf("Loai bo tu lay : '%s'\n", current->word);

            // Xóa node
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            WordNode* temp = current;
            current = current->next;
            free(temp);
            continue;
        }

        prev = current;
        current = current->next;
    }
}
//5.Dem so tu vung xuat hien trong cau
int countUniqueWords(WordNode* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}
//6.Ham in danh sach
void printWordList(WordNode* head) {
    while (head != NULL) {
        printf("Tu : '%s', So lan xuat hien : %d\n", head->word, head->count);
        head = head->next;
    }
}
//7.Ham chinh 
int main() {
    WordNode* wordList = NULL;

  
    char sentence[] = "xanh do vang vang xanh xanh:";
    printf("Câu goc: %s\n", sentence);

 
    char* token = strtok(sentence, " ");
    while (token != NULL) {
        addWord(&wordList, token);
        token = strtok(NULL, " ");
    }


    printf("\nDanh sách tu :\n");
    printWordList(wordList);

    
    printf("\n");
    findMostFrequentWord(wordList);


    printf("\nLoai bo tu  láy:\n");
    removeDuplicateWords(&wordList);

    
    printf("\nDanh sach tu sau khi loai bo tu lay :\n");
    printWordList(wordList);


    int uniqueWords = countUniqueWords(wordList);
    printf("\nSo tu vung xuat hien trong cau : %d\n", uniqueWords);


    while (wordList != NULL) {
        WordNode* temp = wordList;
        wordList = wordList->next;
        free(temp);
    }

    return 0;
}
 
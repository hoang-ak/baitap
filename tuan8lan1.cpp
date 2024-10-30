#include<iostream>
using namespace std;

struct Node{
    int heso; //he so cua hang tu
    int somu; // so mu cua hang tu
    Node* link; // con tro toi hang tu tiep theo
};

struct ListDT{
    Node* first, *last; //con tro dau danh sach, con tro cuoi danh sach
};

void initDT(ListDT *l){
    l->first = l->last = NULL; //khoi tao danh sach da thuc
} 

//tao mot Node moi voi he so va so mu
Node* callNode(int hs, int sm){
    Node*p = new Node;
    if (p==NULL) return NULL;
    p->heso = hs;
    p->somu = sm;
    p->link = NULL;
    return p;
}

//gan Node p vao danh sach
void addNode(ListDT* lDT, Node* p){
    if (lDT->first == NULL){ //danh sach rong
    lDT->first = lDT->last =p;
    } else{
        lDT->last->link = p;// gan dia chi Node cuoi bang p
        lDT->last = p; // chuyen p thanh Node cuoi
    }
}

// Them Node voi he so va so mu cho truoc
void attachNode(ListDT* lDT, int hs, int sm){
    Node* pDT = callNode(hs,sm);
    if (pDT==NULL) return;
    addNode(lDT,pDT);
}

//tao da thuc bang cach nhap tu ban phim
void taoDT(ListDT* lDT){
   int hs;
   int sm;
   int i=0;
   cout<< "-Bat dau nhap da thuc (nhap he so 0 de ket thuc):" << endl;
   do
   {
    i++;
    cout<< "Nhap so phan tu thu" << i << endl;
    cout<< "\nNhap he so =";
    cin>>hs;
    if (hs==0) break;
    cout<< "\nNhap so mu =";
    cin>> sm;
    attachNode(lDT,hs,sm);
   } while (hs !=0);
   cout << "ket thuc nhap" <<endl;
}

// in da thuc
void inDT(ListDT* lDT){
    Node* p = lDT->first;
    cout<< "f(x)=";
    bool firstTerm= true;
    while (p != NULL){
        if (p->heso !=0){ //chi in neu he so khac 0
        if (!firstTerm && p->heso >0){
            cout<< "+";
        } else if (p->heso <0){
            cout << "-";
            if (!firstTerm) cout<< -p->heso;
            else cout << p->heso;
        } else {
            cout << p->heso;
        }
        if (p->somu >1){
            cout<< "* x^" << p->somu;
        } else if (p->somu == 1){
            cout << "* x";
        }

        firstTerm = false;

        }

        p = p->link;

    }
    
    if (firstTerm) cout << "0";
    cout<<endl;
}

// giai phong bo nho cua danh sach
void giaiphongDT(ListDT* lDT){
    Node* p = lDT->first;
    while (p!=NULL){
        Node* temp = p;
        p = p->link;
        delete temp;
    }
    lDT->first = lDT->last = NULL;
}


int main(){
    ListDT DT1;
    initDT(&DT1);
    taoDT(&DT1);
    inDT(&DT1);
    giaiphongDT(&DT1); // giai phong bo nho sau khi su dung
    return 0;
}






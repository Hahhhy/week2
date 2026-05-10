//https://www.luogu.com.cn/problem/P3370
#include<bits/stdc++.h>
using namespace std;


const int CAPACITY=7;

struct Node{
    string key;
    string value;
    Node *next;
};


struct HashTable{
    Node *buckets[CAPACITY];
    int size;
};

void initHashTable(HashTable * ht){
    ht->size=0;
    for(int i=0;i<CAPACITY;++i){
        ht->buckets[i]=nullptr;
    }
}

int hashFunc(string key){
    int hashValue=0;
    for(int i=0;i<key.length();i++){
        hashValue=hashValue*31+key[i];
    }
    return (hashValue%CAPACITY+CAPACITY)%CAPACITY;
}

void put(HashTable* ht,string key,string value){
    int index=hashFunc(key);
    Node* current=ht->buckets[index];
    while(current!=nullptr){
        if(current->key==key){
            current->value=value;
            return;
        }
        current=current->next;
    }

    Node *newNode=new Node;
    newNode->key=key;
    newNode->value=value;
    newNode->next=ht->buckets[index];

    ht->buckets[index]=newNode;
    ht->size++;
}


bool get(HashTable* ht,string key,string& outValue){
    int index=hashFunc(key);
    Node* current=ht->buckets[index];

    while(current!=nullptr){
        if(current->key==key){
            outValue=current->value;
            return true;
        }
        current=current->next;
    }
    return false;
}

bool remove(HashTable*ht,string key){
    int index=hashFunc(key);

    Node* current=ht->buckets[index];
    Node* prev=nullptr;

    while(current!=nullptr){
        if(current->key==key){
            if(prev==nullptr){
                ht->buckets[index]=current->next;
            }else{
                prev->next=current->next;
            }
            delete current;
            ht->size--;
            return true;
        }
        prev=current;
        current=current->next;
    }
    return false;
}


// 8. 销毁哈希表 (防止内存泄漏)
void destroyHashTable(HashTable* ht) {
    for (int i = 0; i < CAPACITY; i++) {
        Node* current = ht->buckets[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        ht->buckets[i] = nullptr;
    }
    ht->size = 0;
}


int main(){
    // 声明一个哈希表变量，并初始化
    HashTable myTable;
    initHashTable(&myTable);

    // 各种操作都需要把哈希表的地址 (&myTable) 传进去
    put(&myTable, "apple", "苹果");
    put(&myTable, "banana", "香蕉");

    string val;
    if (get(&myTable, "apple", val)) {
        cout << "查询 apple: " << val << endl;
    }

    remove(&myTable, "apple");
    
    if (!get(&myTable, "apple", val)) {
        cout << "apple 已被删除" << endl;
    }

    // 用完记得销毁
    destroyHashTable(&myTable);

    return 0;
}







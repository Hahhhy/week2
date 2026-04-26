//P11615 【模板】哈希表 
#include<bits/stdc++.h>

using namespace std;

// 定义哈希表的容量 
const int CAPACITY = 7; 

// 定义链表节点 , 键值对 + 指向下一个节点的指针
struct Node {
    string key;
    string value;
    Node* next;
};

//  定义哈希表结构体
struct HashTable {
    Node* buckets[CAPACITY]; // 存着头指针
    int size;                // 当前元素个数
};

//初始化哈希表
void initHashTable(HashTable* ht) {
    ht->size = 0;
    for (int i = 0; i < CAPACITY; i++) {
        ht->buckets[i] = nullptr; // 把所有链表头指针置空
    }
}

//哈希函数
int hashFunc(string key) {
    int hashValue = 0;
    for (int i = 0; i < key.length(); i++) {
        hashValue += key[i];
    }
    return hashValue % CAPACITY;
}

//增/改 
void put(HashTable* ht, string key, string value) {
    int index = hashFunc(key);
    Node* current = ht->buckets[index];

    // 先找找有没有相同的 key
    while (current != nullptr) {
        if (current->key == key) {
            current->value = value; // 找到就修改
            return;
        }
        current = current->next;
    }

    // 没找到，新建节点 (头插法)
    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;
    newNode->next = ht->buckets[index];
    
    ht->buckets[index] = newNode;
    ht->size++;
}

// 6. 查 (Get)
bool get(HashTable* ht, string key, string& outValue) {
    int index = hashFunc(key);
    Node* current = ht->buckets[index];

    while (current != nullptr) {
        if (current->key == key) {
            outValue = current->value;
            return true;
        }
        current = current->next;
    }
    return false;
}

// 删 (Remove)
bool remove(HashTable* ht, string key) {
    int index = hashFunc(key);
    
    Node* current = ht->buckets[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) { // 删的是头节点
                ht->buckets[index] = current->next;
            } else {               // 删的是中间或尾部节点
                prev->next = current->next;
            }
            delete current; // 释放内存
            ht->size--;
            return true;
        }
        prev = current;
        current = current->next;
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

int main() {
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
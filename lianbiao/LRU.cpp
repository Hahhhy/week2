#include<bits/stdc++.h>
using namespace std;

class LRUCache{
    struct Node{
        int key,val;
        Node *prev,*next;
        Node(int k,int v) : key(k), val(v), prev(NULL),next(NULL){}
    };

    int cap;
    unordered_map<int,Node*> mp;
    Node *head,*tail;

    void insertHead(Node *p){
        p->next=head->next;
        p->prev=head;
        if(head->next!=NULL)
            head->next->prev=p;
        head->next=p;
    }

    void remove(Node *p){
        p->prev->next=p->next;
        p->next->prev=p->prev;
    }

public:
    LRUCache(int capacity) : cap(capacity) {
        head=new Node(-1,-1);
        tail=new Node(-1,-1);
        head->next=tail;
        tail->prev=head;
    }

    int get(int key){
        if(mp.find(key)==mp.end()) return -1;
        Node *p=mp[key];
        remove(p);
        insertHead(p);
        return p->val;
    }

    void put(int key,int value){
        if(mp.find(key)!=mp.end()){
            Node *p=mp[key];
            p->val=value;
            remove(p);
            insertHead(p);
        }else{
            if((int)mp.size()==cap){
                Node *lru=tail->prev;
                remove(lru);
                mp.erase(lru->key);
                delete lru;
            }
            Node *p=new Node(key,value);
            insertHead(p);
            mp[key]=p;
        }
    }

};


int main() {
    LRUCache* cache = new LRUCache(2);

    cache->put(1, 1);  // {1=1}
    cache->put(2, 2);  // {1=1, 2=2}

    assert(cache->get(1) == 1);   // 返回 1，1 移到头部
    cache->put(3, 3);             // 淘汰 2，{1=1, 3=3}
    assert(cache->get(2) == -1);  // 2 已淘汰
    cache->put(4, 4);             // 淘汰 1，{3=3, 4=4}
    assert(cache->get(1) == -1);  // 1 已淘汰
    assert(cache->get(3) == 3);
    assert(cache->get(4) == 4);
    cout << "示例测试通过" << endl;

    // 测试更新已有 key
    LRUCache* cache2 = new LRUCache(2);
    cache2->put(1, 1);
    cache2->put(1, 100);           // 更新 key=1 的值
    assert(cache2->get(1) == 100); // 应该返回新值
    cout << "更新测试通过" << endl;

    // 测试容量为 1
    LRUCache* cache3 = new LRUCache(1);
    cache3->put(1, 1);
    cache3->put(2, 2);             // 淘汰 1
    assert(cache3->get(1) == -1);
    assert(cache3->get(2) == 2);
    cout << "容量1测试通过" << endl;

    // 测试 get 之后影响淘汰顺序
    LRUCache* cache4 = new LRUCache(2);
    cache4->put(1, 1);
    cache4->put(2, 2);
    cache4->get(1);    // 访问 1，链表变为 [1, 2]，尾部是 2
    cache4->put(3, 3); // 淘汰尾部的 2
    assert(cache4->get(2) == -1);
    assert(cache4->get(1) == 1);
    assert(cache4->get(3) == 3);
    cout << "访问顺序测试通过" << endl;

    cout << "所有测试通过！" << endl;
    return 0;
}
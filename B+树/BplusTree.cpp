#include<bits/stdc++.h>
using namespace std;

const int ORDER = 3; 

struct Node{
    bool is_leaf;
    vector<int> keys;
    vector<Node*> children;
    
    vector<string> vals;
    vector<bool> is_deleted; // 惰性删除标记
    Node* next = nullptr;    // 叶子节点链表指针，用于区间搜索
    
    explicit Node(bool leaf) : is_leaf(leaf) {}
};

class BplusTree{
private:
    Node* root;

    // 节点分裂
    void split_child(Node* parent, int idx){
        Node* old = parent->children[idx];
        Node* nw = new Node(old->is_leaf);
        int mid = old->keys.size() / 2;

        if(old->is_leaf){
            nw->keys.assign(old->keys.begin() + mid, old->keys.end());
            nw->vals.assign(old->vals.begin() + mid, old->vals.end());
            nw->is_deleted.assign(old->is_deleted.begin() + mid, old->is_deleted.end());
            
            old->keys.resize(mid);
            old->vals.resize(mid);
            old->is_deleted.resize(mid);
            
            nw->next = old->next;
            old->next = nw;
            
            parent->keys.insert(parent->keys.begin() + idx, nw->keys[0]);
        }else{
            int push_up_key = old->keys[mid];
            
            nw->keys.assign(old->keys.begin() + mid + 1, old->keys.end());
            nw->children.assign(old->children.begin() + mid + 1, old->children.end());
            
            old->keys.resize(mid);
            old->children.resize(mid + 1);
            
            parent->keys.insert(parent->keys.begin() + idx, push_up_key);
        }
        parent->children.insert(parent->children.begin() + idx + 1, nw);
    }

    void insert_non_full(Node* cur, int key, string val){
        if(cur->is_leaf){
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            int idx = distance(cur->keys.begin(), it);
            
            if(idx > 0 && cur->keys[idx - 1] == key){
                cur->vals[idx - 1] = val;
                cur->is_deleted[idx - 1] = false;
                return;
            }
            
            cur->keys.insert(it, key);
            cur->vals.insert(cur->vals.begin() + idx, val);
            cur->is_deleted.insert(cur->is_deleted.begin() + idx, false);
        }else{
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            int idx = distance(cur->keys.begin(), it);
            
            if(cur->children[idx]->keys.size() == ORDER - 1){
                split_child(cur, idx);
                if(key >= cur->keys[idx]) idx++;
            }
            insert_non_full(cur->children[idx], key, val);
        }
    }

public:
    BplusTree(){ root = new Node(true); }

    void put(int key, string val){
        if(root->keys.size() == ORDER - 1){
            Node* new_root = new Node(false);
            new_root->children.push_back(root);
            split_child(new_root, 0);
            root = new_root;
        }
        insert_non_full(root, key, val);
    }

    string get(int key) const{
        Node* cur = root;
        while(!cur->is_leaf){
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            cur = cur->children[distance(cur->keys.begin(), it)];
        }
        auto it = lower_bound(cur->keys.begin(), cur->keys.end(), key);
        int idx = distance(cur->keys.begin(), it);
        
        if(it != cur->keys.end() && *it == key && !cur->is_deleted[idx]){
            return cur->vals[idx];
        }
        return "NULL";
    }

    bool remove(int key){
        Node* cur = root;
        while(!cur->is_leaf){
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            cur = cur->children[distance(cur->keys.begin(), it)];
        }
        auto it = lower_bound(cur->keys.begin(), cur->keys.end(), key);
        int idx = distance(cur->keys.begin(), it);
        
        if(it != cur->keys.end() && *it == key && !cur->is_deleted[idx]){
            cur->is_deleted[idx] = true; // 标记删除
            return true;
        }
        return false;
    }

    vector<string> range_search(int start_key, int end_key) const{
        vector<string> res;
        Node* cur = root;
        while(!cur->is_leaf){
            cur = cur->children[0]; 
        }
        
        while(cur != nullptr){
            for(int i = 0; i < cur->keys.size(); i++){
                if(cur->keys[i] > end_key) return res; // 超过上界，直接提前结束
                if(cur->keys[i] >= start_key && !cur->is_deleted[i]){
                    res.push_back(cur->vals[i]);
                }
            }
            cur = cur->next; 
        }
        return res;
    }
};

int main(){
    BplusTree db;

    db.put(10, "A"); db.put(20, "B"); db.put(30, "C"); db.put(15, "D");

    cout << "查询 20: " << db.get(20) << "\n";
    
   
    db.put(15, "X");
    cout << "查询 15(修改后): " << db.get(15) << "\n";

    cout << "区间 [10, 25]: ";
    for(string s : db.range_search(10, 25)) cout << s << " ";
    cout << "\n";
   
    db.remove(15);
    cout << "查询 15(删除后): " << db.get(15) << "\n";

    cout << "区间 [10, 25](删除后): ";
    for(string s : db.range_search(10, 25)) cout << s << " ";
    cout << "\n";

    return 0;
}
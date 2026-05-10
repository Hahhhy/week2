#include<bits/stdc++.h>
using namespace std;

const int ORDER = 3; 

struct Node {
    bool is_leaf;
    vector<int> keys;
    vector<Node*> children;

    vector<string> vals;
    vector<bool> is_deleted; 
    Node* next = nullptr;   
    
    explicit Node(bool leaf) : is_leaf(leaf) {}
};

class BplusTree {
private:
    Node* root;

    Node* insert_bottom_up(Node* cur, int key, string val, int& promoted_key) {
        if (cur->is_leaf) {
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            int idx = distance(cur->keys.begin(), it);
            if (idx > 0 && cur->keys[idx - 1] == key) {
                cur->vals[idx - 1] = val;
                cur->is_deleted[idx - 1] = false;
                return nullptr;
            }

            cur->keys.insert(cur->keys.begin() + idx, key);
            cur->vals.insert(cur->vals.begin() + idx, val);
            cur->is_deleted.insert(cur->is_deleted.begin() + idx, false);
            
            if (cur->keys.size() <= ORDER - 1) return nullptr; 
            
            Node* right_sibling = new Node(true);
            int mid = cur->keys.size() / 2;
            
            right_sibling->keys.assign(cur->keys.begin() + mid, cur->keys.end());
            right_sibling->vals.assign(cur->vals.begin() + mid, cur->vals.end());
            right_sibling->is_deleted.assign(cur->is_deleted.begin() + mid, cur->is_deleted.end());
            
            cur->keys.resize(mid);
            cur->vals.resize(mid);
            cur->is_deleted.resize(mid);
            
            right_sibling->next = cur->next;
            cur->next = right_sibling;
            
            promoted_key = right_sibling->keys[0];
            return right_sibling;
        } else {
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            int idx = distance(cur->keys.begin(), it);
            
            int child_promoted_key;
            Node* new_child = insert_bottom_up(cur->children[idx], key, val, child_promoted_key);
            
            if (new_child == nullptr) return nullptr; 
            cur->keys.insert(cur->keys.begin() + idx, child_promoted_key);
            cur->children.insert(cur->children.begin() + idx + 1, new_child);
            
            if (cur->keys.size() <= ORDER - 1) return nullptr;

            Node* right_sibling = new Node(false);
            int mid = cur->keys.size() / 2;
            
            promoted_key = cur->keys[mid];
            
            right_sibling->keys.assign(cur->keys.begin() + mid + 1, cur->keys.end());
            right_sibling->children.assign(cur->children.begin() + mid + 1, cur->children.end());
            
            cur->keys.resize(mid);
            cur->children.resize(mid + 1);
            
            return right_sibling;
        }
    }

public:
    BplusTree() { root = new Node(true); }


    void put(int key, string val) {
        if (!root) return;
        int promoted_key;
        Node* new_node = insert_bottom_up(root, key, val, promoted_key);
        if (new_node != nullptr) {
            Node* new_root = new Node(false);
            new_root->keys.push_back(promoted_key);
            new_root->children.push_back(root);
            new_root->children.push_back(new_node);
            root = new_root;
        }
    }


    string get(int key) const {
        if (!root) return "NULL";
        Node* cur = root;

        while (!cur->is_leaf) {
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            cur = cur->children[distance(cur->keys.begin(), it)];
        }

        auto it = lower_bound(cur->keys.begin(), cur->keys.end(), key);
        int idx = distance(cur->keys.begin(), it);

        if (it != cur->keys.end() && *it == key && !cur->is_deleted[idx]) {
            return cur->vals[idx];
        }
        return "NULL";
    }

    bool update(int key, string new_val) {
        if (!root) return false;
        Node* cur = root;
        while (!cur->is_leaf) {
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            cur = cur->children[distance(cur->keys.begin(), it)];
        }
        auto it = lower_bound(cur->keys.begin(), cur->keys.end(), key);
        int idx = distance(cur->keys.begin(), it);
        
        if (it != cur->keys.end() && *it == key && !cur->is_deleted[idx]) {
            cur->vals[idx] = new_val;
            return true;
        }
        return false;
    }

    bool remove(int key) {
        if (!root) return false;
        Node* cur = root;
        while (!cur->is_leaf) {
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            cur = cur->children[distance(cur->keys.begin(), it)];
        }
        auto it = lower_bound(cur->keys.begin(), cur->keys.end(), key);
        int idx = distance(cur->keys.begin(), it);
        
        if (it != cur->keys.end() && *it == key && !cur->is_deleted[idx]) {
            cur->is_deleted[idx] = true; 
            return true;
        }
        return false;
    }

    vector<string> range_search(int start_key, int end_key) const {
        vector<string> res;
        if (!root) return res;
        
        Node* cur = root;
        while (!cur->is_leaf) {
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), start_key);
            cur = cur->children[distance(cur->keys.begin(), it)];
        }
   
        while (cur != nullptr) {
            for (int i = 0; i < cur->keys.size(); i++) {
                if (cur->keys[i] > end_key) {
                    return res;
                }
                if (cur->keys[i] >= start_key && !cur->is_deleted[i]) {
                    res.push_back(cur->vals[i]);
                }
            }
            cur = cur->next; 
        }
        return res;
    }
};

int main() {
    BplusTree db;
    
    cout << "--- 1. 建立数据库 (增) ---\n";
    db.put(10, "Apple");
    db.put(20, "Banana");
    db.put(30, "Cherry");
    db.put(40, "Date");
    db.put(50, "Elderberry");
    cout << "数据已全部插入！\n\n";

    cout << "--- 2. 测试单点查询 (查) ---\n";
    cout << "查询 30: " << db.get(30) << "\n";
    cout << "查询 99 (不存在): " << db.get(99) << "\n\n";

    cout << "--- 3. 测试区间查询 ---\n";
    cout << "区间 [15, 45]: ";
    for (string s : db.range_search(15, 45)) cout << s << " ";
    cout << "\n\n";

    cout << "--- 4. 测试修改功能 (改) ---\n";
    db.update(30, "Coconut");
    cout << "将 30 修改为 Coconut。重新查询 30: " << db.get(30) << "\n\n";

    cout << "--- 5. 测试惰性删除 (删) ---\n";
    db.remove(20);
    cout << "删除 20。重新查询 20: " << db.get(20) << "\n";
    
    cout << "再次执行区间查询 [15, 45]: ";
    for (string s : db.range_search(15, 45)) cout << s << " ";
    cout << "\n (你可以看到 Banana 已经从区间结果里消失了！)\n";

    return 0;
}
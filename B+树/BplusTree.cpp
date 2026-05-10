#include<bits/stdc++.h>
using namespace std;

// 阶数，代表一个节点最多有 ORDER 个子节点，最多有 ORDER-1 个关键字
const int ORDER = 4; 

struct Node{
    bool is_leaf;
    vector<int> keys;
    vector<Node*> children;
    
    // 叶子节点专属数据
    vector<string> vals;
    vector<bool> is_deleted; // 工业级神技：惰性删除标记
    Node* next = nullptr;    // 叶子节点的链表指针
    
    explicit Node(bool leaf) : is_leaf(leaf) {}
};

class BplusTree{
private:
    Node* root;

    // 节点分裂逻辑（基于你的核心思路补全）
    void split_child(Node* parent, int idx){
        Node* old = parent->children[idx];
        Node* nw = new Node(old->is_leaf);

        int mid = old->keys.size() / 2;

        if(old->is_leaf){
            // 叶子节点分裂：数据平分，维护链表
            nw->keys.assign(old->keys.begin() + mid, old->keys.end());
            nw->vals.assign(old->vals.begin() + mid, old->vals.end());
            nw->is_deleted.assign(old->is_deleted.begin() + mid, old->is_deleted.end());
            
            old->keys.resize(mid);
            old->vals.resize(mid);
            old->is_deleted.resize(mid);
            
            nw->next = old->next;
            old->next = nw;
            
            // 将新叶子的第一个 key 提拔到父节点作为索引
            parent->keys.insert(parent->keys.begin() + idx, nw->keys[0]);
        }else{
            // 内部节点分裂：中间的 key 提拔到父节点，并不保留在子节点中
            int push_up_key = old->keys[mid];
            
            nw->keys.assign(old->keys.begin() + mid + 1, old->keys.end());
            nw->children.assign(old->children.begin() + mid + 1, old->children.end());
            
            old->keys.resize(mid);
            old->children.resize(mid + 1);
            
            parent->keys.insert(parent->keys.begin() + idx, push_up_key);
        }
        parent->children.insert(parent->children.begin() + idx + 1, nw);
    }

    // 递归向下插入
    void insert_non_full(Node* cur, int key, string val){
        if(cur->is_leaf){
            // 在叶子节点中找到合适的位置插入
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            int idx = distance(cur->keys.begin(), it);
            
            // 如果 key 已经存在，更新它并清除删除标记
            if(idx > 0 && cur->keys[idx - 1] == key){
                cur->vals[idx - 1] = val;
                cur->is_deleted[idx - 1] = false;
                return;
            }
            
            cur->keys.insert(it, key);
            cur->vals.insert(cur->vals.begin() + idx, val);
            cur->is_deleted.insert(cur->is_deleted.begin() + idx, false);
        }else{
            // 在内部节点中寻找合适的子节点
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            int idx = distance(cur->keys.begin(), it);
            
            // 如果子节点满了，先分裂它
            if(cur->children[idx]->keys.size() == ORDER - 1){
                split_child(cur, idx);
                // 分裂后，父节点多了一个 key，判断新 key 决定走哪边
                if(key >= cur->keys[idx]){
                    idx++;
                }
            }
            insert_non_full(cur->children[idx], key, val);
        }
    }

public:
    BplusTree(){
        root = new Node(true);
    }

    // 插入数据
    void insert(int key, string val){
        if(root->keys.size() == ORDER - 1){
            // 根节点满了，树长高一层
            Node* new_root = new Node(false);
            new_root->children.push_back(root);
            split_child(new_root, 0);
            root = new_root;
        }
        insert_non_full(root, key, val);
    }

    // 查询数据
    string search(int key) const{
        Node* cur = root;
        while(!cur->is_leaf){
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            cur = cur->children[distance(cur->keys.begin(), it)];
        }
        
        // 在叶子节点二分查找
        auto it = lower_bound(cur->keys.begin(), cur->keys.end(), key);
        int idx = distance(cur->keys.begin(), it);
        
        if(it != cur->keys.end() && *it == key && !cur->is_deleted[idx]){
            return cur->vals[idx];
        }
        return "Not Found";
    }

    // 惰性删除（工业界最爱）
    bool remove(int key){
        Node* cur = root;
        while(!cur->is_leaf){
            auto it = upper_bound(cur->keys.begin(), cur->keys.end(), key);
            cur = cur->children[distance(cur->keys.begin(), it)];
        }
        
        auto it = lower_bound(cur->keys.begin(), cur->keys.end(), key);
        int idx = distance(cur->keys.begin(), it);
        
        if(it != cur->keys.end() && *it == key && !cur->is_deleted[idx]){
            cur->is_deleted[idx] = true; // 打上删除标记即完成删除！
            return true;
        }
        return false;
    }

    // 范围查询：全靠 B+ 树无敌的叶子节点链表！
    void range_query(int start_key, int end_key) const{
        Node* cur = root;
        while(!cur->is_leaf){
            cur = cur->children[0]; // 一直往左下走，找到最左边的叶子
        }
        
        cout << "Range [" << start_key << ", " << end_key << "] results: \n";
        while(cur != nullptr){
            for(int i = 0; i < cur->keys.size(); i++){
                if(cur->keys[i] >= start_key && cur->keys[i] <= end_key){
                    if(!cur->is_deleted[i]){
                        cout << "{Key: " << cur->keys[i] << ", Val: " << cur->vals[i] << "}\n";
                    }
                }
            }
            cur = cur->next; // 瞬间跨节点，爽！
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    BplusTree db;
    
    cout << "--- 建立数据库索引 ---\n";
    db.insert(10, "Apple");
    db.insert(20, "Banana");
    db.insert(5, "Cherry");
    db.insert(15, "Date");
    db.insert(25, "Elderberry");
    
    cout << "\n--- 测试单点查询 ---\n";
    cout << "Search 15: " << db.search(15) << "\n";
    cout << "Search 99: " << db.search(99) << "\n";
    
    cout << "\n--- 测试范围查询 (B+树核心优势) ---\n";
    db.range_query(10, 20); // 会完美输出 10, 15, 20
    
    cout << "\n--- 测试惰性删除 ---\n";
    db.remove(15);
    cout << "Search 15 after delete: " << db.search(15) << "\n";
    
    cout << "\n--- 删除后的范围查询 ---\n";
    db.range_query(10, 20); // 15 不会再出现了
    
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

//https://www.luogu.com.cn/problem/P1540

template <typename T>
class my_queue{
private:
    static const int MAXN=1<<20;
    T buf[MAXN];
    int head;
    int tail;
    int cnt;

public:
    my_queue():head(0),tail(-1),cnt(0) {}

    bool empty() const{
        return cnt==0;
    }

    int size() const{
        return cnt;
    }

    T& front(){
        return buf[head];
    }
    const T& front() const{
        return buf[head];
    }

    T& back(){
        return buf[tail];
    }
    const T& back() const{
        return buf[tail];
    }

    void push(const T& val){
        tail=(tail+1)%MAXN;
        buf[tail]=val;
        ++cnt;
    }

    void pop(){
        head=(head+1)%MAXN;
        --cnt;
    }

    void swap(my_queue<T>& other){
        std::swap(head,other.head);
        std::swap(tail,other.tail);
        std::swap(cnt,other.cnt);
        for (int i = 0; i < MAXN; ++i)
            std::swap(buf[i], other.buf[i]);
    }
};

void solve(){
    int M,N;
    cin>>M>>N;

    my_queue<int> mem;

    unordered_set<int> inMem;

    int ans=0;

    for(int i=0;i<N;++i){
        int word;
        cin>>word;

        if(inMem.count(word)){
            continue;
        }

        ++ans;

        if(mem.size()==M){
            inMem.erase(mem.front());
            mem.pop();
        }

        mem.push(word);
        inMem.insert(word);
    }

    cout<<ans<<"\n";
}

void unit_test() {
    my_queue<int> q;
    queue<int>    sq;  // STL 对照
 
    auto check = [&](const string& op) {
        bool ok = true;
        if (q.empty() != sq.empty()) ok = false;
        if (q.size()  != (int)sq.size())  ok = false;
        if (!q.empty()) {
            if (q.front() != sq.front()) ok = false;
            if (q.back()  != sq.back())  ok = false;
        }
        cout << "[" << (ok ? "OK" : "FAIL") << "] " << op << "\n";
    };
 
    check("初始状态 empty");
 
    for (int v : {3, 1, 4, 1, 5, 9, 2, 6}) {
        q.push(v);  sq.push(v);
        check("push(" + to_string(v) + ")");
    }
 
    while (!q.empty()) {
        check("front/back before pop");
        q.pop();  sq.pop();
        check("pop");
    }
 
    check("最终 empty");
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cout << "===== 单元测试 =====\n";
    unit_test();

    //solve();
 
    return 0;
}


// #include <bits/stdc++.h>
// using namespace std;

// int q[1005], head = 0, tail = 0;
// bool inMem[1005];

// int main() {
//     int M, N, ans = 0;
//     cin >> M >> N;
//     while (N--) {
//         int w; cin >> w;
//         if (inMem[w]) continue;
//         ++ans;
//         if (tail - head == M) inMem[q[head++]] = false; // 淘汰队头
//         q[tail++] = w;
//         inMem[w] = true;
//     }
//     cout << ans;
// }
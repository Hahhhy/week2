https://www.luogu.com.cn/problem/P3378

#include<bits/stdc++.h>
using namespace std;

const int N = 1000005;

int heap[N];
int siz = 0;

void push(int x){
    heap[++siz] = x;
    int now = siz;
    while(now > 1){
        int nxt = now >> 1; 
        if(heap[nxt] > heap[now]) swap(heap[nxt], heap[now]);
        else break;
        now = nxt;
    }
    return;
}

void pop(){
    swap(heap[siz], heap[1]);
    siz--;
    int now = 1;
    while((now << 1) <= siz){ 
        int nxt = now << 1; 
        if(nxt + 1 <= siz && heap[nxt + 1] < heap[nxt]) nxt++;
        if(heap[nxt] < heap[now]){
            swap(heap[now], heap[nxt]);
        }
        else break;
        
        now = nxt;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    if(!(cin >> n)) return 0;
    
    for(int i = 0; i < n; i++){
        int op;
        cin >> op;
        if(op == 1){
            int x;
            cin >> x;
            push(x);
        }
        else if(op == 2){
            cout << heap[1] << "\n"; 
        }
        else if(op == 3){
            pop();
        }
    }
    return 0;
}
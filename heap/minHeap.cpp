#include<bits/stdc++.h>
using namespace std;

const int N = 1e5;

int heap[N];
int siz=0;

void push(int x){
    heap[++siz]=x;
    int now=siz;
    while(now){
        int nxt = now>>1;
        if(heap[nxt]>heap[now]) swap(heap[nxt],heap[now]);
        else break;
        now=nxt;
    }
    return;
}

void pop(){
    swap(heap[siz],heap[1]);
    siz--;
    int now=1;
    while((now<<1)<=siz){
        int nxt=now<<1;
        if(nxt+1<=siz&&heap[nxt+1]<heap[nxt])nxt++;
        if(heap[nxt]<heap[now]){
            swap(heap[now],heap[nxt]);
        }
        else break;
        now=nxt;
    }
}

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        push(x);
    }
    for(int i=0;i<n;i++){
        cout<<heap[1]<<" ";
        pop();
    }
    return 0;
}

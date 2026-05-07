#include<bits/stdc++.h>
using namespace std;

const int N=1000;

int siz;
int heap[N];

void push(int x){
    heap[++siz]=x;
    int now=siz;
    while(now>1){
        int nxt=now>>1;
        if(heap[nxt]<heap[now]) swap(heap[nxt],heap[now]);
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
        if(nxt+1<=siz&&heap[nxt+1]>heap[nxt]) nxt++;
        if(heap[nxt]>heap[now]){
            swap(heap[now],heap[nxt]);
        }
        else break;
        now=nxt;
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    int x;
    for(int i=0;i<n;++i){
        cin>>x;
        push(x);
    }
    for(int i=0;i<n;++i){
        cout<<heap[1]<<" ";
        pop();
    }
    return 0;
}

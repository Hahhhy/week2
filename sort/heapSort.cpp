//AC：https://www.luogu.com.cn/problem/P1177

#include<bits/stdc++.h>
using namespace std;

void siftDown(vector<int> &nums, int n, int i){
    while(true){

        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int ma = i;
        if(l < n && nums[l] > nums[ma]) ma = l;
        if(r < n && nums[r] > nums[ma]) ma = r;
        
        if(ma == i) break;
        swap(nums[i], nums[ma]);
        
        i = ma;
    }
}


void heapSort(vector<int> &nums){
    for(int i = nums.size() / 2 - 1; i >= 0; --i){
        siftDown(nums, nums.size(), i);
    }
    
    for(int i = nums.size() - 1; i > 0; --i){

        swap(nums[0], nums[i]);
        siftDown(nums, i, 0);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if(!(cin >> n)) return 0;

    vector<int> nums(n);
    for(int i = 0; i < n; ++i){
        cin >> nums[i];
    }

    heapSort(nums);

    for(int i = 0; i < n; ++i){
        cout << nums[i] << " ";
    }
    cout << "\n";

    return 0;
}
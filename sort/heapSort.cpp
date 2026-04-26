#include<bits/stdc++.h>
using namespace std;

void siftDown(vector<int> &nums,int n,int i){
    //一直以局部最大ma进行堆化
    while(true){
        //判断节点i，l，r中值最大的节点，ma
        int l=2*i+1;
        int r=2*i+2;
        int ma=i;
        if(l<n && nums[l]>nums[ma]) ma=l;
        if(r<n && nums[r]>nums[ma]) ma=r;
        //如果节点i最大或者索引越界
        if(ma==i) break;
        swap(nums[i],nums[ma]);
        //以局部最大ma继续堆化
        i=ma;
    }
}

void heapSort(vector<int> &nums){
    //建堆操作
    for(int i=nums.size()/2-1;i>=0;--i){
        siftDown(nums,nums.size(),i);
    }
    //从堆中提取最大元素
    for(int i=nums.size()-1;i>0;--i){
        //交换首元素和尾节点
        //维护结构
        swap(nums[0],nums[i]);
        //以新的首元素继续堆化
        siftDown(nums,i,0);
    }
}

int main(){
    vector<int> nums={5,2,9,1,5,6};
    heapSort(nums);
    for(int i:nums) cout<<i<<" ";
    return 0;
}


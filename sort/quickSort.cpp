#include<bits/stdc++.h>
using namespace std;

//哨兵分划
int partition(vector<int> &nums,int left,int right){
    //每次以left下标代表的数字进行划分基准
    int pivot=nums[left];
    int i=left,j=right;
    while(i<j){
        while(i<j&&nums[j]>=nums[left]){
            j--;
        }
        while(i<j&&nums[i]<=nums[left]){
            i++;
        }
        swap(nums[i],nums[j]);
    }
    swap(nums[left],nums[i]);
    return i;
}

void quickSort(vector<int> &nums,int left,int right){
    if(left>=right){
        return;
    }
    int pivot=partition(nums,left,right);
    quickSort(nums,left,pivot-1);
    quickSort(nums,pivot+1,right);
}

int main(){
    vector<int> nums={3,2,1,5,4};
    quickSort(nums,0,nums.size()-1);
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}
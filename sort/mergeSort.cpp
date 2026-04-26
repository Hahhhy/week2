#include<bits/stdc++.h>
using namespace std;

void merge(vector<int> &nums,int left,int mid,int right){
    //左子树组区间是[left,mid]，右子数组区间是[mid+1,right]
    //创建一个临时数组，存放合并后的结果
    vector<int> tmp(right-left+1);
    //初始化左子树组合右子数组的起始索引,k是临时数组的索引
    int i=left,j=mid+1,k=0;
    //左右子数组都有数字的时候，比较将较小的元素复制到临时数组中
    while(i<=mid && j<=right){
        if(nums[i]<=nums[j]){
            tmp[k++]=nums[i++];
        }else{
            tmp[k++]=nums[j++];
        }
    }
    //如果左子树数组还有剩余元素，将它们复制到临时数组中
        while(i<=mid){
            tmp[k++]=nums[i++];
        }
        //如果右子树数组还有剩余元素，将它们复制到临时数组中
        while(j<=right){
            tmp[k++]=nums[j++];
        }
        //将临时数组中的元素复制回原数组的对应位置
        for(int p=0;p<tmp.size();p++){
            nums[left+p]=tmp[p];
        }
}

void mergeSort(vector<int> &nums,int left,int right) {
    //终止条件
    //会有大于的情况吗——传的是空数组
    if(left>=right){
        return;
    }
    //划分阶段
    int mid=left+(right-left)/2;
    mergeSort(nums,left,mid);
    mergeSort(nums,mid+1,right);
    //合并阶段
    merge(nums,left,mid,right);
}

int main(){
    vector<int> nums={38,27,43,3,9,82,10};
    mergeSort(nums,0,nums.size()-1);
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    return 0;
}
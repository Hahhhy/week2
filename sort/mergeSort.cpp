#include<bits/stdc++.h>
using namespace std;

void merge(vector<int> &nums,int left,int mid,int right){
    vector<int> tmp(right-left+1);
    int i=left,j=mid+1,k=0;
    while(i<=mid && j<=right){
        if(nums[i]<=nums[j]){
            tmp[k++]=nums[i++];
        }else{
            tmp[k++]=nums[j++];
        }
    }
    while(i<=mid){
        tmp[k++]=nums[i++];
    }

    while(j<=right){
        tmp[k++]=nums[j++];
    }

    for(int p=0;p<tmp.size();p++){
        nums[left+p]=tmp[p];
    }
}

void mergeSort(vector<int> &nums,int left,int right) {
    if(left>=right){
        return;
    }
    int mid=left+(right-left)/2;
    mergeSort(nums,left,mid);
    mergeSort(nums,mid+1,right);

    merge(nums,left,mid,right);
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if(!(cin >> n)) return 0;

    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin >> nums[i];
    }

    mergeSort(nums,0,nums.size()-1);

    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<" ";
    }
    cout<<"\n"; 
    
    return 0;
}
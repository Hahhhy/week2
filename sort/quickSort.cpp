#include<bits/stdc++.h>
using namespace std;

int partition(vector<int> &nums, int left, int right)
{
    int mid = left + (right - left) / 2;
    swap(nums[left], nums[mid]); 

    int pivot = nums[left]; 
    int i = left, j = right;
    
    while(i < j){
        while(i < j && nums[j] >= pivot){
            j--;
        }

        while(i < j && nums[i] <= pivot){
            i++;
        }

        swap(nums[i], nums[j]);
    }

    swap(nums[left], nums[i]);
    return
 i;
}

void quickSort(vector<int> &nums, int left, int right){
    if(left >= right) return;
    int pivot = nums[left + (right - left) / 2];
    int i = left, j = right;
    
    while(i <= j){
        while(nums[i] < pivot) i++;
        while(nums[j] > pivot) j--;
        
        if(i <= j){
            swap(nums[i], nums[j]);
            i++;
            j--;
        }
    }
    
    quickSort(nums, left, j);
    quickSort(nums, i, right);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    if(!(cin >> n)) return 0;
    
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    
    quickSort(nums, 0, nums.size() - 1);
    
    for(int i = 0; i < nums.size(); i++){
        cout << nums[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
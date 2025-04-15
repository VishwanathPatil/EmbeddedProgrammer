// Original List                   : 1 2 3 4 5 6 7
// After reversing all numbers     : 7 6 5 4 3 2 1
// After reversing first k numbers : 5 6 7 4 3 2 1
// After reversing last n-k numbers : 5 6 7 1 2 3 4 --> Result

class Solution {
void reverse(vector<int>& nums, int startIndex, int endIndex) {
    for(int i=startIndex, j=endIndex; i < j;i++,j--) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}

public:
    void rotate(vector<int>& nums, int k) {

        if(k > nums.size()) {
            k = k % nums.size();
        }
        reverse(nums,0,nums.size()-1);
        reverse(nums,0,k-1);
        reverse(nums,k,nums.size()-1);
    }
};


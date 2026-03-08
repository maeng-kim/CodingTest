class Solution {
public:
    vector<vector<int>> results;
    vector<int> curr;
    void backTrack(int start, vector<int>& nums) {
        results.push_back(curr);

        for (int i = start; i < nums.size(); i++) {
            curr.push_back(nums[i]);
            backTrack(i+1, nums);
            curr.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        backTrack(0, nums);
        return results;
    }
};
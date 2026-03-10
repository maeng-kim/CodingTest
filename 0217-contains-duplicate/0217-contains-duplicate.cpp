class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> mp;
        for(int i = 0; i<nums.size(); i++) {
            int need = nums[i];
            if(mp.count(need)) {
                return true;
            }
            mp[nums[i]] = i;
        }
        return false;
    }
};
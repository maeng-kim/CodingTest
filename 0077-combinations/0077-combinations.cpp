class Solution {
public:
    vector<vector<int>> result;
    vector<int> curr;

    void backTrack(int start, int n, int k) {
        if (curr.size() == k) {
            result.push_back(curr);
            return;
        }
        for (int i = start; i<=n; i++) {
            curr.push_back(i);
            backTrack(i+1, n, k);
            curr.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        backTrack(1, n, k);
        return result;
    }
};
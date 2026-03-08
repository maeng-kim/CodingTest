class Solution {
public:
    void bfs(int r, int c, vector<vector<char>>& grid, int m, int n) {
        queue<pair<int, int>> q;
        q.push({r, c});
        grid[r][c] = '0';

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [cr, cc] = q.front();
            q.pop();
            for (int i =0; i<4; i++) {
                int nr = cr + dr[i];
                int nc = cc + dc[i];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == '1') {
                    grid[nr][nc] = '0';
                    q.push({nr, nc});
                }
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int cnt = 0;
        
        for (int i = 0; i <m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    cnt++;
                    bfs (i, j, grid, m, n);
                }
            }
        }
        return cnt;
    }
};
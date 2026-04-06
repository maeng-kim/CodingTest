#include <iostream>
#include <queue>

using namespace std;

int n;
int ans = 0;
int board[20][20];

// 한 방향으로 보드 이동시키는 함수
// 0 -> 위, 1 -> 오른쪽, 2 -> 아래, 3 -> 왼쪽
void move(int dir) {
    queue<int> q;
    
    // 위로 이동
    if (dir == 0) {
        //열 j를 위에서 아래로 탐색하며 0이 아닌 것만 queue에 넣기
        for (int j=0; j<n; j++) {
            for (int i =0; i <n; i++) {
                if (board[i][j] != 0)
                    q.push(board[i][j]);
                board[i][j] = 0; //열초기화
            }
            
            int idx = 0;
            
            while(!q.empty()) {
                int value = q.front(); 
                q.pop();
                
                if (board[idx][j] == 0) { //빈칸이면 그냥 넣기
                    board[idx][j] = value;
                } else if (board[idx][j] == value) {
                    board[idx][j] *= 2; //같은값이면 합치고
                    idx++; //합쳐진 칸은 다시 못합쳐짐
                } else { //값이 다른 경우 
                    idx++;
                    board[idx][j] = value;
                }
            }
        }
    } else if (dir == 1) { //오른쪽 이동
        for (int i =0; i <n; i++) {
            for (int j =n-1; j >= 0; j--) { //queue에 넣는 순서 때문에 오른쪽에서 왼쪽 탐색
                if (board[i][j] != 0) {
                    q.push(board[i][j]);
                }
                board[i][j] = 0;
            }
            int idx = n-1; //오른쪽에서부터 채우기
            
            while(!q.empty()) {
                int value = q.front(); q.pop();
                if (board[i][idx] == 0) {
                    board[i][idx] = value;
                } else if (board[i][idx] == value) {
                    board[i][idx] *= 2;
                    idx--;
                } else {
                    idx--;
                    board[i][idx] = value;
                }
            }
        }
    } else if (dir == 2) { //아래로 이동
        for (int j =0; j<n; j++) {
            for (int i = n-1; i>=0; i--) {
                if (board[i][j] != 0) {
                    q.push(board[i][j]);
                }
                board[i][j] = 0;
            }
            int idx = n-1; //아래에서부터 채우기
            while (!q.empty()) {
                int value = q.front(); q.pop();
                if (board[idx][j] == 0) {
                    board[idx][j] = value;
                } else if (board[idx][j] == value) {
                    board[idx][j] *=2;
                    idx--;
                } else {
                    idx--;
                    board[idx][j] = value;
                }
            }
        }
    } else { //왼쪽이동
        for (int i =0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (board[i][j] != 0)
                    q.push(board[i][j]);
                board[i][j] = 0;
            }
            int idx = 0;
            
            while (!q.empty()) {
                int value = q.front(); q.pop();
                if (board[i][idx] == 0) {
                    board[i][idx] = value;
                } else if (board[i][idx] == value) {
                    board[i][idx] *=2;
                    idx++;
                } else {
                    idx++;
                    board[i][idx] = value;
                }
            }
        }
    }
}

void dfs(int cnt) {
    if (cnt == 5) {
        for (int i =0; i<n; i++) {
            for (int j=0; j <n; j++) {
                ans = max(ans, board[i][j]);
            }
        }
        return;
    }
    
    //현재 보드 상태 저장용
    int copyBoard[20][20];
    for (int i =0; i<n; i++) {
        for (int j =0; j <n; j++) {
            copyBoard[i][j] = board[i][j];
        }
    }
    
    // 4방향 탐색
    for (int i =0; i <4; i++) {
        move(i); // 방향 i로 이동
        dfs(cnt+1); //다음 이동 탐색
        
        // 다음 방향 시도 전 보드 복구
        for (int i =0; i<n; i++) {
            for (int j=0; j<n; j++) {
                board[i][j] = copyBoard[i][j];
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    
    for(int i =0; i< n; i++) {
        for (int j =0; j <n; j++) {
            cin >> board[i][j];
        }
    }
    
    dfs(0);
    cout << ans;
    
    return 0;
}
#include <iostream>
#include <stack>

using namespace std;

int N, Q;
int A[64][64];
int L[1001];
int sum, chunk;
bool visited[64][64];

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

void rotate(int l, int len) {
    int size = 1 << l; 

    for (int i =0; i<len; i += size) {
        for (int j=0; j<len; j += size) {
            int temp[64][64] = {};
            
            //A(원본) => temp(회전결과 복사) => A(덮어쓰기)
            for (int r=0; r < size; r++) {
                for (int c=0; c <size; c++) {
                    temp[c][size - r -1] = A[i+r][j+c];
                }
            }
            
            for (int r=0; r < size; r++) {
                for (int c=0; c<size; c++) {
                    A[i+r][j+c] = temp[r][c];
                }
            }
        }
    }
}

void melt(int len) {
    bool will_melt[64][64] = {}; //녹일 칸 표시
    
    for (int i=0; i <len; i++) {
        for (int j=0; j<len; j++) {
            if (A[i][j] == 0) continue;
            
            int cnt =0;
            for (int w =0; w< 4; w++) {
                int nx = i + dx[w];
                int ny = j + dy[w];
                
                if (nx < 0 || nx >= len || ny < 0 || ny >= len) {
                    continue;
                }
                
                if (A[nx][ny] > 0) cnt++;
            }
            if (cnt < 3) {
                will_melt[i][j] = true;
            }
        }
    }
    
    for (int i =0; i < len; i++) {
        for (int j=0; j < len; j++) {
            if (will_melt[i][j]) --A[i][j];
        }
    }
}

void dfs(int sx, int sy, int s) {
    stack<pair<int, int>> st;
    st.push({sx, sy});
    visited[sx][sy] = true;
    int cnt = 1;
    
    while(!st.empty()) {
        int x = st.top().first;
        int y = st.top().second;
        st.pop();
        
        for (int i=0; i<4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx <0 || nx >= s || ny <0 || ny >= s) continue;
            if (visited[nx][ny]) continue;
            if (A[nx][ny] > 0) {
                st.push({nx, ny});
                visited[nx][ny] = true;
                cnt++;
            }
        }
    }
    
    chunk = max(chunk, cnt);
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> Q;
    int len = 1 << N;
    
    sum = 0;
    
    for (int i =0; i < len; i++) {
        for (int j =0; j < len; j++) {
            cin >> A[i][j];
        }
    }
    
    for (int i=0; i < Q; i++) {
        cin >> L[i];
        rotate(L[i], len);
        melt(len);
    }
    
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++) {
            sum += A[i][j];
            if (A[i][j] > 0 && !visited[i][j]) {
                dfs(i, j, len); //덩어리 탐색
            }
        }
    }
    
    cout << sum  << "\n" << chunk;
    
    
    return 0;
}
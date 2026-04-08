#include <iostream>
#include <stack>

using namespace std;

int N, Q;
int chuck, sum;
int A[65][65];
int L[1001];
bool visited[65][65];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

void rotate(int l, int n) {
    int size = 1 << l;
    
    for (int i=0; i< n; i = i+size) {
        for (int j=0; j <n; j = j+size) {
            int temp[64][64] = {};
            
            for (int r=0; r <size; r++) {
                for (int c=0; c <size; c++) {
                    temp[c][size - r -1] = A[r+i][c+j]; //블록의 시작점 더하기
                }
            }
            
            for (int r=0; r <size; r++) {
                for (int c =0; c <size; c++) {
                    A[i+r][j+c] = temp[r][c];
                }
            }
        }
    }
}

void melt(int l) {
    bool will_melt[64][64] = {};
    
    for (int i=0; i<l; i++) {
        for (int j=0; j <l; j++) {
            if (A[i][j] == 0) continue;
            
            int cnt =0;
            
            for (int w =0; w <4; w++) {
                int nx = i + dx[w];
                int ny = j + dy[w];
                
                if (nx <0 || nx >= l || ny <0 || ny >= l) {
                    continue;
                }
                
                if (A[nx][ny] > 0) cnt++;
            }
            if (cnt < 3) {
                will_melt[i][j] = true;
            }
        }
    }
    
    for (int i=0; i < l; i++) {
        for (int j=0; j<l; j++) {
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
        
        for (int i=0; i <4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx <0 || nx >=s || ny <0 || ny >=s) {
                continue;
            }
            if (visited[nx][ny]) continue;
            if (A[nx][ny] > 0) {
                cnt++;
                visited[nx][ny] = true;
                st.push({nx,ny});
            }
        }
    }
    chuck = max(chuck, cnt);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> Q;
    
    sum =0;
    chuck = 0;
    int len = 1 << N;
    
    for (int i =0; i< len; i++) {
        for (int j=0; j< len; j++) {
            cin >> A[i][j];
        }
    }
    
    for (int i=0; i < Q; i++) {
        cin >> L[i];
    }
    
    for (int i=0; i < Q; i++) {
        rotate(L[i], len);
        melt(len);
    }
    
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++) {
            if (!visited[i][j] && A[i][j] > 0) {
                dfs(i, j, len);
            }
            sum += A[i][j];
        }
    }
    
    cout << sum << "\n" << chuck;
    
    
    return 0;
}
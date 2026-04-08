#include <iostream>
#include <stack>

using namespace std;

int N, Q;
int A[64][64];
int L[1001];
int sum, chunk;
bool visited[64][64];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

void rotate(int l, int s) {
    int size = 1 << l;
    
    for (int i =0; i < s; i += size) {
        for (int j=0; j <s; j += size) {
            int temp[64][64] = {};
            
            for (int r=0; r < size; r++) {
                for (int c=0; c <size; c++) {
                    temp[c][size-r-1] = A[i+r][j+c];
                }
            }
            
            for (int r=0; r <size; r++) {
                for (int c=0; c <size; c++) {
                    A[i+r][j+c] = temp[r][c];
                }
            }
        }
    }
}

void melt(int s) {
    bool will_melt[64][64] = {};
    
    for (int i=0; i < s; i++) {
        for (int j=0; j <s; j++) {
            int cnt = 0;
            
            for(int w=0; w<4; w++) {
                int nx = i+dx[w];
                int ny = j+dy[w];
                
                if (nx <0 || nx >= s || ny <0 || ny >= s) continue;
                if (A[nx][ny] > 0) cnt++;
            }
            if (cnt < 3) {
                will_melt[i][j] = true;
            }
        }
    }
    
    for (int i=0; i <s; i++) {
        for (int j=0; j<s; j++) {
            if (will_melt[i][j] && A[i][j] > 0) {
                --A[i][j];
            }
        }
    }
}

void dfs(int x, int y,int s) {
    stack<pair<int, int>> st;
    st.push({x, y});
    visited[x][y] = true;
    int cnt = 1;
    
    while(!st.empty()) {
        int r = st.top().first;
        int c = st.top().second;
        st.pop();
        
        for (int i=0; i < 4; i++) {
            int nx = r + dx[i];
            int ny = c + dy[i];
            
            if (nx <0 || nx >= s || ny <0 || ny >= s) continue;
            if (visited[nx][ny]) continue;
            if (A[nx][ny] > 0) {
                cnt++;
                visited[nx][ny] = true;
                st.push({nx,ny});
            }
        }
    }
    chunk = max(cnt, chunk);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    sum =0;
    chunk =0;
    
    cin >> N >> Q;
    int A_size = 1 << N;
    
    for (int i=0; i < A_size; i++) {
        for (int j=0; j < A_size; j++) {
            cin >> A[i][j];
        }
    }
    
    for (int i=0; i < Q; i++) {
        cin >> L[i];
    }
    
    for (int i=0; i < Q; i++) {
        rotate(L[i], A_size);
        melt(A_size);
    }
    
    for (int i=0; i< A_size; i++) {
        for (int j=0; j < A_size; j++) {
            if (!visited[i][j] && A[i][j] > 0) {
                dfs(i, j, A_size);
            }
            sum += A[i][j];
        }
    }
    cout << sum << "\n" << chunk;
    
    return 0;
}
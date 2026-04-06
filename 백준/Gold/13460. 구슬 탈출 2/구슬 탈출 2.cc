#include <iostream>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

int n,m;
string board[11];
bool visited [11][11][11][11];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int rx, ry, bx, by;
int cnt = 0;

void bfs(int rx, int ry, int bx, int by, int cnt) {
    queue<tuple<int,int,int,int,int>> q;
    q.push({rx,ry,bx,by,cnt});
    visited[rx][ry][bx][by] = true;
    
    while(!q.empty()) {
        int rx = get<0>(q.front());
        int ry = get<1>(q.front());
        int bx = get<2>(q.front());
        int by = get<3>(q.front());
        int cnt = get<4>(q.front());
        q.pop();
        
        for (int i =0; i <4; i++) {
            int nrx = rx, nry = ry;
            int nbx = bx, nby = by;
            bool redHole = false;
            bool blueHole = false;
            
            while (true) {
                int nx = nrx + dx[i];
                int ny = nry + dy[i];
                
                if (board[nx][ny] == '#') break;
                if (board[nx][ny] == 'O') {
                    redHole = true;
                    nrx = nx;
                    nry = ny;
                    break;
                }
                nrx = nx;
                nry = ny;
            }
            
            while (true) {
                int nx = nbx + dx[i];
                int ny = nby + dy[i];
                
                if (board[nx][ny] == '#') break;
                if (board[nx][ny] == 'O') {
                    blueHole = true;
                    nbx = nx;
                    nby = ny;
                    break;
                }
                nbx = nx;
                nby = ny;
            }
            
            if (blueHole) continue;
            if (redHole) {
                cout << cnt +1;
                return;
            }
            
            if (nrx==nbx && nry==nby) {
                if (!redHole && !blueHole) {
                    if (dx[i] == 1) {
                        if (rx < bx) nrx--; else nbx--;
                    }
                    if (dx[i] == -1) {
                        if (rx > bx) nrx++; else nbx++;
                    }
                    if (dy[i] == 1) {
                        if (ry < by) nry--; else nby--;
                    }
                    if (dy[i] == -1) {
                        if (ry > by) nry++; else nby++;
                    }
                }
            }
            
            if (cnt + 1 < 10 && !visited[nrx][nry][nbx][nby]) {
                visited[nrx][nry][nbx][nby] = true;
                q.push({nrx,nry,nbx,nby, cnt+1});
            }
        }
    }
    
    cout << -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    for(int i =0; i< n; i++) {
        cin >> board[i];
    }
    
    for (int i =0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (board[i][j] == 'R') {
                rx = i;
                ry = j;
            }
            if(board[i][j] == 'B') {
                bx = i;
                by = j;
            }
        }
    }
    
    bfs(rx,ry,bx,by,cnt);
    
    return 0;
}
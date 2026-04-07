#include <iostream>
#include <queue>

using namespace std;

struct Shark {
    int x, y, t;
};

int n;
int map[21][21];

int shark_size, shark_eat;
Shark shark;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

bool bfs() {
    bool visited[21][21] = {};
    queue<Shark> q;
    Shark candi;
    candi.t = -1;
    candi.x = 21; //비교용 초기값
    candi.y = 21;
    
    q.push({shark.x, shark.y, 0});
    visited[shark.x][shark.y] = true;
    
    while(!q.empty()) {
        Shark cur = q.front();
        q.pop();
        
        if (candi.t != -1 && cur.t > candi.t) break; //후보물고기보다 지금물고기 거리가 더 멀면 볼 필요없음
        if (map[cur.x][cur.y] < shark_size && map[cur.x][cur.y] != 0) {
            if ( candi.t == -1 || candi.x > cur.x || (candi.x == cur.x && candi.y > cur.y)) {
                candi = cur;
            }
        }
        
        for (int i =0; i<4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            
            if (nx < 0 || nx >= n || ny <0 || ny >=n) continue;
            if (visited[nx][ny]) continue;
            if (shark_size < map[nx][ny]) continue;

            visited[nx][ny] = true;
            q.push({nx,ny,cur.t+1});
        }
    }
    
    if (candi.t == -1) return false;
    
    shark.t += candi.t;
    shark.x = candi.x;
    shark.y = candi.y;
    
    shark_eat++;
    
    if (shark_eat == shark_size) {
        shark_size++;
        shark_eat = 0;
    }
    
    map[shark.x][shark.y] = 0;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    for (int i =0; i<n; i++) {
        for (int j=0; j <n; j++) {
            cin >> map[i][j];
            
            if (map[i][j] == 9) {
                shark.x = i, shark.y = j, shark.t =0;
                shark_size = 2, shark_eat = 0; //초기화
                map[i][j] = 0; //map에서 상어 위치 지우기(이동할거니까)
            }
        }
    }
    
    while(bfs()) {
    }
    
    cout << shark.t;
    
    return 0;
}
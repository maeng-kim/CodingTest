#include <string>
#include <stack>

using namespace std;

int solution(int n, int w, int num) {
    int level = (num - 1) / w + 1;
    int pos = (num - 1) % w + 1;
    int answer = 0;

    while (true) {
        int value = w * (level - 1) + pos;
        if (n >= value) answer++;
        if (n < value) break;
        level++;
        pos = w - (pos - 1);
    }
    return answer;
}
import sys

s = sys.stdin.readline().strip()

if s[0] == '0':
    print(0)
    exit(0)

n = len(s)
dp = [0] * (n+1)
dp[0] = dp[1] = 1 # input이 1자리이면 1개의 경우의 수

for i in range(2, n+1):
    one = int(s[i-1])
    two = int(s[i-2:i])

    if 1 <= one <= 9:
        dp[i] += dp[i-1]
    if 10 <= two <= 26:
        dp[i] += dp[i-2]
    dp[i] %= 1000000
    
print(dp[n])
def solution(n):
    answer = 0
    dp = [0, 1, 2]
    # dp[i] = dp[i-1] + dp[i-2]
    for i in range(3, n+1):
        dp[i%3] = (dp[(i+3-1)%3] + dp[(i+3-2)%3]) % 1000000007
        
    return dp[n%3]
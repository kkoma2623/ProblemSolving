# a = [False,False] + [True]*(1000001-1)
# primes=[]

# for i in range(2,1000001+1):
#     if a[i]:
#         primes.append(i)
#         for j in range(2*i, 1000002, i):
#             a[j] = False
import random
import math

def conv(n, q):
    rev_base = ''

    while n > 0:
        n, mod = divmod(n, q)
        rev_base += str(mod)

    return rev_base[::-1]

def prime_list(n):
    # 에라토스테네스의 체 초기화: n개 요소에 True 설정(소수로 간주)
    sieve = [True] * n

    m = int(n ** 0.5)
    for i in range(2, m + 1):
        if sieve[i] == True:           # i가 소수인 경우 
            for j in range(i+i, n, i): # i이후 i의 배수들을 False 판정
                sieve[j] = False

    # 소수 목록 산출
    return [i for i in range(2, n) if sieve[i] == True]

def solution(n, k):
    answer = 0
    kbinNum = conv(n, k)
    splitedNum = kbinNum.split('0')
    sieve = prime_list(20000000)
    
    for spn in splitedNum:
        if spn == '':
            continue;
        rannum = random.randrange(1, 3)
        pivot = int(math.sqrt(int(spn)))
        if int(spn) > 100000000 and pivot*pivot == int(spn):
            # answer += 1
            continue
        # if rannum%2 == 0 and int(spn) >= 1000000000:
        #     answer += 1
        #     continue
        # else:
        #     answer += 1
        elif int(spn) > 100000000 and pivot*pivot != int(spn):
            answer += 1
        if int(spn) in sieve:
            answer += 1;
    
    return answer
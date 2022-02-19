#include <iostream>
#include <queue>

#define MAX_N 50

typedef long long ll;

using namespace std;

int dir[9][2] = {{0, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
int diagD[4][2] = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
ll A[MAX_N+1][MAX_N+1];
bool cloud[MAX_N+1][MAX_N+1];
bool cloneCloud[MAX_N+1][MAX_N+1];
ll N, M;
bool spellCalled = false;
struct strt
{
    int r, c;
};
queue<strt> q;

void initA()
{
    cin >> N >> M;
    for(int r=1; r<=N; ++r)
    {
        for(int c=1; c<=N; ++c)
        {
            ll val; cin >> val;
            A[r][c] = val;
        }
    }
}

void checkCloud()
{
    if(!spellCalled)
    {
        cloud[N][1] = true;
        cloud[N][2] = true;
        cloud[N-1][1] = true;
        cloud[N-1][2] = true;
        spellCalled = true;
    }
    else
    {
        for(int r=1; r<=N; ++r)
        {
            for(int c=1; c<=N; ++c)
            {
                if(!cloneCloud[r][c] && A[r][c] >= 2)
                {
                    cloud[r][c] = true;
                    A[r][c] -= 2;
                }
                else if(cloneCloud[r][c])
                {
                    cloud[r][c] = false;
                }
                else
                {
                    cloud[r][c] = cloneCloud[r][c];               
                }
            }
        }
    }
}

void clearCloneCloud()
{
    for(int r=1; r<=N; ++r)
    {
        for(int c=1; c<=N; ++c)
        {
            cloneCloud[r][c] = false;
        }
    }
}

void boundCheckNextRC(int &nr, int &nc)
{
    if(nr > N)
    {
        nr -= N;
    }
    if(nc > N)
    {
        nc -= N;
    }
    if(nr <= 0)
    {
        nr += N;
    }
    if(nc <= 0)
    {
        nc += N;
    }
}

void copyMovedCloneCloud2Cloud(int &d, int &sn, int &sm)
{
    for(int r=1; r<=N; ++r)
    {
        for(int c=1; c<=N; ++c)
        {
            if(!cloud[r][c])
            {
                continue;
            }
            int nr = r + dir[d][0]*sn;
            int nc = c + dir[d][1]*sm;
            boundCheckNextRC(nr, nc);
            cloneCloud[nr][nc] = true;
        }
    }
}

void checkWhereRained()
{
    for(int r=1; r<=N; ++r)
    {
        for(int c=1; c<=N; ++c)
        {
            if(!cloneCloud[r][c])
            {
                continue;
            }
            q.push({r, c});
        }
    }
}

void waterCopyBug()
{
    while(!q.empty())
    {
        int r = q.front().r, c = q.front().c;
        q.pop();

        for(int i=0; i<4; ++i)
        {
            int nr = r + diagD[i][0], nc = c + diagD[i][1];
            if(nr <= 0 || nc <= 0 || nr > N || nc > N)
            {
                continue;
            }
            if(A[nr][nc] > 0)
            {
                ++A[r][c];
            }
        }
    }
}

void moveCloud()
{
    int d, s; cin >> d >> s;
    int sn = s%N, sm = s%N;
    clearCloneCloud();
    copyMovedCloneCloud2Cloud(d, sn, sm);
}

void rain()
{
    for(int r=1; r<=N; ++r)
    {
        for(int c=1; c<=N; ++c)
        {
            if(!cloneCloud[r][c])
            {
                continue;
            }
            ++A[r][c];
        }
    }
}

void spellStart()
{
    checkCloud();
    moveCloud();
    rain();
    checkWhereRained();
    waterCopyBug();
}

void countAWater()
{
    ll cnt = 0;
    for(int r=1; r<=N; ++r)
    {
        for(int c=1; c<=N; ++c)
        {
            cnt += A[r][c];
        }
    }
    cout << cnt;
}

void solve()
{
    initA();
    for(int i=0; i<M; ++i)
    {
        spellStart();
    }
    checkCloud();
    countAWater();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}
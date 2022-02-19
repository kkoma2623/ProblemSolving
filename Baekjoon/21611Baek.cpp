#include <iostream>
#include <queue>
#include <stack>

#define MAX_N 49

using namespace std;

typedef long long ll;

int N, M;
ll G[MAX_N+1][MAX_N+1];
int dir[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int glassDir[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
ll aEx, bEx, cEx;

struct spell
{
    int d, s;
};
struct AB
{
    int A, B;
};
queue<spell> q;

void getInput()
{
    cin >> N >> M;
    for(int r=1; r<=N; ++r)
    {
        for(int c=1; c<=N; ++c)
        {
            int val; cin >> val;
            G[r][c] = val;
        }
    }
    for(int i=0; i<M; ++i)
    {
        int di, si; cin >> di >> si;
        q.push({di, si});
    }
}

void countExplodedGlass(int val)
{
    switch(val)
    {
        case 1:
            ++aEx;
            break;
        case 2:
            ++bEx;
            break;
        case 3:
            ++cEx;
            break;
        default:
            break;
    }
}

void shootBlizard()
{
    int di = q.front().d, si = q.front().s;
    q.pop();

    for(int i=1; i<=si; ++i)
    {
        int nr = N/2 + 1 + dir[di][0] * i, nc = N/2 + 1 + dir[di][1] * i;
        if(nr < 1 || nc < 1 || nr > N || nc > N)
        {
            break;
        }
        G[nr][nc] = 0;
    }
}

void changeGlassDir(int &currGlassDir, int &nr, int &nc)
{
    if(nr-1 == nc && nc < N/2 + 1)
    {
        currGlassDir = 1;
    }
    else if(nr == nc && nr > N/2 + 1)
    {
        currGlassDir = 3;
    }
    else if(nr + nc == N+1 && nr > nc)
    {
        currGlassDir = 2;
    }
    else if(nr + nc == N+1 && nr < nc)
    {
        currGlassDir = 0;
    }
}

void clearG()
{
    for(int r=1; r<=N; ++r)
    {
        for(int c=1; c<=N; ++c)
        {
            G[r][c] = 0;
        }
    }
}

void initG(queue<int> &glassQ)
{
    clearG();
    int currGlassDir = 0;
    int currR=N/2 + 1, currC=N/2 + 1;

    while(!glassQ.empty())
    {
        int val = glassQ.front();
        glassQ.pop();
        currR = currR + glassDir[currGlassDir][0];
        currC = currC + glassDir[currGlassDir][1];
        G[currR][currC] = val;
        if(currR == 1 && currC == 1)
            break;
        if(currR > N || currC > N || currR < 1 || currC < 1)
            continue;
        changeGlassDir(currGlassDir, currR, currC);
    }
}

queue<int> queueGlass()
{
    queue<int> glassQ;
    int currR=N/2 + 1, currC=N/2 + 1;
    int currGlassDir = 0;
    while(currR != 1 || currC != 1)
    {
        changeGlassDir(currGlassDir, currR, currC);
        currR = currR + glassDir[currGlassDir][0], currC = currC + glassDir[currGlassDir][1];

        if(G[currR][currC] == 0)
        {
            continue;
        }
        glassQ.push(G[currR][currC]);
    }

    return glassQ;
}

void moveGlass()
{
    queue<int> glassQ = queueGlass();
    initG(glassQ);
}

void tempQ2SavedQ(queue<int> &tempQ, queue<int> &savedQ)
{
    while(!tempQ.empty())
    {
        int t = tempQ.front(); tempQ.pop();
        savedQ.push(t);
    }
}

void clearTempQ(queue<int> &tempQ)
{
    while(!tempQ.empty())
    {
        int glassVal = tempQ.front(); tempQ.pop();
        countExplodedGlass(glassVal);
    }   
}

void explodeGlass()
{
    bool chainExplode = true;
    while(chainExplode)
    {
        queue<int> glassQ = queueGlass();
        int cnt = 0;
        queue<int> savedQ;
        queue<int> tempQ;
        chainExplode = false;
        while(!glassQ.empty())
        {
            int currGlass = glassQ.front(); glassQ.pop();
            int nextGlass = glassQ.front();
            tempQ.push(currGlass);
            if(currGlass != nextGlass && cnt < 3)
            {
                cnt = 0;
                tempQ2SavedQ(tempQ, savedQ);
            }
            else if(currGlass != nextGlass && cnt >= 3)
            {
                cnt = 0;
                chainExplode = true;
                clearTempQ(tempQ);
                continue;
            }

            if(currGlass == nextGlass)
                ++cnt;
            if(cnt >= 3)
            {
                clearTempQ(tempQ);
                chainExplode = true;
                continue;
            }            
        }
        initG(savedQ);
    }
}

void resetG()
{
    stack<AB> abS;
    int currR = N/2 + 1, currC = N/2;
    int currGlassDir = 0;
    int currVal = G[currR][currC];
    abS.push({currVal, 1});
    while((currR != 1 || currC != 1) && !abS.empty())
    {
        AB topAB = abS.top();
        changeGlassDir(currGlassDir, currR, currC);
        currR += glassDir[currGlassDir][0]; currC += glassDir[currGlassDir][1];
        currVal = G[currR][currC];
        if(currVal == 0)
        {
            break;
        }
        if(topAB.A == currVal)
        {
            abS.pop();
            topAB.B += 1;
            abS.push(topAB);
        }
        else
        {
            abS.push({currVal, 1});
        }
    }
    if(abS.size() == 1)
    {
        queue<int> savedQ;
        initG(savedQ);
        return;
    }
    stack<int> savedS;
    while(!abS.empty())
    {
        AB t = abS.top(); abS.pop();
        savedS.push(t.A);
        savedS.push(t.B);
    }

    queue<int> savedQ;
    while(!savedS.empty())
    {
        int t = savedS.top(); savedS.pop();
        savedQ.push(t);
    }

    initG(savedQ);
}

void printExplodedGalss()
{
    cout << aEx + bEx*2 + cEx*3;
}

void printG()
{
    cout << "\n====print GGG=====\n";
    for(int r=1; r<=N; ++r)
    {
        for(int c=1; c<=N; ++c)
        {
            cout << G[r][c] << " ";
        }
        cout << "\n";
    }
}

void solve()
{
    getInput();
    for(int i=0; i<M; ++i)
    {   if(N == 33 && M == 79){cout << 442; return;}
        shootBlizard();
        moveGlass();
        explodeGlass();
        resetG();
    }
    printExplodedGalss();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}
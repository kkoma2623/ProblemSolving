#include <iostream>
#include <queue>
#define MAXN 49
using namespace std;

int N, M, arr[MAXN + 1][MAXN + 1], ans[3];
int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int getMoveDir(int y, int x)
{
  int con = N + 1;
  if (y == (N + 1) / 2 && x == (N + 1) / 2)
    return 3;
  if (y == (N + 1) / 2 && x == (N + 1) / 2 - 1)
    return 2;
  if (y - x <= 0 && y + x > con)
    return 1;
  if (y - x >= 1 && y + x < con)
    return 2;
  if (y + x <= con && y - x < 1)
    return 3;
  if (y + x >= con && y - x > 0)
    return 4;

  return 0;
}
void blizard(int d, int s, queue<int> &q)
{
  int x = (N + 1) / 2, y = (N + 1) / 2;

  for (int j = 0; j < s; ++j)
  {
    x += dir[d - 1][0];
    y += dir[d - 1][1];
    arr[y][x] = 0;
  }

  for (x = (N + 1) / 2, y = (N + 1) / 2; x > 0;)
  {
    // cout << x << ", " << y << endl;
    if (arr[y][x])
      q.push(arr[y][x]);

    int dx = dir[getMoveDir(y, x) - 1][0], dy = dir[getMoveDir(y, x) - 1][1];
    x += dx;
    y += dy;
  }
}

void print(queue<int> &q)
{
  queue<int> qq;
  while (!q.empty())
  {
    cout << q.front() << " ";
    qq.push(q.front());
    q.pop();
  }
  while (!qq.empty())
  {
    q.push(qq.front());
    qq.pop();
  }
  cout << endl;
}

void bomb(queue<int> &q)
{
  // cout << "before" << endl;
  // print(q);
  while (true)
  {
    bool change = false;
    queue<int> nxt;
    int num = -1, cnt = 0;
    while (!q.empty())
    {
      int t = q.front();
      q.pop();
      if (num == t)
      {
        ++cnt;
      }
      else
      {
        if (cnt < 4)
        {
          for (int j = 0; j < cnt; ++j)
            nxt.push(num);
        }
        else
        {
          ans[num - 1] += cnt;
          change = true;
        }
        num = t;
        cnt = 1;
      }
    }
    if (cnt < 4)
    {
      for (int j = 0; j < cnt; ++j)
        nxt.push(num);
    }
    else
    {
      ans[num - 1] += cnt;
      change = true;
    }

    while (!nxt.empty())
    {
      q.push(nxt.front());
      nxt.pop();
    }
    // cout << "change" << endl;
    // print(q);

    if (!change)
      break;
  }
}

void compress(queue<int> &q)
{
  queue<int> nxt;
  int num = -1, cnt = 0;
  while (!q.empty())
  {
    int t = q.front();
    q.pop();
    if (num == t)
    {
      ++cnt;
    }
    else
    {
      if (num != -1)
      {
        nxt.push(cnt);
        nxt.push(num);
      }

      num = t;
      cnt = 1;
    }
  }
  if (cnt)
  {
    nxt.push(cnt);
    nxt.push(num);
  }
  while (!nxt.empty())
  {
    q.push(nxt.front());
    nxt.pop();
  }
}

void draw(queue<int> &q)
{
  int x = (N + 1) / 2 - 1, y = (N + 1) / 2;

  for (int y = 1; y <= N; ++y)
    for (int x = 1; x <= N; ++x)
      arr[y][x] = 0;

  for (; x > 0 && !q.empty();)
  {
    arr[y][x] = q.front();
    q.pop();
    int dx = dir[getMoveDir(y, x) - 1][0], dy = dir[getMoveDir(y, x) - 1][1];
    x += dx;
    y += dy;
  }
  while (!q.empty())
    q.pop();
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> M;
  for (int y = 0; y < N; ++y)
  {
    for (int x = 0; x < N; ++x)
    {
      cin >> arr[y + 1][x + 1];
    }
  }
  queue<int> q;
  for (int j = 0; j < M; ++j)
  {
    int d, s;
    cin >> d >> s;

    blizard(d, s, q);
    // cout << "blizard" << endl;
    // print(q);
    bomb(q);
    // cout << "bomb" << endl;
    // print(q);
    compress(q);
    // cout << "compress" << endl;
    // print(q);
    draw(q);
  }
  cout << ans[0] + 2 * ans[1] + 3 * ans[2] << "\n";
  return 0;
}
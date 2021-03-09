#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define ONE_TO_TWO 15
#define ONE_TO_THREE 10
#define ONE_TO_FOUR 5
#define HORSES 4
#define TURNS 10

using namespace std;

struct horse
{
  int val;
  int board;
  int idx;
  bool arrived;
};

int boards[5][51] = { {0,},
                  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0, },
                  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 28, 27, 26, 25, 30, 35, 40, 0, },
                  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 25, 30, 35, 40, 0, },
                  {0, 2, 4, 6, 8, 10, 13, 16, 19, 25, 30, 35, 40, 0, }};

int dfs(int val, horse h1, horse h2, horse h3, horse h4, queue<int> nums){
  // 숫자 다 돌림
  if(nums.empty()){
    return val;
  }
  // 움직일 말이 없음
  if(h1.arrived && h2.arrived && h3.arrived && h4.arrived){
    return -99999;
  }
  int ans = val;
  horse nextH1 = h1, nextH2 = h2, nextH3 = h3, nextH4 = h4;
  queue<int> n1 = nums, n2 = nums, n3 = nums, n4 = nums;
  int temp1=0, temp2=0, temp3=0, temp4=0;
  // 1번 말 보내기
  // 도착인지 먼저 파악
  if(!nextH1.arrived){
    // 도착 안했다면
    if(nextH1.board == 1){
      // 1번 보드에 있을 때
      // 보드를 갈아타나 확인
      if(nextH1.idx == ONE_TO_TWO){
        nextH1.board = 2;
      }
      if(nextH1.idx == ONE_TO_THREE){
        nextH1.board = 3;
      }
      if(nextH1.idx == ONE_TO_FOUR){
        nextH1.board = 4;
      }
    }

    // 도착하나 확인
    if(boards[nextH1.board][nextH1.idx + n1.front()] == 0){
      // 도착이다.
      // dfs 한다.
      nextH1.arrived = true; nextH1.idx += n1.front(); n1.pop(); nextH1.val = 0;
      temp1 = dfs(val, nextH1, h2, h3, h4, n1);
    }
    else{
      // 도착 아니다.
      // 일단 보내고
      nextH1.idx += n1.front();
      // 갈 곳에 말이 있나 확인
      if((nextH1.idx == h2.idx && nextH1.board == h2.board && !h2.arrived) || (nextH1.idx == h3.idx && nextH1.board == h3.board && !h3.arrived) || (nextH1.idx == h4.idx && nextH1.board == h4.board && !h4.arrived)){
        temp1 = 0;
      }
      else{
        // 갈 곳에 말이 없다.
        n1.pop();
        nextH1.val = boards[nextH1.board][nextH1.idx];
        temp1 = dfs(val+nextH1.val, nextH1, h2, h3, h4, n1);
      }
    }
  }

  // 2번 말 보내기
  // 도착인지 먼저 파악
  if(!nextH2.arrived){
    // 도착 안했다면
    if(nextH2.board == 1){
      // 1번 보드에 있을 때
      // 보드를 갈아타나 확인
      if(nextH2.idx == ONE_TO_TWO){
        nextH2.board = 2;
      }
      if(nextH2.idx == ONE_TO_THREE){
        nextH2.board = 3;
      }
      if(nextH2.idx == ONE_TO_FOUR){
        nextH2.board = 4;
      }
    }

    // 도착하나 확인
    if(boards[nextH2.board][nextH2.idx + n2.front()] == 0){
      // 도착이다.
      // dfs 한다.
      nextH2.arrived = true; nextH2.idx += n2.front(); n2.pop(); nextH2.val = 0;
      temp2 = dfs(val, h1, nextH2, h3, h4, n2);
    }
    else{
      // 도착 아니다.
      // 일단 보내고
      nextH2.idx += n2.front();
      // 갈 곳에 말이 있나 확인
      if((nextH2.idx == h1.idx && nextH2.board == h1.board && !h1.arrived) || (nextH2.idx == h3.idx && nextH2.board == h3.board && !h3.arrived) || (nextH2.idx == h4.idx && nextH2.board == h4.board && !h4.arrived)){
        temp2 = 0;
      }
      else{
        // 갈 곳에 말이 없다.
        n2.pop();
        nextH2.val = boards[nextH2.board][nextH2.idx];
        temp2 = dfs(val+nextH2.val, h1, nextH2, h3, h4, n2);
      }
    }
  }

  // 3번 말 보내기
  // 도착인지 먼저 파악
  if(!nextH3.arrived){
    // 도착 안했다면
    if(nextH3.board == 1){
      // 1번 보드에 있을 때
      // 보드를 갈아타나 확인
      if(nextH3.idx == ONE_TO_TWO){
        nextH3.board = 2;
      }
      if(nextH3.idx == ONE_TO_THREE){
        nextH3.board = 3;
      }
      if(nextH3.idx == ONE_TO_FOUR){
        nextH3.board = 4;
      }
    }

    // 도착하나 확인
    if(boards[nextH3.board][nextH3.idx + n3.front()] == 0){
      // 도착이다.
      // dfs 한다.
      nextH3.arrived = true; nextH3.idx += n3.front(); n3.pop(); nextH3.val = 0;
      temp3 = dfs(val, h1, h2, nextH3, h4, n3);
    }
    else{
      // 도착 아니다.
      // 일단 보내고
      nextH3.idx += n3.front();
      // 갈 곳에 말이 있나 확인
      if((nextH3.idx == h2.idx && nextH3.board == h2.board && !h2.arrived) || (nextH3.idx == h1.idx && nextH3.board == h1.board && !h1.arrived) || (nextH3.idx == h4.idx && nextH3.board == h4.board && !h4.arrived)){
        temp3 = 0;
      }
      else{
        // 갈 곳에 말이 없다.
        n3.pop();
        nextH3.val = boards[nextH3.board][nextH3.idx];
        temp3 = dfs(val+nextH3.val, h1, h2, nextH3, h4, n3);
      }
    }
  }

  // 4번 말 보내기
  // 도착인지 먼저 파악
  if(!nextH4.arrived){
    // 도착 안했다면
    if(nextH4.board == 1){
      // 1번 보드에 있을 때
      // 보드를 갈아타나 확인
      if(nextH4.idx == ONE_TO_TWO){
        nextH4.board = 2;
      }
      if(nextH4.idx == ONE_TO_THREE){
        nextH4.board = 3;
      }
      if(nextH4.idx == ONE_TO_FOUR){
        nextH4.board = 4;
      }
    }

    // 도착하나 확인
    if(boards[nextH4.board][nextH4.idx + n4.front()] == 0){
      // 도착이다.
      // dfs 한다.
      nextH4.arrived = true; nextH4.idx += n4.front(); n4.pop(); nextH4.val = 0;
      temp4 = dfs(val, h1, h2, h3, nextH4, n4);
    }
    else{
      // 도착 아니다.
      // 일단 보내고
      nextH4.idx += n4.front();
      // 갈 곳에 말이 있나 확인
      if((nextH4.idx == h2.idx && nextH4.board == h2.board && !h2.arrived) || (nextH4.idx == h3.idx && nextH4.board == h3.board && !h3.arrived) || (nextH4.idx == h1.idx && nextH4.board == h1.board && !h1.arrived)){
        temp4 = 0;
      }
      else{
        // 갈 곳에 말이 없다.
        n4.pop();
        nextH4.val = boards[nextH4.board][nextH4.idx];
        temp4 = dfs(val+nextH4.val, h1, h2, h3, nextH4, n4);
      }
    }
  }

  priority_queue<int> tempPQ;
  tempPQ.push(temp1); tempPQ.push(temp2); tempPQ.push(temp3); tempPQ.push(temp4);
  ans = tempPQ.top();
  // if(ans == 218){
    cout << temp1 << ", " << temp2 << ", " << temp3 << ", " << temp4 << "\n";
    cout << "nums: ";
    while(!nums.empty()){
      cout << nums.front() << ", ";
      nums.pop();
    }
    cout << "\n";
  // }
  // cout << temp1 << ", " << temp2 << ", " << temp3 << ", " << temp4 << "\n";
  return ans;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  queue<int> dices;
  for(int i=0; i<TURNS; ++i){
    int temp; cin >> temp;
    dices.push(temp);
  }
  vector<horse> h(4);
  for(int i=0; i<4; ++i){
    h[i].val = 0;
    h[i].board = 1;
    h[i].idx = 0;
    h[i].arrived = false;
  }
  
  h[0].idx = dices.front();
  h[0].val = boards[1][dices.front()];
  dices.pop();
  cout << dfs(h[0].val, h[0], h[1], h[2], h[3], dices);

  return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#define ROOM_SIZE 4

using namespace std;

struct fishInfo
{
  // 물고기의 값과 방향을 저장
  int val;
  int dir;
};


// 값이 작은 물고기부터 꺼내기 위한 priority_queue
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > fish;

// 번호에 대한 방향, idx는 1~8까지임 그래서 9로 함
int direction[9][2] = {{0,0}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}};

// val: 상어가 여태 먹은 값, deep: 상어가 들어갈 깊이, sharkDir: 상어의 방향 번호, tank[][4]: 상어가 움직인 후 어항 판, pq: 살아남은 물고기들의 priority_queue
int dfs(int val, int deep, int sharkDir, pair<int, int> pos, fishInfo tank[][4], priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq){
  // if no space
  // 먼저 상어의 방향에 대해 깊이 deep만큼 갔는데 어항을 벗어나면 여태 먹은 값 val을 리턴한다.
  int sharkRowDeep = pos.first + direction[sharkDir][0]*deep, sharkColDeep = pos.second + direction[sharkDir][1]*deep;
  if(sharkRowDeep < 0 || sharkRowDeep > 3 || sharkColDeep < 0 || sharkColDeep > 3){
    return val;
  }
  
  // tempTank는 tank의 값만 복사한다.
  // tempTank는 물고기들이 움직인 후 어항의 상황을 저장할 것이다.
  fishInfo tempTank[ROOM_SIZE][ROOM_SIZE];
  for(int i=0; i<ROOM_SIZE; ++i){
    for(int j=0; j<ROOM_SIZE; ++j){
      tempTank[i][j] = tank[i][j];
    }
  }

  // fish move
  // pq가 빌 때 까지 물고기들을 작은값부터 뱉어낸다.
  while(!pq.empty()){
    // fishVal은 물고기의 값, fishDir는 물고기의 방향
    int fishVal = pq.top().first, fishDir = pq.top().second;
    // find where is fish
    // fishVal과 일치하는 물고기 위치 찾기
    int row, col;
    bool found=false;
    for(int i=0; i<4 || !found; ++i){
      for(int j=0; j<4 || !found; ++j){
        if(fishVal == tempTank[i][j].val){
          // 물고기를 찾았으면 위치 i,j를 row,col에 저장하고 이중 loop를 나온다.
          row=i; col=j;
          found = true;
        }
      }
    }

    // spin fish
    // 찾은 물고기를 회전시킨다.
    // 1이상 8이하인 이유는 물고기가 한 바퀴 돌아서 제자리 올 때 까지 완전탐색 할려고
    for(int i=1; i<=8; ++i){
      // 물고기의 원래 위치에 물고기의 방향으로 한 칸 이동한다.
      int fishRow = row+direction[fishDir][0], fishCol = col+direction[fishDir][1];
      // sharkDir out of tank or meet shark
      // 만약 이동한 칸이 어항을 벗어나거나 상어가 있다면 fishDir를 1 증가(45도 반시계방향)시키고 continue;
      if(fishRow < 0 || fishRow > 3 || fishCol < 0 || fishCol > 3 || (fishRow == pos.first && fishCol == pos.second)){
        if(fishDir == 8){
          // 물고기 방향이 8이면 증가시킬 수 없으니 1로 바꿔준다.
          fishDir = 1;
        }
        else{
          fishDir++;
        }
        continue;
      }

      // change fish if direction in space and not meet shark
      // 물고기의 방향대로 한 칸 이동이 가능하면 그 칸의 물고기와 스왑한다.
      // temp는 이동할 물고기의 값과 방향을 임시 저장.
      fishInfo temp = {tempTank[row][col].val, fishDir};
      // tempTank[row][col]에는 이동할 곳의 물고기를 저장.
      tempTank[row][col] = tempTank[fishRow][fishCol];
      // 이동할 곳에 이동할 물고기를 넣어서 스왑
      tempTank[fishRow][fishCol] = temp;
      // cout << "tempTank\n";
      // for(int ii=0; ii<4; ++ii){
      //   for(int jj=0; jj<4; ++jj){
      //     cout << tempTank[ii][jj].val << " ";
      //   }
      //   cout << "\n";
      // }
      // cout << "------\n";
      // cout << "change fish " << temp.val << " to " << temp.dir << ", " << tempTank[row][col].val << "\n";
      
      
      // 물고기를 스왑했다면 break;
      break;
    }
    
    // pop fish
    // 물고기를 스왑했으니 pop
    pq.pop();
  }

  // ans는 상어가 여태 먹은 물고기 값의 합.
  int ans = val;
  // ansPos는 상어가 다음으로 갈 곳.
  pair<int, int> ansPos;
  // check shark can eat
  // rrow와 ccol는 상어의 방향*deep
  int rrow = pos.first + direction[sharkDir][0]*deep, ccol = pos.second + direction[sharkDir][1]*deep;
  // 상어의 방향대로 deep만큼 갔는데 어항 벗어나면 return val;
  if(rrow < 0 || rrow > 3 || ccol < 0 || ccol > 3){
    return val;
  }

  // nextFish는 잡아먹힐 물고기
  fishInfo nextFish = tempTank[rrow][ccol];
  if(nextFish.val != 0){
    // 물고기가 있는 곳이면 먹는다.
    // eat fish
    // cout << "shark from " << pos.first << ", " << pos.second << " dir was " << sharkDir << " ->" << direction[sharkDir][0] << ","<<direction[sharkDir][1] << " deep was " << deep << "\n";
    // cout << "nextFish eaten " << nextFish.val << " row: " << rrow << " col: " << ccol << " dir: " << nextFish.dir << "\n";

    // 먹어서 값 증가시키고
    ans += nextFish.val;
    // 그 곳으로 ansPos를 이동시키고(상어 이동)
    ansPos.first = rrow;
    ansPos.second = ccol;
    // 상어가 먹은 물고기의 방향정보 저장하고
    int ansDir = nextFish.dir;
    // 먹은 곳을 0으로 처리
    tempTank[ansPos.first][ansPos.second].val = 0;

    
    // push remain fishes
    // 남은 물고기들을 priority_queue에 담아준다.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> nextPq;
    for(int i=0; i<4; ++i){
      for(int j=0; j<4; ++j){
        if(tempTank[i][j].val != 0){
          // 살아있다면 push
          nextPq.push({tempTank[i][j].val, tempTank[i][j].dir});
        }
      }
    }
    // next dfs
    // 다음 상어의 방향대로 깊이 1부터 깊이 3까지 3번 dfs를 재귀호출
    for(int i=1; i<=3; ++i){
      // cout << "shark dir " << direction[ansDir][0] << ", " << direction[ansDir][1] << " " << " shark deep " << i << "\n";
      // for(int ii=0; ii<4; ++ii){
      //   for(int jj=0; jj<4; ++jj){
      //     cout << tempTank[ii][jj].val << " ";
      //   }
      //   cout << "\n";
      // }
      // cout << "===================\n";

      // temp에 값 받아오고
      int temp = dfs(ans, i, ansDir, {ansPos.first, ansPos.second}, tempTank, nextPq);
      if(temp > ans){
        // temp > ans면 갱신. 가장 큰 숫자 합만큼 먹어야 하니깐.
        ans = temp;
      }
    }
    // 가장 큰 숫자 합 만큼 먹었던거 뱉기.
    // 여태 먹은거 + dfs(깊이 1부터 3까지 갔던 것 중 가장 컸던 dfs)
    return ans;
  }
  else{
    // no fish to eat
    // 먹을 물고기가 없음 그래서 여태 먹은거 return
    return val;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  pair<int, int> shark;
  fishInfo tank[ROOM_SIZE][ROOM_SIZE];

  for(int i=0; i<4; ++i){
    for(int j=0; j<4; ++j){
      if(i==0 && j==0){
        cin >> shark.first >> shark.second;
        // 가장 처음에 상어는 0,0으로 들어오니깐 바로 먹어준다. val=0
        tank[0][0].val = 0; tank[0][0].dir = shark.second;
      }
      else{
        int val, dir; cin >> val >> dir;
        // priority_queue에 넣어서 val이 작은 것 부터 나오도록
        fish.push({val, dir});
        // 어항 초기화
        tank[i][j] = {val, dir};
      }
    }
  }

  // cout << "\n origin tank\n";
  // for(int i=0; i<ROOM_SIZE; ++i){
  //   for(int j=0; j<ROOM_SIZE; ++j){
  //     cout << tank[i][j].val << " ";
  //   }
  //   cout << "\n";
  // }
  // cout << "=------------\n";
  int ans = 0;
  for(int i=1; i<=3; ++i){
    // cout << "shar dir " << shark.second << " shar deep " << i << "\n";

    // 상어가 0,0에서 먹은 물고기의 방향대로 깊이 1, 2, 3만큼 이동해보고 가장 크게 뱉는 dfs를 저장한다.
    int temp = dfs(shark.first, i, shark.second, {0,0}, tank, fish);
    if(temp > ans){
      ans = temp;
    }
  }
  cout << ans;
  

  return 0;
}
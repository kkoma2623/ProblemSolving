#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int N, K;
struct strt{
  bool robot;
  int cnt;
};

deque<strt> dq;

void getInput(){
  cin >> N >> K;
  for(int i=0; i<2*N; ++i){
    int temp; cin >> temp;
    dq.push_back({false, temp});
  }
}

void moveBelt(){
  strt back = dq.back(); dq.pop_back();
  dq.push_front(back);
}

void moveRobot(int n){
  if(!dq[n].robot) return;
  if(n == N-1){
    dq[n].robot = false;
    return;
  }

  if(dq[n+1].robot){
    return;
  }

  if(dq[n+1].cnt >= 1 && dq[n].robot){
    if(n+1 == N-1) {
      dq[n].robot = false;
      dq[n+1].robot = false;
      dq[n+1].cnt -= 1;
      return;
    }
    dq[n].robot = false;
    dq[n+1].robot = true;
    dq[n+1].cnt -= 1;
    return;
  }
}

void putRobot(){
  if(dq[0].cnt >= 1){
    dq[0].robot = true;
    dq[0].cnt -= 1;
  }
}

int checkCnt(){
  int cnt = 0;
  for(int i=0; i<2*N; ++i){
    if(dq[i].cnt <= 0){
      ++cnt;
    }
  }

  return cnt;
}


int solution(){
  getInput();
  int cnt = checkCnt();
  int ret = 0;
  while(cnt < K){
    ++ret;
    moveBelt(); // step 1
    if(dq[N-1].robot){ // robot go down
      dq[N-1].robot = false;
    }
    for(int i=N-2; i>=0; --i){ // step 2
      moveRobot(i);
    }
    putRobot(); // step 3
    cnt = checkCnt();
  }

  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << solution();
  return 0;
}
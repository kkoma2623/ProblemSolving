#include <iostream>
#include <vector>

#define MAX_N 100

using namespace std;

int N;
int albumSize;
vector<int> card;
int recommand[MAX_N+1];
int when[MAX_N+1];

void getInput(){
  cin >> N;
  int stu; cin >> stu;
  for(int i=0; i<stu; ++i){
    int temp; cin >> temp;
    card.push_back(temp);
  }
}

// 학생 번호와 인덱스를 받아옴
void putCard(int stuNum, int index){
  // 추천 목록에 있다면 추천수 하나 늘림
  if(recommand[stuNum]){
    ++recommand[stuNum];
    return;
  }

  // 사진 틀이 비어있다면 사진틀에 하나 추가시킴
  // 앨범 크기 하나 늘림
  if(albumSize < N){
    ++recommand[stuNum];
    ++albumSize;
    when[stuNum] = index;
    return;
  }

  // 사진 틀이 꽉차있고 새로 넣어야 하는 경우
  int minRec = 987654321;
  int outNum = 0;
  for(int stuIter=1; stuIter<=MAX_N; ++stuIter){
    if(recommand[stuIter] == 0){
      continue;
    }
    
    // 가장 적은 추천수를 찾음
    if(minRec > recommand[stuIter]){
      minRec = recommand[stuIter];
      outNum = stuIter;

      continue;
    }

    // 추천수가 같다면 가장 먼저 들어온 애를 뺀다.
    if(minRec == recommand[stuIter]){
      if(when[stuIter] < when[outNum]){
        outNum = stuIter;
      }
    }
  }

  // 빼야 하는 아이
  recommand[outNum] = 0;
  when[outNum] = 987654321;
  // 새로 넣는 아이
  recommand[stuNum] = 1;
  when[stuNum] = index;
}

void solve(){
  getInput();
  for(int i=1; i<=card.size(); ++i){
    putCard(card[i-1], i);
  }

  for(int i=1; i<=MAX_N; ++i){
    if(recommand[i]){
      cout << i << " ";
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}
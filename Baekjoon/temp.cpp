#include <iostream>

using namespace std;

unsigned int PRNG() {
  static unsigned int seed = 5323;
  seed = 8253729 * seed + 2396403;
  
  return seed % 3 + 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int inputNum; cin >> inputNum;
  for(int i=0; i<inputNum; ++i){
    for(int j=0; j<inputNum; ++j){
      cout << PRNG() << " ";
    }
    cout << "\n";
  }

  return 0;
}
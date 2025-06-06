#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<char> st;
string inputString;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> inputString;

  int ret = 0;
  int bars = 0;
  for(int i=0; i<inputString.size(); ++i) {
    if (inputString[i] == '(') {
      st.push('(');
      ++bars;
      continue;
    }

    if (st.top() == '(') {
      st.pop();
      ret += bars - 1;
      bars -= 1;
      st.push(')');
      continue;
    }

    bars -= 1;
    ret += 1;
    st.push(')');
  }

  cout << ret;


  return 0;
}
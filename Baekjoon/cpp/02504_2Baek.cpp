#include <iostream>
#include <stack>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string inputStr;
  cin >> inputStr;

  long long ans = 0;
  long long mul = 1;
  stack<char> st;
  bool multed = false;
  for(int i=0; i<inputStr.size(); ++i){
    switch(inputStr[i]) {
      case '(':
        mul *= 2;
        st.push('(');
        multed = false;
        break;
      case '[':
        mul *= 3;
        st.push('[');
        multed = false;
        break;
      case ')':
        if (st.empty() || st.top() != '(') {
          cout << 0;
          return 0;
        }
        if (!multed) {
          ans += mul;
          multed = true;
        }
        mul /= 2;
        st.pop();
        break;
      case ']':
        if (st.empty() || st.top() != '[') {
          cout << 0;
          return 0;
        }
        if (!multed) {
          ans += mul;
          multed = true;
        }
        mul /= 3;
        st.pop();
        break;
    }
  }

  if(st.empty()) {
    cout << ans;
  } else {
    cout << 0;
  }
  return 0;
}
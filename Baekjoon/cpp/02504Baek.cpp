#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<char> stk;
string st;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> st;
  int temp = 1;
  long long ret = 0;

  for(int i=0; i<st.size(); ++i){
    switch (st[i]) {
      case '(':
        stk.push('(');
        temp *= 2;
        break;
      case '[':
        stk.push('[');
        temp *= 3;
        break;
      case ')':
        if (stk.empty() || stk.top() != '(') {
          // invalid
          cout << 0;
          return 0;
        }
        ret += temp;
        temp /= 2;
        break;
      case ']':
        if (stk.empty() || stk.top() != '[') {
          // invalid
          cout << 0;
          return 0;
        }
        ret += temp;
        temp /= 3;
        break;
      default:
        break;
    }
  }
  if (!stk.empty()) {
    cout << 0;
  } else {
    cout << ret;
  }

  return 0;
}
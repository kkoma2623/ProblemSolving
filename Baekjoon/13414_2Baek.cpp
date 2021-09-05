#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<string> getReverseSortedLog(int &testCases, vector<string> &clickList, set<string> &studentId)
{
  while(testCases--)
  {
    string id; cin >> id;
    clickList.push_back(id);
  }

  vector<string> ret;
  for(auto iter = clickList.rbegin(); iter != clickList.rend(); ++iter)
  {
    if(studentId.find(*iter) == studentId.end())
    {
      ret.push_back(*iter);
      studentId.insert(*iter);
    }
  }

  return ret;
}

void printSuccessStudents(int &lectureSize, vector<string> &clickedStudents)
{
  int i = 0;
  set<string> printedId;
  for(auto iter = clickedStudents.rbegin(); iter != clickedStudents.rend() && i < lectureSize; ++iter)
  {
    if(printedId.find(*iter) == printedId.end())
    {
      cout << (*iter) << "\n";
      ++i;
    }
    
    printedId.insert(*iter);
  }
}

void solve()
{
  set<string> studentId;
  vector<string> clickList;
  int lectureSize, testCases; cin >> lectureSize >> testCases;
  vector<string> clickedStudents = getReverseSortedLog(testCases, clickList, studentId);
  printSuccessStudents(lectureSize, clickedStudents);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}
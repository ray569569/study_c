#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int highnum(float a)
{
  while(a>=10)
  {
    a/=10;
  }
  return int(a);
}
class DecimalBookInfo {
public:
  float _code;
  string _book;
  bool friend operator <(DecimalBookInfo a,DecimalBookInfo b);
  bool friend operator <=(DecimalBookInfo a,DecimalBookInfo b);
  bool friend operator >(DecimalBookInfo a,DecimalBookInfo b);
  bool friend operator >=(DecimalBookInfo a,DecimalBookInfo b); 
  DecimalBookInfo(string name,float code)
  {
    _book = name;
    _code = code;
  }
};

bool operator <(DecimalBookInfo a,DecimalBookInfo b)
{
  if(a._code<b._code)
    return 1;
  else
    return 0;
}
bool operator <=(DecimalBookInfo a,DecimalBookInfo b)
{
  if(a._code<=b._code)
    return 1;
  else
    return 0;
}
bool operator >(DecimalBookInfo a,DecimalBookInfo b)
{
  if(a._code>b._code)
    return 1;
  else
    return 0;
}
bool operator >=(DecimalBookInfo a,DecimalBookInfo b)
{
  if(a._code>=b._code)
    return 1;
  else
    return 0;
}

void PrintBooks(const vector<DecimalBookInfo> &list) {
  int n=list.size();
  cout<<"SubjectNum: "<<highnum(list[0]._code)<<endl;
  cout<<list[0]._book<<" "<<list[0]._code<<endl;
  for(int i=1;i<n;i++)
  {
    if(highnum(list[i]._code)>highnum(list[i-1]._code))
    {
      cout<<"SubjectNum: "<<highnum(list[i]._code)<<endl;
    }
    cout<<list[i]._book<<" "<<list[i]._code<<endl;
  }
}


int main() {
  vector<string> NameLists = {"The Elements of Chemistry",
                              "Chemical Principles",
                              "Computer Organization and Design",
                              "The C++ Programming Language",
                              "The Wealth of Nations",
                              "The Story of Art",
                              "The Origin of Species",
                              "ABC"};
  vector<float> CodeLists = {516.3, 563.4, 490.3, 490.6, 830.7, 120.9, 259.8, 259.8};
  vector<DecimalBookInfo> BookLists;
  for (int i = 0; i < (int)CodeLists.size(); i++) {
    DecimalBookInfo temp(NameLists[i], CodeLists[i]);
    BookLists.push_back(temp);
  }
  sort(BookLists.begin(), BookLists.end());
  PrintBooks(BookLists);
  cout << "\n";

  if (BookLists[3] > BookLists[2])
    cout << "true\n";
  else
    cout << "false\n";

  if (BookLists[3] < BookLists[2])
    cout << "true\n";
  else
    cout << "false\n";

  if (BookLists[1] >= BookLists[2])
    cout << "true\n";
  else
    cout << "false\n";

  if (BookLists[1] <= BookLists[2])
    cout << "true\n";
  else
    cout << "false\n";
}
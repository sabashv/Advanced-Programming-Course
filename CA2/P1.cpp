#include <iostream>
#include <string>
#include <vector>
using namespace std;
void encrypting(string input)
{
  if(input.size()<=2)
  {
      cout<<input;
      return;
  }
  else
  {
   int mid=(input.size()-1)/2;
   cout<<input[mid];
   string leftpart;
   for (int i=0;i<mid;i++)
      leftpart+=input[i];
   string rightpart;
   for (int j=mid+1;j<input.size();j++)
      rightpart+=input[j];
   encrypting(leftpart);
   encrypting(rightpart);
  }
}
int main()
{
  string word;
  cin >> word;
  encrypting(word);
  cout<<endl;
}

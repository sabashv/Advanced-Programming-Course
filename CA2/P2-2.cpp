#include <iostream>
#include <vector>
using namespace std;
vector<int> get_tallest_heights_in_front (const vector<int>& heights,int start_index)
{
  vector<int> resultvec;
  int tallest_height_in_front;
  if(start_index==heights.size()-1)
     tallest_height_in_front=-1;
  else
  {
    tallest_height_in_front=heights[start_index+1];
    for(int i=start_index+2;i<heights.size();i++)
    {
      if(heights[i]> tallest_height_in_front)
         {
            tallest_height_in_front=heights[i];
         }
    }
  }
  if(start_index<heights.size()-1){
     resultvec=get_tallest_heights_in_front(heights,start_index+1);
   }
 resultvec.insert(resultvec.begin(),tallest_height_in_front);
 //resultvec.push_back(num);
 return resultvec;
}
vector<int> get_tallest_heights_in_front(const vector <int>&heights)
{
  return get_tallest_heights_in_front ( heights,0);
}

vector<int>get_height()
{
  vector<int> input;
  int height;
  while(cin>>height)
  {
    input.push_back(height);
  }
  return input;
}
void print_heights(const vector <int> & heights)
{
  cout<<endl;
  for(int i= 0;i<heights.size();i++){
       cout<< heights[i]<<" ";
   }
}
int main()
{
 
  vector<int> heights=get_height();
  vector<int> tallest_heights_in_front=get_tallest_heights_in_front(heights);
  print_heights( tallest_heights_in_front);
  return 0;
}

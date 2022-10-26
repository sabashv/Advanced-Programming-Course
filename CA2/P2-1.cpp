#include <iostream>
#include <vector>
using namespace std;
struct HeightInfo
{
  int height;
  int tallest_height_in_front;
};
int find_tallest_heights_in_front(const vector<HeightInfo*>& height_infos,int start_index)
{
  if(start_index>=height_infos.size()-1){
     return 1;
  }
  height_infos[start_index]->tallest_height_in_front=height_infos[start_index+1]->height;
  for(int i=start_index+2;i<height_infos.size();i++)
    {
      if(height_infos[i]->height > height_infos[start_index]->tallest_height_in_front)
         {
             height_infos[start_index]->tallest_height_in_front=height_infos[i]->height;
         }
    }
  find_tallest_heights_in_front(height_infos,start_index+1);
}
void set_tallest_heights_in_front(const vector <HeightInfo*>&height_infos)
{
  find_tallest_heights_in_front(height_infos,0);
}
vector<HeightInfo*>get_height_infos()
{
  vector<HeightInfo*> inputvec;
  int Height;
  while(cin>>Height)
  { 
   HeightInfo *input_data=new HeightInfo;
   input_data->height=Height;
   input_data->tallest_height_in_front=-1;
   inputvec.push_back(input_data);
  }
  return inputvec;
}
void print_heights(const vector <HeightInfo*> & height_infos)
{
  for(int i=0;i< height_infos.size()-1;i++)
  {
     cout<< height_infos[i]->tallest_height_in_front<<" ";
  }
  cout<<height_infos[height_infos.size()-1]->tallest_height_in_front<<endl;
}
int main()
{
  vector<HeightInfo*> height_infos=get_height_infos();
  set_tallest_heights_in_front(height_infos);
  print_heights(height_infos);
  return 0;
}

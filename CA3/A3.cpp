#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <map>
using namespace std;
struct MovieInfo
{
    string CinemaName;
    string Day;
    string MovieName;
    string StartingTime;
    string FinishingTime;
    string Price;
};
int Find_dayNUM(string Day)
{
    if(Day=="Saturday")
         return 0;
    if(Day=="Sunday")
         return 1;
    if(Day=="Monday")
         return 2;
    if(Day=="Tuesday")
         return 3;
    if(Day=="Wednesday")
         return 4;
    if(Day=="Thursday")
         return 5;
    if(Day=="Friday")
         return 6;
}
int Calculate_Time(string time)
{
	string hour_digits=time.substr(3,5);
    string minute_digits=time.substr(0,2);
    int minut=stoi(minute_digits);
    int hour=stoi(hour_digits);
    return hour+minut*60;
}
vector<string> Create_Day_Vector()
{
   vector<string> DayVector={"Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday"};
   return DayVector;
}
vector<string> HTML_File_Time_boxes()
{
	vector<string> time_boxes;
	int distance_from_left=100,time=8;
	string line="<div class=\"time-box\" style=\"left: "+to_string(distance_from_left)+"px;\"><p>0"+to_string(time)+":00</p></div>";
    time_boxes.push_back(line);
    for(time=10;time<24;time=time+2)
    {
       distance_from_left+=200;
       line=string("<div class=\"time-box\" style=\"left: ")+to_string(distance_from_left)+"px;\"><p>"+to_string(time)+":00</p></div>";
       time_boxes.push_back(line);
    }
    line=string("<div class=\"time-box\" style=\"left: ")+to_string(distance_from_left+200)+"px;\"><p>00:00</p></div>";
    time_boxes.push_back(line);  
    return time_boxes;
}
vector<string> HTML_File_Vertical_Lines()
{
	 vector<string> vertical_lines;
     for(int col=100;col<1800;col=col+100)
     {
         string line="<div class=\"vertical-line\" style=\"left: "+to_string(col)+"px;\"></div>";
         vertical_lines.push_back(line);
     }
     return vertical_lines;
}
vector<string> HTML_File_Days()
{
     vector<string> days;
     vector<string> DayVector=Create_Day_Vector();
     for(int i=0,row=60;i<7;i++,row+=50)
     {
   	  days.push_back("<div class=\"day-box\" style=\"top: "+to_string(row)+"px;\">"+DayVector[i]+"</div>");
     }
     return days;
}
vector<string> HTML_File_Rcord_Boxes(const vector<vector<MovieInfo>> &movies)
{
	 vector<string> record_boxes;
	 for(int m=0;m<movies.size();m++)
     {
      for(int k=0;k<movies[m].size();k++)
      {
         int dayNUM=Find_dayNUM(movies[m][k].Day);
         int StartTime=Calculate_Time(movies[m][k].StartingTime);
   	     int FinishTime=Calculate_Time(movies[m][k].FinishingTime);
         int width=50*((FinishTime-StartTime)/30);
         int left=100+50*((StartTime-480)/30);
         int top=60+dayNUM*50;
         record_boxes.push_back("<div class=\"record-box\" style=\"width: "+to_string(width)+"px; left: "+to_string(left)+"px; top:"+to_string(top)+"px; \">"+movies[m][k].CinemaName+"</div>");
     }
    }
    return record_boxes;
}
void Create_HTML_File(const vector<vector<MovieInfo>> &movies,string moviename)
{
    ofstream HTMLfile(moviename+".html");
    HTMLfile<<"<html lang=\"en\">"<<endl<<"<head>"<<endl
    <<"<title></title>"<<endl<<"<link rel=\"stylesheet\" href=\"./style.css\" />"
    <<endl<<"</head>"<<endl<<"<body>"<<endl;
    vector<string> time_boxes=HTML_File_Time_boxes();
    vector<string> vertical_lines=HTML_File_Vertical_Lines();
    vector<string> days=HTML_File_Days();
    vector<string> record_boxes=HTML_File_Rcord_Boxes(movies);
    for(int i=0;i<time_boxes.size();i++)
    	 HTMLfile<<time_boxes[i]<<endl;
    for(int i=0;i<vertical_lines.size();i++)
         HTMLfile<<vertical_lines[i]<<endl;
    for(int i=0;i<days.size();i++)
   	     HTMLfile<<days[i]<<endl;
    for(int i=0;i<record_boxes.size();i++)
   	     HTMLfile<<record_boxes[i]<<endl;
    HTMLfile<<"</body>"<<endl<<"</html>";
    HTMLfile.close();
}
vector<vector<string>> Read_Input_From_File(string fileaddress)
{
    ifstream inputfile(fileaddress);
    vector<vector<string>> Info_table;
    while (!inputfile.eof()) 
    {
        string line;
        getline(inputfile, line);
        vector<string> *row=new vector<string>;
        string word;
        stringstream ss(line);
        while(getline(ss,word,','))
            row->push_back(word);
        Info_table.push_back(*row); 
    }
    return Info_table;
}
map<string,int> Find_Column(const vector<vector<string>> &inputfile)
{
    map<string,int> inputorder;
    vector<string> inputvector={"MovieName","CinemaName","Day","Price","StartingTime","FinishingTime"};
    for(int i=0;i<7;i++)
     {
     	for(int j=0;j<7;j++)
     	{
     		if(inputfile[0][i]==inputvector[j])
     			inputorder[inputvector[j]]=i;
     	}
    }
    return inputorder;
}
void Print_All_Movie(const vector<string> &movienames)
{
    cout<<movienames[0]<<endl;
    for(int i=1;i<movienames.size();i++)
    {
        if(movienames[i]!=movienames[i-1])
            cout<<movienames[i]<<endl;
    }
}
string Extract_Movie_Name(string inputline)
{
   string moviename=inputline.substr(13,inputline.size());
   return moviename;
}
bool Check_If_Movie_Exists(const vector<vector<string>> &inputfile,string moviename)
{
    map<string,int> inputorder=Find_Column(inputfile);
    for(int i=1;i<inputfile.size()-1;i++)
    {
      if((moviename.compare(inputfile[i][inputorder["MovieName"]]))==0)
         return true;
    }
    return false;
}
void Print_Table(const vector<vector<string>> &table)
{  
   for(int i=0;i<16;i++)
   {  
      for(int j=0;j<175;j++)
         cout<<table[i][j];
      cout<<endl;
   }
}
vector<vector<string>> Create_Table_Frame()
{
   vector<vector<string>> table(16,vector<string>(175," "));
   int firstdigit=0,seconddigit=8,row=2;
   for(int i=10;i<180;i=i+20)
   {
   	if(i==30)
   	{
   		firstdigit=1;
   		seconddigit=0;
   	}
   	if(i==130){
   		firstdigit=2;
   		seconddigit=0;
   	}
   	if(i==170){
   		firstdigit=0;
   		seconddigit=0;
   	}
   	table[0][i]=to_string(firstdigit);
   	table[0][i+1]=to_string(seconddigit);
   	table[0][i+2]=":";
   	table[0][i+3]="0";
   	table[0][i+4]="0";
   	seconddigit+=2;
   }
   vector<string> DayVector=Create_Day_Vector();
   for(int i=0;i<7;i++)
   {
   	 for(int j=0;j<DayVector[i].size();j++)
   		 table[row][j]=DayVector[i][j];
   	 row+=2;
   }
   return table;
}
bool Compare_Two_Movie_Structures(MovieInfo movie1,MovieInfo movie2)
{
    if(movie1.StartingTime!=movie2.StartingTime)
         return movie1.StartingTime<movie2.StartingTime;
    if(movie1.Price!=movie2.Price)
         return movie1.Price<movie2.Price;
    if(movie1.CinemaName!=movie2.CinemaName)
         return movie1.CinemaName<movie2.CinemaName;
}
int Find_Row(string Day)
{
   map <string,int> days;
   vector<string> DayVector=Create_Day_Vector();
   days[DayVector[0]]=2;
   days[DayVector[1]]=4;
   days[DayVector[2]]=6;
   days[DayVector[3]]=8;
   days[DayVector[4]]=10;
   days[DayVector[5]]=12;
   days[DayVector[6]]=14;
   return days[Day];
}
void Update_Table(vector<vector<string>> &table,string CinemaName,int row,int col,int lenght)
{
      table[row-1][col]="+";
      table[row][col]="|";
      table[row+1][col]="+";
      col++;
      for(int k=0;k<CinemaName.size();k++)
      {
          table[row][col]=CinemaName[k];
          col++;
      }
      col=col-CinemaName.size();
      for(int i=0;i<lenght;i++)
      {
         if(table[row-1][col]==" ")
             table[row-1][col]="-";
         if(table[row+1][col]==" ")
             table[row+1][col]="-";
         col++;
      }
      table[row][col]="|";
      table[row-1][col]="+";
      table[row+1][col]="+";
}
vector<vector<string>> Create_Table(const vector<vector<MovieInfo>> &Movies_To_Show)
{
   vector<vector<string>> table=Create_Table_Frame();
   for(int i=0;i<Movies_To_Show.size();i++)
   {
   	 if(Movies_To_Show[i].size()<0)
   	   continue;
   	int row=Find_Row(Movies_To_Show[i][0].Day);
   	for(int j=0;j<Movies_To_Show[i].size();j++)
   	{ 
      int StartTime=Calculate_Time(Movies_To_Show[i][j].StartingTime);
   	  int FinisgTime=Calculate_Time(Movies_To_Show[i][j].FinishingTime);
      int col=10+(((StartTime-480)/30)*5);
      int lenght=(((FinisgTime-StartTime)/30)*5)-1;
      Update_Table(table,Movies_To_Show[i][j].CinemaName,row,col,lenght);
    }
  }
  return table;
}
vector<vector<MovieInfo>> Choose_Times(const vector<vector<MovieInfo>> &movies)
{
   vector<vector<MovieInfo>> selcted_movies;
   for(int j=0;j<movies.size();j++)
   {
   	if(movies[j].size()>0)
   	{
   	  vector<MovieInfo> selcted_movies_in_one_day;
   	  selcted_movies_in_one_day.push_back(movies[j][0]);
      for(int i=1;i<movies[j].size();i++)
      {
         if(selcted_movies_in_one_day[selcted_movies_in_one_day.size()-1].FinishingTime<=movies[j][i].StartingTime)
             selcted_movies_in_one_day.push_back(movies[j][i]);
      }
      if(selcted_movies_in_one_day.size()>0)
         selcted_movies.push_back(selcted_movies_in_one_day);
    }
   }
   return selcted_movies;
}
vector<vector<MovieInfo>> Separate_Days(const vector<MovieInfo> &movietable)
{
   vector<vector<MovieInfo>> movies_in_separate_days;
   vector<string> DayVector=Create_Day_Vector();
   for(int j=0;j<7;j++)
   {
   	vector<MovieInfo> movies;
   	for(int i=0;i<movietable.size();i++)
   	{
      if(movietable[i].Day==DayVector[j])
      {
          movies.push_back(movietable[i]);
      }
    }
    if(movies.size()>0)
         movies_in_separate_days.push_back(movies);
   }
   return movies_in_separate_days;
}
vector<MovieInfo> Create_Movie_Vector(const vector<vector<string>> &input,string moviename)
{
   vector<MovieInfo> Movievector;
   map<string,int> inputorder=Find_Column(input);
   for(int i=1;i<input.size()-1;i++)
    {
      if(moviename==input[i][inputorder["MovieName"]])
      {
         MovieInfo movie;
         movie.MovieName=moviename;
         movie.CinemaName=input[i][inputorder["CinemaName"]];
         movie.Day=input[i][inputorder["Day"]];
         movie.StartingTime=input[i][inputorder["StartingTime"]];
         movie.FinishingTime=input[i][inputorder["FinishingTime"]];
         movie.Price=input[i][inputorder["Price"]];
         Movievector.push_back(movie);
      }
    }
    return Movievector;
}
vector<MovieInfo> Sort_Movievector(vector<MovieInfo> movievector)
{
	sort(movievector.begin(),movievector.end(),Compare_Two_Movie_Structures);
	return movievector;
}
void Show_All_Movies(const vector<vector<string>> &input)
{
   vector<string> movienames;
   map<string,int> inputorder=Find_Column(input);
   for(int i=1;i<input.size()-1;i++)
   {
       movienames.push_back(input[i][inputorder["MovieName"]]);
   }
   sort( movienames.begin(), movienames.end());
   Print_All_Movie(movienames);
}
void Show_Schedule(const vector<vector<string>> &inputfile,string inputline)
{
   string moviename=Extract_Movie_Name(inputline);
   if(!Check_If_Movie_Exists(inputfile,moviename))
      return;
   vector<MovieInfo> movievector=Create_Movie_Vector(inputfile,moviename);
   vector<MovieInfo> SortedMovievector=Sort_Movievector(movievector);
   vector<vector<MovieInfo>> movies_in_separate_days=Separate_Days(SortedMovievector);
   vector<vector<MovieInfo>> Movies_to_show=Choose_Times(movies_in_separate_days);
   vector<vector<string>> table=Create_Table(Movies_to_show);
   Print_Table(table);
   Create_HTML_File(Movies_to_show,moviename);
}
int main(int argc , char *argv[])
{
    vector<vector<string>> inputfile=Read_Input_From_File(argv[1]);
    while(cin)
    {
      int firstcommandSize=14;
      int secondcommandSize=13;
      string line;
      getline(cin,line);
      if(line.size()>=firstcommandSize)
      {
         string input=line.substr(0,firstcommandSize);
         if(input=="GET ALL MOVIES" & line.size()==firstcommandSize)
             Show_All_Movies(inputfile);
         else if(input.substr(0,secondcommandSize)=="GET SCHEDULE ")
             Show_Schedule(inputfile,line);
      }
    }
    return 0;
}
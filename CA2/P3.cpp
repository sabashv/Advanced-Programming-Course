#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
bool findword(vector<vector<char>> Input_table,vector<vector<int>> &result_table, string word, int row, int column,int n, int level) 
{ 
    int word_len = word.length(); 
    if (level == word_len) 
        return true; 
    if (row < 0 || column < 0 || row >= n || column >= n) 
        return false; 
    if (Input_table[row][column] == word[level]) { 
        if(result_table[row][column]==0)
            result_table[row][column] = level+1;  
        char temp = Input_table[row][column]; 
        Input_table[row][column] = 'C'; 
        bool checking_next_character = findword(Input_table,result_table, word, row - 1, column, n, level + 1) |  
                                       findword(Input_table,result_table, word, row + 1, column, n, level + 1) |  
                                       findword(Input_table,result_table, word, row, column - 1, n, level + 1) |  
                                       findword(Input_table,result_table, word, row, column + 1, n, level + 1) |
                                       findword(Input_table,result_table, word, row-1, column + 1, n, level + 1)|
                                       findword(Input_table,result_table, word, row-1, column - 1, n, level + 1)|
                                       findword(Input_table,result_table, word, row+1, column + 1, n, level + 1)|
                                       findword(Input_table,result_table, word, row-1, column + 1, n, level + 1); 
        if(!checking_next_character)
           result_table[row][column] = 0; 
        Input_table[row][column] = temp;
        return checking_next_character; 
    } 
    else
        return false; 
} 
void checkMatch(vector<vector<char>> input_table, string word, int n) 
{ 
    vector<vector<int>> result_table(n,vector<int>(n,0));
    for (int row = 0; row < n; row++) 
    { 
        for (int column = 0; column < n; column++) 
       { 
            if (input_table[row][column] == word[0])
             { 
                if (findword(input_table,result_table,word,row, column, n, 0)) 
                  {
                    cout<<"Yes"<<endl;
                    for (int row = 0; row <n; row++) 
                    {    
                         for (int column = 0; column < n-1; column++)
                            cout << result_table[row][column] << " ";
                         cout<< result_table[row][n-1];
                         cout << endl;
                    }    
                    return; 
                  }
             }
        } 
    } 
    cout<<"No"<<endl;
    return; 
} 
vector<vector<char>> get_table(int n)
{
   vector<vector<char>> table;
   for(int i=0;i<n;++i)
   {
      vector<char> row; 
      for(int j=0;j<n;++j)
      { 
	 char value; 
	 cin >> value; 
         row.push_back(value); 
      }
      table.push_back(row); 
    } 
   return table;
}
int main()
{
  string word;
  int n;
  cin>>word;
  cin>>n;
  vector<vector<char>> table=get_table(n);
  checkMatch(table,word,n);
  return 0;
}

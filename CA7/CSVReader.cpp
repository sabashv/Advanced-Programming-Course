#include "CSVReader.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

CSVReader::CSVReader(string filename, string delm ) 
{
     file_name = filename;
     delimeter = delm;
}
           
vector<vector<string>> CSVReader::getData()
{
    ifstream input_file(file_name);
    vector<vector<string>> dataList;
    string line;
    while (getline(input_file, line))
    {
        vector<string> *row=new vector<string>;
        string word;
        stringstream ss(line);
        while(getline(ss,word,','))
            row->push_back(word);
        dataList.push_back(*row); 
    }
    input_file.close();
    return dataList;
}


#ifndef CSVREADER_H
#define  CSVREADER_H "CSVREADER_H"


#include <string>
#include <vector>

class CSVReader
{
    std::string file_name;
    std::string delimeter;
public:
    CSVReader(std::string filename, std::string delm);
    std::vector<std::vector<std::string>> getData();
};


#endif
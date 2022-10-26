#ifndef Matrix_H
#define  Matrix_H "Matrix_H"


#include <string>
#include <sstream>
#include <vector>

class matrix
{
public:
	matrix(std::vector<std::string> row ,std::vector<std::string> col, std::vector<std::vector<double>> values_);
	matrix();
	int find_row(std::string name);
	void sort_row(int row_number);
	double operator ()(int roe,int col);
	matrix operator *(matrix &second_matrix) const;
	std::string get_name(int column_number);
	int get_song_id(int column_number);
private:
	void swap_column(int column1 , int column2);
	std::vector<std::string> first_row;
	std::vector<std::string> first_column;
	std::vector<std::vector<double>> values;
};


#endif


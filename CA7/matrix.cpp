#include "matrix.hpp"
#include <iostream>
using namespace std;

matrix::matrix(vector<string> row ,vector<string> col, vector<vector<double>> values_)
{
	first_row = row;
	first_column = col;
	values = values_;
}

matrix::matrix()
{}

double matrix::operator()(int row,int col)
{
	return values[row][col];
}


matrix matrix::operator *( matrix &second_matrix) const
{
	matrix result;
	result.first_row = second_matrix.first_row;
	result.first_column = first_column;
	result.values = vector<vector<double>> (first_column.size() ,vector<double>(result.first_row.size()));
	for(int s=0;s<result.first_row.size() ;s++)
	{
		for(int i=0 ;i<first_column.size() ;i++)
		{
			double temp =0;
			for(int j=0;j<first_column.size() ;j++)
			{
				if(values[i][j] != -1)
				{
					int row_number = second_matrix.find_row(first_row[j]);
 					temp +=  values[i][j] * second_matrix(row_number , s);
				}
			}
			result.values[i][s] = double(temp)/double(first_column.size() -1);
		}
	}
	return result;
}


string matrix::get_name(int column_number){return first_row[column_number];}

int matrix::get_song_id(int column_number){return stoi(first_row[column_number]);}

int matrix::find_row(string name)
{
	for(int i=0 ;i<first_column.size() ;i++)
	{
		if(first_column[i] == name)
			return i;
	}
}

void matrix::sort_row(int row_number)
{
	for(int i=0; i<first_row.size() ;i++)
	{
		for(int j=i+1 ; j<first_row.size() ;j++)
		{

			if(values[row_number][i] < values[row_number][j])
				swap_column(i , j);
			else if(values[row_number][i] == values[row_number][j])
			{
				if(first_row[i] > first_row[j])
					swap_column(i , j);
			}
		}
	}
}


void matrix::swap_column(int column1 , int column2)
{
	vector<double> temp_vec;
	for(int m=0 ;m<values.size() ;m++)
	{
		temp_vec.push_back(values[m][column1]);
		values[m][column1] = values[m][column2];
		values[m][column2] = temp_vec[m];
	}
	string temp_name = first_row[column1];
	first_row[column1] = first_row[column2];
	first_row[column2] = temp_name;
}

#include <iostream>
#include <conio.h>
using namespace std;

class Matrix
{
	int **matrix;
	int size_column;
	int size_line;
public :
	Matrix(double c, double l) : size_column(0), size_line(0) {};
	Matrix(double column, double line) : size_column(column), size_line(line) 
	{
		matrix = new int*[size_line];
		for (unsigned int i = 0; i < size_line; ++i)
			matrix[i] = new int*[size_column];
	}
	void Fill(char *File_name)
	{
		FILE *file;
		file = fopen(File_name , "rt");
		if (file == 0)
		{
			printf("Error. File not found!");
			system("pause");
			return;
		}
		fscanf(file, "d")
	}






	~Matrix() 
	{
		for (unsigned int i = 0; i < size_line; ++i)
			delete[]matrix[i];
		delete[]matrix;
	};
};	
ostream & operator << (ostream &out, const Matrix<double> &c)
{
	out << "(" << c.re << ", " << c.im << ")";
	return out;
}
istream & operator >> (istream &in, Matrix<double> &c)
{
	in >> c.re >> c.im;
	return in;
}
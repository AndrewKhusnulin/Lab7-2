
// Lab7.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

template <class T>
class Matrix 
{
	vector < vector <T> > matrix_data;
	vector<T> column_buf;
public:
	~Matrix() 
	{ 
		matrix_data.clear(); 
		column_buf.clear();
	}
	Matrix(string str) { fill_by_file(str); }
	Matrix() {};
	void clear()
	{
		matrix_data.clear();
		column_buf.clear();
	}
	vector<vector<T>> get_raw_data()
	{
		return matrix_data;
	}
	int fill_by_vector( vector<vector<T>>& v)
	{
		matrix_data = v;
		for (auto i = (++matrix_data.begin()); i != matrix_data.end(); ++i)
		{
			if (i->size() != matrix_data.begin()->size())
			{
				cout << "The amount of numbers in rows isn't equal!" << endl;
				matrix_data.clear();
				return 0;
			}
		}
		return 1;
	}
	vector<T>* row( unsigned int i)
	{
		if (i < matrix_data.size())
		{
			vector<T>* buf = &matrix_data[i];
			return buf;
		}
		else
		{
			cout << "Row doesn't exist" << endl;
			return nullptr;
		}
	}
	vector<T>* column( unsigned int i)
	{
		if (i < matrix_data.begin()->size())
		{
			column_buf.clear();
			for (auto j = matrix_data.begin(); j != matrix_data.end(); ++j)
			{	
				column_buf.push_back((*j)[i]);
			}
			vector<T>* ptr = &column_buf;
			return ptr;
		}
		else
		{
			cout << "Column doesn't exist" << endl;
			return nullptr;
		}
	} 
	int fill_by_file( string infile) {
		ifstream file;
		file.open(infile.c_str());
		if (!file.is_open())
		{
			cout << "File could not be opened" << endl;
			return 0;
		}
		else
		{
			string str;
			while (getline(file, str))
			{
				istringstream line(str);
				vector <T> temp;
				T buf;
				while (line >> buf)
				{
					temp.push_back(buf);
				}
				matrix_data.push_back(temp);
			}
			for (auto i = (++matrix_data.begin()); i != matrix_data.end(); ++i)
			{
				if(i->size() != matrix_data.begin()->size())
				{
					cout << "The amount of numbers in rows isn't equal!" << endl;
					matrix_data.clear();
					return 0;
				}
			}
		}
		file.close();	
		return 1;
	}
	void print()
	{
		for (auto i = matrix_data.begin(); i != matrix_data.end(); ++i)
		{
			for (auto j = i->begin(); j != i->end(); ++j)
			{
				cout << *j << "   ";
			}
			cout << endl;
		}
	}
	Matrix sub( Matrix& m2)
	{
		Matrix output;
		Matrix m1;
		m1.fill_by_vector(matrix_data);
		vector<vector<T>> buf1;
		vector<T> buf2;
		if ((m1.row(0)->size() == m2.row(0)->size()) && (m1.column(0)->size() == m2.column(0)->size()))
		{
			for (unsigned int i = 0; i < m1.column(0)->size(); ++i)
			{
				for (unsigned int j = 0; j < m1.row(0)->size(); ++j)
				{
					buf2.push_back((*(m1.row(i)))[j] + (*(m2.row(i)))[j]);
				}
				buf1.push_back(buf2);
				buf2.clear();
			}
		}
		else
			cout << "Matrices aren't equal in dimensions !" << endl;
		output.fill_by_vector(buf1);
		buf1.clear();
		return output;
	}
	Matrix mul( Matrix& m2)
	{
		Matrix output;
		Matrix m1;
		m1.fill_by_vector(matrix_data);
		vector<vector<T>> buf1;
		vector<T> buf2;
		T buf_var = 0;
		if (m1.row(0)->size() == m2.column(0)->size())
		{
			for (unsigned int i = 0; i < m1.column(0)->size(); ++i)
			{
				for (unsigned int j = 0; j < m1.column(0)->size(); ++j)
				{
					for (unsigned int t = 0; t < m1.column(0)->size(); ++t)
					{
						buf_var += ((*(m1.row(i)))[t]) * ((*(m2.column(j)))[t]);
					}
					buf2.push_back(buf_var);
					buf_var = 0;
				}
				buf1.push_back(buf2);
				buf2.clear();
			}
		}
		else
			cout << "Matrices' dimensions aren't suitable for multiplication" << endl;
		output.fill_by_vector(buf1);
		buf1.clear();
		return output;
	}
	Matrix operator+( Matrix& m2)
	{
		return sub(m2);
	}
	Matrix operator*( Matrix& m2)
	{
		return mul(m2);
	}
	bool operator==( Matrix& m2)
	{
		if (matrix_data == m2.get_raw_data())
			return 1;
		else
			return 0;
	}
	void operator=( Matrix& m2)
	{
		matrix_data = m2.get_raw_data();
	}
	template <typename U>
	friend ostream& operator<<(ostream&, const Matrix<U>&);
	template <typename U>
	friend std::istream& operator >> (istream&, Matrix<U>&);
};
template <class T>
ostream& operator<<(ostream& os, const Matrix<T>& m1)
{
	for (auto i = m1.matrix_data.begin(); i != m1.matrix_data.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			os << *j << "   ";
		}
		os << endl;
	}
	return os;
}
template <class T>
istream& operator >> (istream &in, Matrix<T>& m1)
{
	string str;
	in >> str;
	m1.fill_by_file(str);
	return in;
}




#include <memory>
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

template <class T>
class Matrix
{
	vector < vector <T> > MatrixData;
	vector<T> column_temp;
public:
	~Matrix()
	{
		MatrixData.clear();
		column_temp.clear();
	}
	Matrix(string str) { fill_file(str); }
	Matrix() {};
	void clear()
	{
		MatrixData.clear();
		column_temp.clear();
	}
	vector<vector<T>> get_raw_data()
	{
		return MatrixData;
	}
	int fill_vector(vector<vector<T>>& v)
	{
		MatrixData = v;
		for (auto i = (++MatrixData.begin()); i != MatrixData.end(); ++i)
		{
			if (i->size() != MatrixData.begin()->size())
			{
				cout << "The amount of numbers in rows isn't equal!" << endl;
				MatrixData.clear();
				return 0;
			}
		}
		return 1;
	}
	vector<T>* row(unsigned int i)
	{
		if (i < MatrixData.size())
		{
			vector<T>* buf = &MatrixData[i];
			return buf;
		}
		else
		{
			cout << "Row doesn't exist" << endl;
			return nullptr;
		}
	}
	vector<T>* column(unsigned int i)
	{
		if (i < MatrixData.begin()->size())
		{
			column_temp.clear();
			for (auto j = MatrixData.begin(); j != MatrixData.end(); ++j)
			{
				column_temp.push_back((*j)[i]);
			}
			vector<T>* ptr = &column_temp;
			return ptr;
		}
		else
		{
			cout << "Column doesn't exist" << endl;
			return nullptr;
		}
	}
	int fill_file(string infile) {
		ifstream file;
		file.open(infile.c_str());
		if (!file.is_open())
		{
			cout << "File could not be opened" << endl;
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
				MatrixData.push_back(temp);
			}
			for (auto i = (++MatrixData.begin()); i != MatrixData.end(); ++i)
			{
				if (i->size() != MatrixData.begin()->size())
				{
					cout << "The amount of numbers in rows isn't equal!" << endl;
					MatrixData.clear();
					return 0;
				}
			}
		}
		file.close();
		return 1;
	}
	void print()
	{
		for (auto i = MatrixData.begin(); i != MatrixData.end(); ++i)
		{
			for (auto j = i->begin(); j != i->end(); ++j)
			{
				cout << *j << "   ";
			}
			cout << endl;
		}
	}
	Matrix addition(Matrix& m2)
	{
		Matrix output;
		Matrix m1;
		m1.fill_vector(MatrixData);
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
			cout << "Matrixs aren't equal in dimensions !" << endl;
		output.fill_vector(buf1);
		buf1.clear();
		return output;
	}
	Matrix multiplication(Matrix& m2)
	{
		Matrix output;
		Matrix m1;
		m1.fill_vector(MatrixData);
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
			cout << "Matrixs aren't suitable for multiplication" << endl;
		output.fill_vector(buf1);
		buf1.clear();
		return output;
	}
	Matrix operator+(Matrix& m2)
	{
		return addition(m2);
	}
	Matrix operator*(Matrix& m2)
	{
		return multiplication(m2);
	}
	bool operator==(Matrix& m2)
	{
		if (MatrixData == m2.get_raw_data())
			return 1;
		else
			return 0;
	}
	void operator=(Matrix& m2)
	{
		MatrixData = m2.get_raw_data();
	}
	template <typename U>
	friend ostream& operator<<(ostream&, const Matrix<U>&);
	template <typename U>
	friend std::istream& operator >> (istream&, Matrix<U>&);
};
template <class T>
ostream& operator<<(ostream& os, const Matrix<T>& m1)
{
	for (auto i = m1.MatrixData.begin(); i != m1.MatrixData.end(); ++i)
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
istream& operator >> (istream &input, Matrix<T>& m1)
{
	string str;
	input >> str;
	m1.fill_file(str);
	return input;
}

int main()
{

	Matrix<int> m1, m2;
	m1.fill_file("matrix.txt");
	m2.fill_file("matrix.txt");
	cout << "+" << endl;
	cout << m1 + m2 << endl;
	cout << "*" << endl;
	cout << m1*m2 << endl;
	cout << "Compare: " << endl;
	(m1 == m2) ? cout << "Matrix are equal" << endl : cout << "Matrixs arent equal!" << endl;
	system("pause");
	return 0;
}


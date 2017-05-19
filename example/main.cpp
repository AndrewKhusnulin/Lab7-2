#include <iostream>
#include <stdlib.h>

#include "Sem2_Lab7.hpp"
using namespace std;

int main()
{
	Matrix<int> m1, m2;
	vector <vector<int>> v = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	m1.fill_by_vector(v);
	cout << m1;
	return 0;
}

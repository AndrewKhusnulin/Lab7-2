
#include <Lab7-2.hpp>
#include <catch.hpp>

SCENARIO ("ConstructorTest(VectorSuits)"){
	vector <vector<int>> v = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
	Matrix<int> m;
	int rv = m.fill_by_vector(v);
	REQUIRE (rv == 1);
}
SCENARIO ("ConstructorTest(VectorDoesn'tSuit)"){
	vector <vector<int>> v = {{1, 3},{4, 5, 6},{7, 8, 9}};
	Matrix<int> m;
	int rv = m.fill_by_vector(v);
	REQUIRE (rv == 0);
}
SCENARIO ("ColumnTest(ShouldWork)"){
	vector <vector<int>> v = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
	Matrix<int> m;
	m.fill_by_vector(v);
	int rv;
	vector<int> v2 = { 2, 5, 8 };
	if (*m.column(1) == v2)
		rv = 1;
	else
		rv = 0;
	REQUIRE (rv == 1);
}
SCENARIO ("ColumnTest(Shouldn'tWork)"){
	vector <vector<int>> v = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
	Matrix<int> m;
	m.fill_by_vector(v);
	int rv;
	vector<int> v2 = { 2, 1231, 8 };
	if (*m.column(1) == v2)
		rv = 1;
	else
		rv = 0;
	REQUIRE (rv == 0);
}
SCENARIO ("RowTest(ShouldWork)"){
	vector <vector<int>> v = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
	Matrix<int> m;
	m.fill_by_vector(v);
	int rv;
	if (*m.row(1) == v[1])
		rv = 1;
	else
		rv = 0;
	REQUIRE (rv == 1);
}
SCENARIO ("RowTest(ShouldтэеWork)"){
	vector <vector<int>> v = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
	Matrix<int> m;
	m.fill_by_vector(v);
	int rv;
	if (*m.row(1) == v[2])
		rv = 1;
	else
		rv = 0;
	REQUIRE (rv == 0);
}
SCENARIO ("sumTest(ShouldWork)"){
	vector <vector<int>> v = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
	vector <vector<int>> v1 = {{2, 4, 6},{8, 10, 12},{14, 16, 18}};
	Matrix<int> m1, m2;
	m1.fill_by_vector(v);
	m2.fill_by_vector(v);
	REQUIRE ((m1 + m2).get_raw_data() == v1);
}
SCENARIO ("sumTest(Shouldn'tWork)"){
	vector <vector<int>> v = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
	vector <vector<int>> v1 = {{2, 12424, 6},{8, 1420, 12},{14, 1116, 18}};
	Matrix<int> m1, m2;
	m1.fill_by_vector(v);
	m2.fill_by_vector(v);
	REQUIRE ((m1 + m2).get_raw_data() != v1);
}
SCENARIO ("mulTest(ShouldWork)"){
	vector <vector<int>> v = {{1, 2, 0},{0, 1, 2},{3, 0, 2}};
	vector <vector<int>> v1 = {{1, 4, 4},{6, 1, 6},{9, 6, 4}};
	Matrix<int> m1, m2;
	m1.fill_by_vector(v);
	m2.fill_by_vector(v);
	REQUIRE ((m1 * m2).get_raw_data() == v1);
}
SCENARIO ("mulTest(Shouldn'tWork)"){
	vector <vector<int>> v = {{1, 2, 0},{0, 1, 2},{3, 0, 2}};
	vector <vector<int>> v1 = {{1, 412, 4},{6, 112, 6},{9, 612, 4}};
	Matrix<int> m1, m2;
	m1.fill_by_vector(v);
	m2.fill_by_vector(v);
	REQUIRE ((m1 * m2).get_raw_data() != v1);
}

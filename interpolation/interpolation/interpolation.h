#pragma once
#include <cmath>
#include<algorithm>
#include<vector>
using namespace std;

class Interpolation
{
private:
	Interpolation(const Interpolation &a) {};
	Interpolation& operator=(const Interpolation& a) {};

	vector<vector<float>> table; //x, f(x) values
	vector<float> Lagrange_coeff; //basis Lagrange coefficients
	vector<float> x_nearest; // nearest x-coordinates to a specified x value
	vector<float> y_nearest; // correspondind y-values of x_nearest
	float L;				// the value of the Lagrange polynom
	int nodes_numb;			
	float CalcLagrangePolinom(float x);

public:
	Interpolation(){}
	void AddValue(vector<float> column) { table.push_back(column); }
	void SetNodesNumb(int n) { nodes_numb = n; }
	float GetValue() { return L; }

	void LinearInterpolation(float x);
	void SquareInterpolation(float x);
	void CubicInterpolation(float x);

};

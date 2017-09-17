#pragma once
#include<utility>
#include<vector>

struct Point
{
	float x;
	float y;
	Point() { x = 0.0, y = 0.0; }
	Point(float x, float y) :x(x), y(y) {}

};

class Function {
private:
	Function(const Function& f) {};
	Function& operator=(const Function & f) {};

	int n_nodes;					//number of nodes
	std::vector<Point> points;      //x, f(x) data points
public:
	Function() {}
	virtual float Interpolation(const float, const short)  = 0;
	void AddPoint(const Point p) { points.push_back(p); };
	Point GetPoint(const unsigned pos) const { return points.at(pos); }
	void SetNodeNumb(const int n) { n_nodes = n; }
	int GetNodeNumb() { return n_nodes; }
};

class LagrangeInterpolation:public Function {
private:
	short n;               //the degree of the polynomial
	std::vector<Point> domain;
public:
	float Interpolation(const float x, const short polynom_degree);
	void FindDomain(const float x);
	void SetPolyDegree(short deg) { n = deg; }
	short GetPolyDegree() { return n; }
};
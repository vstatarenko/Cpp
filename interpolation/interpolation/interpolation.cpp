#include "interpolation.h"
#include <iostream>

float Interpolation::CalcLagrangePolinom(float x)
{

	while (Lagrange_coeff.size() != x_nearest.size())
	{
		float x_i = x_nearest.at(Lagrange_coeff.size());
		float numerator = 1.0, denominator = 1.0;
		for (size_t i = 0; i < x_nearest.size(); i++)
		{
			if (Lagrange_coeff.size() == i)
				continue;
			numerator *= (x - x_nearest.at(i));
			denominator *= (x_i - x_nearest.at(i));
		}
		Lagrange_coeff.push_back(numerator / denominator);
	}

	float Lagrange_value = 0;
	for (size_t i = 0; i < Lagrange_coeff.size(); i++)
	{
		Lagrange_value += Lagrange_coeff.at(i)*y_nearest.at(i);
	}
	return Lagrange_value;
}


void Interpolation::LinearInterpolation(float x)
{
	if (x < table.front().at(0)  || x > table.back().at(0) || table.size() < 2 )
	{
		cout << "x is out of range or not enough nodes for interpolation" << endl;
		return;
	}


	//finding nearest points to x
	for (size_t i = 1; i < table.size(); i++)
	{
		if (x <= table.at(i).at(0))
		{
			if (x_nearest.size())
			{
				x_nearest.clear();
				y_nearest.clear();
				Lagrange_coeff.clear();
			}

			x_nearest.push_back(table.at(i - 1).at(0)); //x0
			x_nearest.push_back(table.at(i).at(0)); //x1
			y_nearest.push_back(table.at(i - 1).at(1)); //y0
			y_nearest.push_back(table.at(i).at(1)); //y1
			break;
		}
	}
	
	L = CalcLagrangePolinom(x);
}

void Interpolation::SquareInterpolation(float x)
{
	if (x < this->table.front().at(0) || x > this->table.back().at(0) || this->table.size() < 3)
	{
		cout << "x is out of range or not enough nodes for interpolation" << endl;
		return;
	}


	//finding nearest points to x
	float min_dist = 100000000.0;
	for (size_t i = 0; i < table.size() - 2; i++)
	{
		float temp;
		temp = max(max(abs(x - table.at(i).at(0)), abs(x - table.at(i + 1).at(0))),
			abs(x - table.at(i + 2).at(0)));
		if (min_dist > temp)
		{
			if (x_nearest.size())
			{
				x_nearest.clear();
				y_nearest.clear();
				Lagrange_coeff.clear();
			}
			min_dist = temp;
			x_nearest.push_back( table.at(i).at(0) ); //x0
			y_nearest.push_back( table.at(i).at(1) );//y0
			x_nearest.push_back( table.at(i + 1).at(0) );//x1
			y_nearest.push_back( table.at(i + 1).at(1) );//y1
			x_nearest.push_back( table.at(i + 2).at(0) );//x2
			y_nearest.push_back( table.at(i + 2).at(1) );//y2
		}
	}

	
	L = CalcLagrangePolinom(x);
}

void Interpolation::CubicInterpolation(float x)
{
	if (x < this->table.front().at(0) || x > this->table.back().at(0) || this->table.size() < 4)
	{
		cout << "x is out of range or not enough nodes for interpolation" << endl;
		return;
	}

	
	//finding nearest points to x
	float min_dist = 100000000.0;
	for (size_t i = 0; i < table.size() - 3; i++)
	{
		float temp;
		temp = max(max(abs(x - table.at(i).at(0)), abs(x - table.at(i + 1).at(0))), 
			max(abs(x - table.at(i + 2).at(0)), abs( x - table.at(i+3).at(0) ) ) );
		if (min_dist > temp)
		{
			if (x_nearest.size())
			{
				x_nearest.clear();
				y_nearest.clear();
				Lagrange_coeff.clear();
			}
			min_dist = temp;
			x_nearest.push_back(table.at(i).at(0)); //x0
			y_nearest.push_back(table.at(i).at(1));//y0
			x_nearest.push_back(table.at(i + 1).at(0));//x1
			y_nearest.push_back(table.at(i + 1).at(1));//y1
			x_nearest.push_back(table.at(i + 2).at(0));//x2
			y_nearest.push_back(table.at(i + 2).at(1));//y2
			x_nearest.push_back(table.at(i + 3).at(0)); //x3
			y_nearest.push_back(table.at(i + 3).at(1)); //y3
		}
	}

	L = CalcLagrangePolinom(x);
}

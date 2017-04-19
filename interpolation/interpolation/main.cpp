#include<iostream>
#include<fstream>
#include<string>
#include "interpolation.h"

string InterpolationMenu();

int main()
{
	Interpolation func;
	string filename1 = "M:/Users/Valentin/Dropbox/C++/interpolation/testcases/test3_1.txt";
	string filename2 = "M:/Users/Valentin/Dropbox/C++/interpolation/testcases/test3_2.txt";
	string line;
	std::ifstream myfile;
	std::ofstream  result;

	//Read first file
	myfile.open(filename1, std::ifstream::in);
	if (myfile.is_open())
	{
		getline(myfile, line);
		func.SetNodesNumb(stoi(line));
		while (getline(myfile, line))
		{
			float x = 0.0;
			float y = 0.0;
			vector<float> new_column;
			x = stof( line.substr( 0, line.find(" ") ) );
			y = stof(line.substr( line.find(" ") ) );
			new_column.push_back(x);
			new_column.push_back(y);
			func.AddValue(new_column);
		}
		myfile.close();
		line.clear();
	}
	
	else 
		cout << "Unable to open file1" << endl;


	string interpolation_type = InterpolationMenu();
	myfile.open(filename2, std::fstream::in);
	result.open(filename2 + "_result.txt", std::ofstream::out); //output file
	//Read second file and write the result to the new file
	if (myfile.is_open())
	{
		getline(myfile, line);
		result << line + '\n';
		while (getline(myfile, line))
		{
			float x = stof(line);
			float y = 0.0;
			if (interpolation_type == "l")
			{
				func.LinearInterpolation(x);
				y = func.GetValue();
			}

			else if (interpolation_type == "s" )
			{
				func.SquareInterpolation(x);
				y = func.GetValue();
			}

			else if (interpolation_type == "c" )
			{
				func.CubicInterpolation(x);
				y = func.GetValue();
			}
			else
			{
				cout << "unknown type of interpolation" << endl;
			}
			
			line = to_string(x) + " " + to_string(y) + '\n';
			result << line;
		}
		myfile.close();
		result.close();
	}

	else
		cout << "Unable to open file2" << endl;

	system("pause");
	return 0;
}

string InterpolationMenu()
{
	string type;
	cout << "Please select a type of interpolation you need:" << endl
		<< "l         linear" << endl
		<< "s         square" << endl
		<< "c         cubic" << endl;
	getline(std::cin, type);

	if (type != "l" && type != "s" && type != "c")
	{
		type.clear();
		cout << "Please use l, s, c to choose the type of interpolation" << endl;
		return InterpolationMenu();
	}
	
	else
		return type;
}

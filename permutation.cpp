#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;


class Permutation {
	size_t  length;
	int watermark;
	vector<int> watermark_binary;
	std::map<int, int> permutation;
	int **two_DM_Array;
public:
	Permutation(int watermark);                   //Encode watermark to self-inverting-permutation
	Permutation(std::map<int, int> permutation);  //Decode permutation to watermark
	void BinaryWatermark();						  //Watermark Binary representation
	void MatrixRepresentation();				  //Transform self-inverting-permutation to 2 dimensional array

	void PrintPermutation();
	void PrintMatrix();
	~Permutation();
};

int main()
{
	Permutation a(6);
	a.PrintPermutation();
	a.MatrixRepresentation();
	a.PrintMatrix();
	return 0;
}
void Permutation::BinaryWatermark()
{
	do
    	watermark_binary.push_back((watermark & 1));
    while (watermark >>= 1);
    std::reverse(watermark_binary.begin(), watermark_binary.end());
    length = 2*watermark_binary.size() + 1;
}

Permutation::Permutation(int watermark)
{
	this -> watermark = watermark;
	//Step 1
	//Create Binary representation of the watermark
	BinaryWatermark();
	//Step 2 
	//Below I create B* the binary number which has following representation 
	//B* = 11...1||neg(watermark_binary)||0 , where neg(x) is negative function neg(0) = 1, neg(1) = 0 
	//length of B* is 2n+1, where n is the length of watermark_binary
	vector<int> binary_star(watermark_binary.size(), 1);
	vector<int>::iterator start = watermark_binary.begin();
	while (start != watermark_binary.end())
	{
		binary_star.push_back((1 + *start) % 2); //flip B,  not(x) = (1 + x) (mod 2) 
		start++;
	}
	binary_star.push_back(0);

	//Step 3
	//Construct sequence X, Y,  positions of 0's and 1's respectively 
	string X, Y;
	start = binary_star.begin();
	vector<int>::iterator current = binary_star.begin();
	while (current != binary_star.end())
	{
		if (*current == 0){
			X.push_back('1' + current - start);
			current++;
			continue;
		}
		Y.push_back('1' + current - start);
		current++;
	}
	//Step 4
	//Constructing bitonic permutation
	string bitonic_permutation;
	std::reverse(Y.begin(), Y.end());
	bitonic_permutation = X + Y;

	//Step 5
	//Constructing self-invering permutation
	size_t size = bitonic_permutation.size();
	string SiP(size, '*');
	string::iterator first = bitonic_permutation.begin();
	string::iterator last  = bitonic_permutation.end();
	last--;
	if (size % 2 == 0)    //this case looks strange, becase B* has ALWAYS length 2n+1 and it's always odd. 
						  //It's just my doubts, need to clarify it in the article. 
						  //May be it is just for symmetricity 
	{
		while (std::distance(first, last) > 0){       //testcase is needed!
			int z_j = *last  - 48;
			int z_i = *first - 48;
			permutation.insert(pair<int, int> (z_j, z_i));
			permutation.insert(pair<int, int> (z_i, z_j));
			first++;
			last--; 
		}
	}
	if (size % 2 == 1)
	{	
		while (first != last)
		{	
			int z_j = *last  - 48;
			int z_i = *first - 48;
			permutation.insert(pair<int, int> (z_j, z_i));
			permutation.insert(pair<int, int> (z_i, z_j));
			first++;
			last--; 
		}
		int z_midlle = bitonic_permutation[size/2] - 48;
		permutation.insert(pair<int, int> (z_midlle, z_midlle));
	}
}

void Permutation::PrintPermutation()
{	
	for (size_t i = 1; i < length + 1; i++)
		cout << i << " " ;
	cout << endl;

	for (size_t i = 1; i < length + 1; i++)
		cout << "|" << " ";
	cout << endl;

	for (size_t i = 1; i < length + 1; i++)
		cout << permutation[i] << " ";
	cout << endl;
}
void Permutation::PrintMatrix()
{
	if (two_DM_Array == 0 || length == 0)
	{
		cout << "matrix is empty" << endl;
		return;
	}
	for (size_t i = 0; i < length; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			cout << two_DM_Array[i][j] << " ";
		}
		cout << endl;
	}

}
void Permutation::MatrixRepresentation()
{
	int len = permutation.size();
	if (len == 0) 
		return;
	
	two_DM_Array = new int *[len];
	for (int i = 0; i < len; i++)
		*(two_DM_Array + i) = new int [len];

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if (permutation[i + 1] == j + 1)
			{
				two_DM_Array[i][j] = - 1;
			}
			else
			{
				two_DM_Array[i][j] = 0;
			}
		}
	}
}

Permutation::~Permutation()
{
	for( int i = 0 ; i < length ; i++ )
	{
    	delete [] two_DM_Array[i] ;   
	}
	delete [] two_DM_Array;
}
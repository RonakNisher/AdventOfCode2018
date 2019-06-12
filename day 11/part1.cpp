// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include <set>
#include <map>

using namespace std;

int CalculateScore(int x, int y, int serial)
{
	int rackId = x + 10;
	int power = rackId * y + serial;
	power *= rackId;
	
	int hundrethDigit;
	
	if (power <= 99)
	{
		hundrethDigit = 0;
	}
	else
	{
		hundrethDigit = power;
		
		hundrethDigit = hundrethDigit/10; //units place  (1949 -> 194 OR 949 -> 94)
		hundrethDigit = hundrethDigit/10; //tens place   (194 -> 19 OR 94 -> 9)
		
		hundrethDigit = hundrethDigit % 10;
	}
	
	return hundrethDigit - 5;
}

// given top left corner, return score
int CalculatePower(const vector<vector<int>>& grid, int x, int y, int k)
{
	
	int score = 0;
	
	for (int row = 0; row < k; row++)
	{
		for (int col = 0; col < k; col++)
		{
			score += grid[y + row][x + col];
		}
	}
	
	return score;
}

int main()
{
	vector<vector<int>> grid;
	
	int rows = 301;
	int cols = 301;
	
	int serialNumber = 7139;
	
	for (int i = 0; i < rows; i++)
	{
		vector<int> r(cols, 0);
		grid.emplace_back(r);
	}
	
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			grid[y][x] = CalculateScore(x, y, serialNumber);
		}
	}
	
	int maxScore = 0;
	tuple<int, int, int> coords;
	
	for (int k = 1; k <= 300; k++)
	{
		cout<<"k = "<<k<<endl;
		for (int y = 0; y < rows - k - 1; y++)
		{
			for (int x = 0; x < cols - k - 1; x++)
			{
				int score = CalculatePower(grid, x, y, k);
				if (score > maxScore)
				{
					maxScore = score;
					coords = make_tuple(x, y, k);
				}
			}
		}
	}
	
	int testX = 122;
	int testY = 79;
	cout<<"grid[79][122]->"<<grid[testY][testX]<<endl;
	
	cout<<"max score is "<<maxScore<<" at "<<get<0>(coords)<<", "<<get<1>(coords)<<", "<<get<2>(coords)<<endl;
	cout<<"done"<<endl;
	return 0;
}
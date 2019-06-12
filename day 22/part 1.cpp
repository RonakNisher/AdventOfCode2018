// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

void print(vector<vector<char>>& grid)
{
	for (const vector<char>& row : grid)
	{
		for (const char& c : row)
		{
			cout<<c;
		}
		cout<<endl;
	}
}

char getType(int erosionLevel)
{
	int res = erosionLevel % 3;
	
	switch (res)
	{
		case 0:
			return '.'; // rocky
			
		case 1:
			return '='; // wet
			
		case 2:
			return '|'; // narrow
	}
}

long getGeoIndex(vector<vector<int>>& erosionLevels, int x, int y, int targetX, int targetY)
{
	if ((x ==0 && y == 0) || (x == targetX && y == targetY))
		return 0;
		
	if (y == 0)
		return x * 16807;
		
	if (x == 0)
		return y * 48271;
		
	return erosionLevels[y][x-1] * erosionLevels[y-1][x];
}

char calculateErosion(vector<vector<int>>& erosionLevels, int x, int y, int targetX, int targetY, int depth)
{
	long geoIndex = getGeoIndex(erosionLevels, x, y, targetX, targetY);
	int erosionLevel = (geoIndex + depth) % 20183;
	
	erosionLevels[y][x] = erosionLevel;
	
	return getType(erosionLevel);
}

int main()
{
	vector<vector<char>> grid;
	vector<vector<int>> erosionLevels;
	
	int depth = 3339;
	int Y = 715;
	int X = 10;
	
	for (int i = 0; i <= Y; i++)
	{
		vector<char> r(X + 1, '#');
		grid.emplace_back(r);
		
		vector<int> erosionRow(X + 1, '0');
		erosionLevels.emplace_back(erosionRow);
	}
	
	int score = 0;
	
	for (int i = 0; i <= Y; i++)
	{
		for (int j = 0; j <= X; j ++)
		{
			char c = calculateErosion(erosionLevels, j, i, X, Y, depth);
			
			if ( !(i == 0 && j == 0) && !(i == Y && j == Y))
			{
				grid[i][j] = c;
				
				switch (c)
				{
					case '=':
						{
							score += 1; // wet
							break;
						}
						
					case '|':
					{
						score += 2; // narrow
						break;
					}
				}
			}
		}
	}
	
	grid[0][0] = 'M';
	grid[Y][X] = 'T';
	
	// print(grid);
	
	cout<<"Total risk is "<<score<<endl;
	
	cout<<"done"<<endl;
	return 0;
}
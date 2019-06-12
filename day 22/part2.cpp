// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <climits>

using namespace std;

template <typename T>
void print(vector<vector<T>>& grid)
{
	for (const vector<T>& row : grid)
	{
		for (const T& c : row)
		{
			cout<<c<<" ";
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

vector<pair<char, int>> getAvailableGearToSwitchForRockyRegion(char currentRegion)
{
	switch (currentRegion)
	{
		case '.' : // rocky
		{
			return { make_pair('c', 8), make_pair('t', 8) };
		}
		
		case '=' : // wet
		{
			return { make_pair('c', 8) };
		}
		
		case '|' : // narrow
		{
			return { make_pair('t', 8) };
		}
	}
}

vector<pair<char, int>> getAvailableGearToSwitchForWetRegion(char currentRegion)
{
	switch (currentRegion)
	{
		case '.' : // rocky
		{
			return { make_pair('c', 8) };
		}
		
		case '=' : // wet
		{
			return { make_pair('c', 8), make_pair('n', 8) };
		}
		
		case '|' : // narrow
		{
			return { make_pair('n', 8) };
		}
	}
}

vector<pair<char, int>> getAvailableGearToSwitchForNarrowRegion(char currentRegion)
{
	switch (currentRegion)
	{
		case '.' : // rocky
		{
			return { make_pair('t', 8) };
		}
		
		case '=' : // wet
		{
			return { make_pair('n', 8) };
		}
		
		case '|' : // narrow
		{
			return { make_pair('t', 8), make_pair('n', 8) };
		}
	}
}

vector<pair<char, int>> getShortestTime(char currentRegion, char currentObject, char nextRegion)
{
	// cout<<"getShortestTime "<<currentRegion<<" to "<<nextRegion<<" with object "<<currentObject<<endl;
	switch (nextRegion)
	{
		case '.': // rocky
		{
			if (currentObject == 't' || currentObject == 'c')
			{
				return { make_pair(currentObject, 1) } ;
			}
			else
				return getAvailableGearToSwitchForRockyRegion(currentRegion);
			break;
		}
		
		case '=': // wet
		{
			if (currentObject == 'c' || currentObject == 'n')
			{
				return { make_pair(currentObject, 1) } ;
			}
			else
				return getAvailableGearToSwitchForWetRegion(currentRegion);
			break;
		}
		
		case '|': // narrow
		{
			if (currentObject == 't' || currentObject == 'n')
			{
				return { make_pair(currentObject, 1) } ;
			}
			else
				return getAvailableGearToSwitchForNarrowRegion(currentRegion);
			break;
		}
	}
}

void calculateShortestDistance(vector<vector<char>>& grid, vector<vector<int>>& shortestPaths, int x, int y, char object, int targetX, int targetY)
{
	if (x == targetX && y == targetY)
	{
		if (object != 't')
		{
			// cout<<"Did not have a torch"<<endl;
			shortestPaths[y][x] += 7;
			cout<<"New Shortest Dist "<<shortestPaths[y][x]<<endl;
		}
		return;
	}
		
	if (y >= grid.size() || x >= grid[0].size())
		return;
		
	char currentRegion = grid[y][x];
	int currentDist = shortestPaths[y][x];
	
	int currentShortestDistAtTarget = shortestPaths[targetY][targetX];
	
	// cout<<endl;
	// cout<<"currentRegion "<<currentRegion<<", currentDist "<<currentDist<<", currentObject "<<object<<" Pos is X,Y "<<x<<", "<<y<<endl;
	
	// go right
	if ((x + 1) < grid[0].size())
	{
		char regionAtRight = grid[y][x + 1];
		int pathDist = shortestPaths[y][x + 1];
		
		// cout<<"Path at right "<<regionAtRight<<", "<<pathDist<<endl;
		
		vector<pair<char, int>> timeTaken = getShortestTime(currentRegion, object, regionAtRight);
		
		// cout<<"Found "<<timeTaken.size()<<" options "<<endl;
		for (const pair<char, int>& p : timeTaken)
		{
			int newPatDist = currentDist + p.second;
			// cout<<" using "<<p.first<<" ==== "<<pathDist<<" -> "<<newPatDist<<endl;
			
			if (newPatDist < pathDist && newPatDist <= currentShortestDistAtTarget)
			{
				shortestPaths[y][x + 1] = newPatDist;
				calculateShortestDistance(grid, shortestPaths, x + 1, y, p.first, targetX, targetY);
			}
		}
		
	}
	
	// go left
	if ((x - 1) >= 0)
	{
		char regionAtLeft = grid[y][x - 1];
		int pathDist = shortestPaths[y][x - 1];
		
		// cout<<"Path at right "<<regionAtLeft<<", "<<pathDist<<endl;
		
		vector<pair<char, int>> timeTaken = getShortestTime(currentRegion, object, regionAtLeft);
		
		// cout<<"Found "<<timeTaken.size()<<" options "<<endl;
		for (const pair<char, int>& p : timeTaken)
		{
			int newPatDist = currentDist + p.second;
			// cout<<" using "<<p.first<<" ==== "<<pathDist<<" -> "<<newPatDist<<endl;
			
			if (newPatDist < pathDist && newPatDist <= currentShortestDistAtTarget)
			{
				shortestPaths[y][x - 1] = newPatDist;
				calculateShortestDistance(grid, shortestPaths, x - 1, y, p.first, targetX, targetY);
			}
		}
		
	}
	
	// go down
	if ((y + 1) < grid.size())
	{
		char regionAtDown = grid[y + 1][x];
		int pathDist = shortestPaths[y + 1][x];
		
		// cout<<"Path at down "<<regionAtDown<<", "<<pathDist<<endl;
		
		vector<pair<char, int>> timeTaken = getShortestTime(currentRegion, object, regionAtDown);
		
		// cout<<"Found "<<timeTaken.size()<<" options "<<endl;
		for (const pair<char, int>& p : timeTaken)
		{
			int newPatDist = currentDist + p.second;
			// cout<<" using "<<p.first<<" ==== "<<pathDist<<" -> "<<newPatDist<<endl;
			
			if (newPatDist < pathDist && newPatDist <= currentShortestDistAtTarget)
			{
				shortestPaths[y + 1][x] = newPatDist;
				calculateShortestDistance(grid, shortestPaths, x, y + 1, p.first, targetX, targetY);
			}
		}
		
	}
	
	// up
	if ((y - 1) >= 0)
	{
		char regionAtUp = grid[y - 1][x];
		int pathDist = shortestPaths[y - 1][x];
		
		// cout<<"Path at up "<<regionAtUp<<", "<<pathDist<<endl;
		
		vector<pair<char, int>> timeTaken = getShortestTime(currentRegion, object, regionAtUp);
		
		// cout<<"Found "<<timeTaken.size()<<" options "<<endl;
		for (const pair<char, int>& p : timeTaken)
		{
			int newPatDist = currentDist + p.second;
			// cout<<" using "<<p.first<<" ==== "<<pathDist<<" -> "<<newPatDist<<endl;
			
			if (newPatDist < pathDist && newPatDist <= currentShortestDistAtTarget)
			{
				shortestPaths[y - 1][x] = newPatDist;
				calculateShortestDistance(grid, shortestPaths, x, y - 1, p.first, targetX, targetY);
			}
		}
		
	}
	
	
	// break;
}

int main()
{
	vector<vector<char>> grid;
	vector<vector<int>> erosionLevels;
	vector<vector<int>> shortestPaths;
	
	int depth = 3339; // 510; 
	// int depth =  510; 
	int targetX = 10;
	int targetY = 715;
	// int targetY = 10; // 715
	int Y = targetY + 0; // 715;
	int X = targetX + 0;
	
	for (int i = 0; i <= Y; i++)
	{
		vector<char> r(X + 1, '#');
		grid.emplace_back(r);
		
		vector<int> erosionRow(X + 1, '0');
		erosionLevels.emplace_back(erosionRow);
		
		vector<int> shortestPath(X + 1, INT_MAX);
		shortestPaths.emplace_back(shortestPath);
	}
	
	
	int score = 0;
	
	for (int i = 0; i <= Y; i++)
	{
		for (int j = 0; j <= X; j ++)
		{
			grid[i][j] = calculateErosion(erosionLevels, j, i, targetX, targetY, depth);
		}
	}
	
	// print(grid);
	cout<<endl;
	
	grid[0][0] = '.';
	grid[targetY][targetX] = '.';
	
	shortestPaths[0][0] = 0;
	calculateShortestDistance(grid, shortestPaths, 0, 0, 't', targetX, targetY);
	
	// print(grid);
	cout<<endl<<endl;
	// print(shortestPaths);
	// print(grid);
	
	cout<<"shortestPath is "<<shortestPaths[targetY][targetX]<<endl;
	
	cout<<"done"<<endl;
	return 0;
}
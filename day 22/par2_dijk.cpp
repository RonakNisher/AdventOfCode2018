// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <tuple>
#include <map>
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

bool Compare(tuple<int, int, char, int>& lhs, tuple<int, int, char, int>& rhs)
{
	return get<3>(lhs) > get<3>(rhs);
}

void calculateShortestDistance(vector<vector<char>>& grid, vector<vector<int>>& shortestPaths, int x, int y, char object, int targetX, int targetY)
{
	priority_queue<tuple<int, int, char, int>, vector<tuple<int, int, char, int>>, function<bool(tuple<int, int, char, int>&, tuple<int, int, char, int>&)>> nodesToBeProcessed(Compare); // x,y, currentObject, currentDist
	// priority_queue<tuple<int, int, char, int>, vector<tuple<int, int, char, int>>> nodesToBeProcessed; // x,y, currentObject, currentDist
	
	// map<tuple<int, int, char>> visitedStates; // x, y, object
	
	tuple<int, int, char, int> startPos = make_tuple(0, 0, 't', 0);
	// visitedStates[make_tuple(0, 0, 't')] = 1;
	
	nodesToBeProcessed.push(startPos);
	
	
	while (!nodesToBeProcessed.empty())
	{
		
		tuple<int, int, char, int> current = nodesToBeProcessed.top();
		nodesToBeProcessed.pop();
		
		int currentX = get<0>(current);
		int currentY = get<1>(current);
		char currentObject = get<2>(current);
		int currentDist = get<3>(current);
		
		// cout<<currentY<<", "<<currentX<<" : "<<currentObject<<" at "<<currentDist<<endl;
		// cout<<"currentDist "<<currentDist<<" > shortestPath "<<shortestPaths[currentY][currentX]<<endl;
		if (currentDist > shortestPaths[currentY][currentX])
			continue;
		
		if (currentX == targetX && currentY == targetY)
		{
			cout<<"Found target "<<endl;
			if (currentObject == 't')
			{
				cout<<"Shortest Dist "<<currentDist<<endl;
				break;
			}
			else
			{
				cout<<" no torch "<<currentDist<<" old sp "<<shortestPaths[currentY][currentX]<<endl;
				shortestPaths[currentY][currentX] = currentDist + 7;
				currentDist += 7;
				break;
			}
		}
		
		vector<pair<int, int >> nextLocations = {{currentX - 1, currentY}, {currentX + 1, currentY}, {currentX, currentY - 1}, {currentX, currentY + 1}};
		
		for (const pair<int, int> nextLocation : nextLocations)
		{
			int nextX = nextLocation.first;
			int nextY = nextLocation.second;
			
			if ( nextX < 0 || nextY < 0 || nextX >= grid[0].size() || nextY >= grid.size())
				continue;
				
			char nextRegion = grid[nextY][nextX];
			
			// cout<<"checking node at "<<nextY<<", "<<nextX<<" region "<<nextRegion<<endl;
			
			// process nodes which do not require an object switch
			if ( (currentObject == 't' && nextRegion == '=') /*wet*/
				|| (currentObject == 'c' && nextRegion == '|' /*narrow*/) 
				|| (currentObject == 'n' && nextRegion == '.' /*rock*/))
					continue;
			
			int newDist = currentDist + 1;
			if (newDist < shortestPaths[nextY][nextX])
			{
				// cout<<"adding node at "<<nextY<<", "<<nextX<<endl;
				shortestPaths[nextY][nextX] = newDist;
				// cout<<nextY<<", "<<nextX<<" : "<<shortestPaths[nextY][nextX]<<endl;
				nodesToBeProcessed.push(make_tuple(nextX, nextY, currentObject, newDist));
			}
		}
		
		// process a switch
		
		char currentRegion = grid[currentY][currentX];
		vector<char> objects = {'t', 'c', 'n'};
		for (char c : objects)
		{
			// already processed
			if (c == currentObject)
				continue;
				
			// digregard combinations which are not possible
			if ((c == 't' && currentRegion == '=') /*wet*/
				|| (c == 'c' && currentRegion == '|' /*narrow*/) 
				|| (c == 'n' && currentRegion == '.' /*rock*/))
					continue;
					
			// int newDist = currentDist + 7;
			
			vector<pair<int, int >> nextLocations = {{currentX - 1, currentY}, {currentX + 1, currentY}, {currentX, currentY - 1}, {currentX, currentY + 1}};
			
			for (const pair<int, int> nextLocation : nextLocations)
			{
				int nextX = nextLocation.first;
				int nextY = nextLocation.second;
				
				if ( nextX < 0 || nextY < 0 || nextX >= grid[0].size() || nextY >= grid.size())
					continue;
					
				char nextRegion = grid[nextY][nextX];
				
				// cout<<"checking node at "<<nextY<<", "<<nextX<<" region "<<nextRegion<<endl;
				
				int newDist = currentDist + 8;
				if (newDist <= shortestPaths[nextY][nextX])
				{
					// cout<<"adding switch  at "<<nextY<<", "<<nextX<<" object "<<c<<endl;
					shortestPaths[nextY][nextX] = newDist;
					nodesToBeProcessed.push(make_tuple(nextX, nextY, c, newDist));
				}
			}
			
			// if (newDist <= shortestPaths[nextY][nextX])
			// {
			// 	shortestPaths[nextY][nextX] = newDist;
			// 	nodesToBeProcessed.push(make_tuple(nextX, nextY, currentObject, newDist));
			// }
		}
	}
	
}

int main()
{
	vector<vector<char>> grid;
	vector<vector<int>> erosionLevels;
	vector<vector<int>> shortestPaths;
	
	int depth = 3339;
	// int depth =  510; 
	int targetX = 10;
	int targetY = 715;
	// int targetY = 10;
	int Y = targetY + 2000;
	int X = targetX + 2000;
	
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
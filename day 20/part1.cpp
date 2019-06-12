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

void makeDoor(vector<vector<char>>& grid, int row, int col, char c)
{
	grid[row][col] = c;
}

void makeRoom(vector<vector<char>>& grid, int row, int col)
{
	grid[row][col] = '.';
}

int makeMap(vector<vector<char>>& grid, int& row, int& col, string& line, int& currentPos, stack<pair<int, int>>& savedPositions)
{
	if (currentPos >= line.size())
		return currentPos;
		
	char c = line[currentPos];
	
	// cout<<c<<" currentPos "<<row<<", "<<col<<" savedPos "<<savedRow<<", "<<savedCol<<endl;

	switch(c)
	{
		case 'W':
		{
			makeDoor(grid, row, col - 1, '|');
			col = col - 2;
			makeRoom(grid, row, col);
			break;
		}
		
		case 'E':
		{
			makeDoor(grid, row, col + 1, '|');
			col = col + 2;
			makeRoom(grid, row, col);
			break;
		}
		
		case 'N':
		{
			makeDoor(grid, row - 1, col, '-');
			row = row - 2;
			makeRoom(grid, row, col);
			break;
		}
		
		case 'S':
		{
			makeDoor(grid, row + 1, col, '-');
			row = row + 2;
			makeRoom(grid, row, col);
			break;
		}
		
		case '(':
		{
			savedPositions.push(make_pair(row, col));
			break;
		}
		
		case ')':
		{
			pair<int, int> savedPosition = savedPositions.top();
			row = savedPosition.first;
			col = savedPosition.second;
			
			savedPositions.pop();
			break;
		}
		
		case '|':
		{
			pair<int, int> savedPosition = savedPositions.top();
			row = savedPosition.first;
			col = savedPosition.second;
			break;
		}
	}
	
	currentPos++;
	
	makeMap(grid, row, col, line, currentPos, savedPositions);
}

int findFurthestRoom(vector<vector<char>>& grid, int row, int col, int currentCount, vector<vector<bool>>& visited)
{
	
	char currentChar = grid[row][col];
	// cout<<currentChar<<" at "<<row<<", "<<col<<endl;
	
	if (currentChar == '#' || visited[row][col] == true)
	{
		visited[row][col] = true;
		return currentCount;
	}
	
	visited[row][col] = true;
		
	if (currentChar == '.')
	{
		currentCount++;
		
	}
		
		int leftCount = findFurthestRoom(grid, row, col - 1, currentCount, visited);
		int rightCount = findFurthestRoom(grid, row, col + 1, currentCount, visited);
		int topCount = findFurthestRoom(grid, row - 1, col, currentCount, visited);
		int bottomCount = findFurthestRoom(grid, row + 1, col, currentCount, visited);
		
		return max(max(leftCount, rightCount), max(topCount, bottomCount));
	
	// if (currentChar == '|' && dir == "right")
	// 	return findFurthestRoom(grid, row, col + 1, currentCount, "right");
		
	// if (currentChar == '|' && dir == "left")
	// 	return findFurthestRoom(grid, row, col - 1, currentCount, "left");
		
	// if (currentChar == '-' && dir == "top")
	// 	return findFurthestRoom(grid, row - 1, col, currentCount, "top");
		
	// if (currentChar == '|' && dir == "bottom")
	// 	return findFurthestRoom(grid, row - 1, col, currentCount, "bottom");
		
	return currentCount;
}


int main()
{
	vector<vector<char>> grid;
	vector<vector<bool>> visited;
	stack<pair<int, int>> savedPositions;
	
	int rows = 500;
	int cols = 500;
	
	for (int i = 0; i < rows; i++)
	{
		vector<char> r(cols, '#');
		grid.emplace_back(r);
		
		vector<bool> rv(cols, false);
		visited.emplace_back(rv);
	}
	
	string line;
	string delimiters = " ";
	ifstream myfile ("input.txt");
	
	if (myfile.is_open())
	{
		getline(myfile, line);
		myfile.close();
	}
	
	int startRow = rows / 2;
	int startCol = cols / 2;
	int row = startRow;
	int col = startCol;
	
	grid[startCol][startRow] = 'X';
	char currentChar;
	
   int startPos = 0;
   makeMap(grid, row, col, line, startPos, savedPositions);
	
	print(grid);
	
	int furthestRoomDoors = 0;
	furthestRoomDoors = findFurthestRoom(grid, startRow, startCol, 0, visited);
	cout<<"furthestRoomDoors "<<furthestRoomDoors<<endl;
	cout<<line<<endl;
	cout<<"done"<<endl;
	return 0;
}
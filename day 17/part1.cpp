// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <utility>
#include <algorithm>    // std::find

using namespace std;


vector<string> split(string input, const string& delimiters)
{
	vector<string> res;
	
	string val = "";
	for (auto i : input) {
		if(!isspace(i) && delimiters.find(i) == -1)
		{
			val.push_back(i);
		}
		else
		{
			if (val != "")
			{
				res.push_back(val);
				val = "";
			}
		}
	}
	
	if(val != "")
		res.push_back(val);
	return res;
}

pair<bool, int> fillWater(vector<vector<char>>& , int , int , int );

struct vein
{
	int x;
	int y;
	
	vein(int x, int y) :
	x(x),
	y(y)
	{};
	
	void print()
	{
		cout<<"x = "<<x<<". y = "<<y<<endl;
	}
};

void print(vector<vector<char>>& area)
{
	// int startX = 494;
	int startX = 400;
	for (const vector<char>& row : area)
	{
		for (int c = startX; c < row.size(); c ++)
		{
			cout<<row[c];
		}
		cout<<endl;
	}
}

pair<bool, int> fillGridSideways(vector<vector<char>>& grid, int x, int y, int direction, int yMax)
{
	// if (x >= 599)
	// cout<<"fillGridSideways y,x "<<y<<", "<<x<<" direction "<<direction<<endl;
	bool overflowFound = false;
	bool fillSideways = true;
	int count = 0;
	int nextX = x;
	while (true)
	{
		nextX += direction;
		
		if (nextX < 0 || nextX >= grid[0].size())
			break;
		
		char nextChar = grid[y][nextX];
		char nextCharBase = grid[y + 1][nextX];
		// cout<<nextChar<<" over "<<nextCharBase<<endl;
		if (nextChar == '#' || nextChar == '|')
		{
			break;
		}
		else if (nextChar == '.')
		{
			// if (y == 22)
				// cout<<" | at "<<y<<", "<<nextX<<endl;
			grid[y][nextX] = '|';
			count++;
			
			if (nextCharBase == '.' && !overflowFound)
			{
				// overflowFound = true;
				// break;
				
				int overflowCount = 0;
				bool fillSideways = false;
				tie(fillSideways, overflowCount) = fillWater(grid, yMax, nextX, y + 1);
				if (!fillSideways)
				{
					overflowFound = true;
					break;
				}
					
				// if (y == 11)
					// cout<<"fillSideways "<<fillSideways<<" y, x "<<y+1<<", "<<nextX<<endl;
				count += overflowCount;
		
				// break;
			}
		}
	}
	
	return {overflowFound, count};
}

void fillWithWater(vector<vector<char>>& grid, int x, int y)
{
	if (x < 0 || x >= grid[0].size())
		return;
		
	// fill left hand side
	int lc = 0;
	char currentChar = grid[y][x];
	int i = x;
	while (currentChar != '#')
	{
		if (i < 0)
			break;
			
		grid[y][i] = '~';
		i--;
		currentChar = grid[y][i];
		lc++;
	}
	
	// fill right hand side
	int rc = 0;
	currentChar = grid[y][x + 1];
	i = x + 1;
	while (currentChar != '#')
	{
		if (i >= grid[0].size())
			break;
			
		grid[y][i] = '~';
		i++;
		currentChar = grid[y][i];
		rc++;
	}
	
	// cout<<"fill with water at "<<y<<", "<<x<<" -> lc "<<lc<<" rc "<<rc<<endl;
}

pair<bool, int> fillWater(vector<vector<char>>& grid, int yMax, int x, int y)
{
	// if (grid[y][x] == '|')
	// 	cout<<"hdsklllllllllllllllllllllllllllllssahhhhl ---- "<<y<<", "<<x<<endl;
	
	// if (y >= yMax)
		// cout<<"fillWater "<<y<<", "<<x<<endl;
		
	if (y > yMax || grid[y][x] == '|')
		return {false /*fillSideways*/, 0 /*count*/};
		
	if (grid[y][x] == '#')
		return {true /*fillSideways*/, 0 /*count*/};
		
	bool fillSideways;
	int count = 1;
	int bottomCount = 0;
	
		
	grid[y][x] = '|';
	
	tie(fillSideways, bottomCount) = fillWater(grid, yMax, x, y + 1);
	
	// cout<<"Bottom Count "<<bottomCount<<" at y,x "<<y<<", "<<x<<endl;
	count += bottomCount;
	
	if (fillSideways)
	{
		// cout<<"Fill sidways "<<y<<", "<<x<<endl;
		
		bool overflowFoundRight;
		bool overflowFoundLeft;
		int countRight;
		int countLeft;
		
		tie(overflowFoundRight, countRight) = fillGridSideways(grid, x, y, 1 /*right*/, yMax);
		
		tie(overflowFoundLeft, countLeft) = fillGridSideways(grid, x, y, -1 /*left*/, yMax);
		
		// cout<<" countRight "<<countRight<<", overflowFoundRight "<<overflowFoundRight<<endl;
		// cout<<" countLeft "<<countLeft<<", overflowFoundLeft "<<overflowFoundLeft<<endl;
		// cout<<"y, x "<<y<<", "<<x<<" Returning count "<<count + countRight + countLeft<<endl;
		// cout<<"y, x "<<y<<", "<<x<<" overflowFoundLeft "<<overflowFoundLeft<<" overflowFoundRight "<<overflowFoundRight<<endl;
		// cout<<endl;
		
		if (!overflowFoundLeft && !overflowFoundRight)
			fillWithWater(grid, x, y);
		
		return { !(overflowFoundRight || overflowFoundLeft), count + countRight + countLeft};
	}
	else
	{
		return {false, count};
	}
}

int main()
{ 
	string line;
	string delimiters = " ,=.";
	ifstream myfile ("input.txt");
	
	vector<vein> input;
	int minX = INT_MAX;
	int maxX = 0;
	int minY = INT_MAX;
	int maxY = 0;
	
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
			vector<string> words = split(line, delimiters);

			if (words[0] == "x")
			{
				int xVal = stoi(words[1]);
				int yValStart = stoi(words[3]);
				int yValEnd = stoi(words[4]);
				
				for (int i = yValStart; i <= yValEnd; i++)
					input.emplace_back(xVal, i);
					
				if (xVal > maxX)
				{
					maxX = xVal;
				}
				else if (xVal < minX)
				{
					minX = xVal;
				}
				
				if (yValStart < minY)
					minY = yValStart;
				if (yValEnd > maxY)
					maxY = yValEnd;
			}
			else
			{
				int yVal = stoi(words[1]);
				int xValStart = stoi(words[3]);
				int xValEnd = stoi(words[4]);
				
				for (int i = xValStart; i <= xValEnd; i++)
					input.emplace_back(i, yVal);
					
				if (yVal > maxY)
				{
					maxY = yVal;
				}
				else if (yVal < minY)
				{
					minY = yVal;
				}
				
				if (xValStart < minX)
					minX = xValStart;
				if (xValEnd > maxX)
					maxX = xValEnd;
			}
		}
		myfile.close();
	}
	// cout<<"size is "<<input.size()<<endl;
	
	// int rows = maxY - minY + 2;
	// int cols = maxX - minX + 3;
	// cout<<"limits are X: "<<minX<<" to "<<maxX<<" and Y: "<<minY<<" to "<<maxY<<endl;
	// cout<<"rows, cols "<<rows<<", "<<cols<<endl;
	
	vector<vector<char>> grid;
	for (int r = 0; r <= maxY; r++)
	{
		vector<char> row(maxX + 2, '.');
		grid.emplace_back(row);
	}
	
	for (const vein& v : input)
	{
		grid[v.y][v.x] = '#';
	}
	
	grid[0][500] = '+'; // water
	
	// print(grid);
	
	int res;
	
	tie(ignore, res) = fillWater(grid, maxY, 500, 1);
	// tie(ignore, res) = fillWater(grid, 60, 500, 1);
	
	// cout<<endl;
	// cout<<"grid size "<<grid.size()<<" rows and cols "<<grid[0].size()<<endl;
	cout<<" Result is "<<res<<endl;
	
	
	// print(grid
	int final = 0;
	int final2 = 0;
	for (int i = minY; i < grid.size(); i++)
	{
		for (int j = 0; j < maxX; j++)
		{
			char c = grid[i][j];
			if (c == '|' || c =='~')
				final++;
			
			if (c == '~')
				final2++;
		}
	}
	
	// int final = 0;
	
	// ofstream outputfile ("output.txt");
	// if (outputfile.is_open())
	// {
	// 	// myfile << "This is another line.\n";
	// 	for (const vector<char>& row : grid)
	// 	{
	// 		for (char c : row)
	// 		{
	// 			if (c == '|' || c =='~')
	// 				final++;
	// 			outputfile<<c;
	// 		}
	// 		outputfile<<"\n";
	// 	}
		
	// 	outputfile.close();
	// }
	
	cout<<"final res is "<<final<<endl;
	cout<<"final res 2 is  "<<final2<<endl;
	cout<<"Done"<<endl;

	return 0;
}
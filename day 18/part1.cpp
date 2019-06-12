// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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

void print( vector<vector<char>>& area)
{
	for (const vector<char>& row : area)
	{
		for (const char& c : row)
		{
			cout<<c;
		}
		cout<<endl;
	}
}

char getNewRegion(const vector<vector<char>>&area, int i, int j, int rows, int cols)
{
	int noOfTrees = 0;
	int noOfLumberyards = 0;
	
	const vector<pair<int, int>> adjacentPositions = { {i + 1, j}, {i - 1, j}, {i, j + 1}, {i, j - 1},
										{i - 1, j - 1}, {i - 1, j + 1}, {i + 1, j - 1}, {i + 1, j + 1} };
										
	for (const pair<int, int>& position : adjacentPositions)
	{
		int r = position.first;
		int c = position.second;
		if ( r < 0 || c < 0 || r >= rows || c >= cols)
			continue;
		
		char regionAtPos = area[r][c];
		
		if (regionAtPos == '|') // tree
		{
			noOfTrees++;
		}
		else if (regionAtPos == '#') // lumberyard
		{
			noOfLumberyards++;
		}
	}
	
	char currentRegion = area[i][j];
	// cout<<currentRegion<<" trees "<<noOfTrees<<", lumberyard "<<noOfLumberyards<<endl;
	
	switch (currentRegion)
	{
		case '.' : // Open Region
		{
			if (noOfTrees >= 3)
				return '|'; // tree
			break;
		}
		
		case '|' : // Tree Region
		{
			if (noOfLumberyards >= 3)
				return '#'; // lumberyard
			break;
		}
		
		case '#' : // lumberyard Region
		{
			if (noOfTrees == 0 || noOfLumberyards == 0)
				return '.'; // open
			break;
		}
	}
	
	return currentRegion;
}

int main()
{ 
	string line;
	string delimiters = " ,";
	ifstream myfile ("input.txt");
	
	vector<string> words;
	vector<vector<char>> area;
	
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
			vector<char> row;
			
			for (const char c : line)
			{
				row.emplace_back(c);
			}
			
			area.emplace_back(std::move(row));
		}
		myfile.close();
	}
	
	// print(area);
	
	const int rows = area.size();
	const int cols = area[0].size();
	
	vector<vector<vector<char>>> alreadySeen; // trees,lumber -> seen/notseen
	map<vector<vector<char>>, int> alreadySeenMap; // trees,lumber -> seen/notseen
	
	int collision = 0;
	int loopCount = 0;
	long i = 0;
	long target = 1000000000;
	bool foundLoop = false;
	while (i <= target + 1)
	{
		int noOfLumberyards = 0;
		int noOfTrees = 0;
		vector<vector<char>> temp;
		for (int i = 0; i < rows; i++)
		{
			vector<char> tempRow;
			for (int j = 0; j < cols; j++)
			{
				char newChar = getNewRegion(area, i, j, rows, cols);
				tempRow.emplace_back(newChar);
				
				if (newChar == '|')
					noOfTrees++;
				else if (newChar == '#')
					noOfLumberyards++;
			}
			temp.emplace_back(tempRow);
		}
		
		// auto it = find(alreadySeen.begin(), alreadySeen.end(), temp);
		
		if (!alreadySeenMap.count(temp) && !foundLoop)
		{
			alreadySeen.push_back(temp);
			alreadySeenMap[temp] = i;
			// i++;
		}
		else if (!foundLoop)
		{
			foundLoop = true;
			cout<<endl;
			cout<<"collision at iteration "<<i<<" for "<<noOfTrees<<", "<<noOfLumberyards<<endl;
			
			area = temp;
			
			// print(alreadySeen[make_pair(noOfTrees, noOfLumberyards)]);
			cout<<endl<<endl;
			collision = alreadySeenMap[temp];
			loopCount = i - alreadySeenMap[temp];
			cout<<"collision "<<collision<<" loop count "<<loopCount<<endl;

			cout<<((target - collision) / loopCount) * loopCount<<endl;
			i = ((target - collision) / loopCount) * loopCount;
			cout<<i + collision<<endl;
			i += collision;
			continue;
		}
		
		if (foundLoop)
		{
			cout<<"i "<<i<<", noOfTrees "<<noOfTrees<<", noOfLumberyards "<<noOfLumberyards<<" -> "<<noOfTrees*noOfLumberyards<<endl;
		}
		
		area = temp;
		i++;
		// cout<<endl;
		// print(area);
		
	}
	cout<<"i is "<<i<<endl;
	// find the correct map
	long offset = (1000000000  - collision) % loopCount;
	cout<<"Offset is "<<offset<<endl;
	cout<<"look for this number area "<<collision + offset<<endl;
	vector<vector<char>> res = alreadySeen[collision + offset];
	
	// calc res
	
	int noOfTrees = 0;
	int noOfLumberyards = 0;
	
	for (const vector<char>& row : area)
	{
		for (const char& c : row)
		{
			if (c == '|')
				noOfTrees++;
			else if (c == '#')
				noOfLumberyards++;
		}
	}
	
	cout<<endl;
	cout<<" noOfTrees: "<<noOfTrees<<", noOfLumberyards: "<<noOfLumberyards<<" -> "<<noOfTrees*noOfLumberyards<<endl;
	cout<<"Done"<<endl;

	return 0;
}
// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include <cmath>
#include <set>

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

int main()
{
	string line;
	string delimiters = ", ";
	ifstream myfile ("input.txt");
	
	vector<pair<int, int>> coordinates; // Col, Row
	

	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
            vector<string> coords = split(line, delimiters);
		    coordinates.emplace_back(make_pair(stoi(coords[0]), stoi(coords[1])));
		}
		myfile.close();
	}
	
	int maxRows = 500;
	int maxCols = 500;
	int path[maxRows][maxCols];
	vector<int> areaCount(coordinates.size(), 0);

	for (int i = 0; i < maxRows; i++)
	{
	    for (int j = 0; j < maxCols; j++)
	    {
	        int closestDistance = 1000;
	        int closestCollidingDistance  = 1000;
	        int closestPoint = 0;
	        
	        int currentCoord = 0;
	        for (const pair<int, int>& coordinate : coordinates)
	        {
	            int distance = abs(coordinate.second - i) + abs(coordinate.first - j);
	            if (distance < closestDistance)
	            {
	               // if (i == 3 && j == 5)
	               //     cout<<closestPoint<<" overtaken with "<<currentCoord<<" for length "<<closestDistance<<endl;
	                    
	               // areaCount[closestPoint]++;
	                closestDistance = distance;
	                closestPoint = currentCoord;
	                path[i][j] = currentCoord;
	               // areaCount[currentCoord]++;
	            }
	            else if (distance == closestDistance)
	            {
	                closestCollidingDistance = closestDistance;
	               // areaCount[closestPoint]--;
	               // if (i == 3 && j == 5)
	               //     cout<<closestPoint<<" collides with "<<currentCoord<<" for length "<<closestDistance<<endl;
	            }
	            currentCoord++;
	        }
	        if (closestCollidingDistance == closestDistance)
	        {
	            path[i][j] = -1;
                // areaCount[closestPoint]--;
	        }
	    }
	}
	
	set<int> infiniteNumbers;
	
	for (int i = 0; i < maxRows; i++)
	{
	    for (int j = 0; j < maxCols; j++)
	    {
	        int closestPoint = path[i][j];
	        if (i == 0 || i == maxRows-1 || j == 0 || j == maxCols-1)
	            infiniteNumbers.emplace(closestPoint);
	            
	        if (closestPoint != -1)
	            areaCount[closestPoint]++;
	    }
	   // cout<<endl;
	}
	
	int maxAreaDist = 0;
	int maxAreaPoint = 0;
	int currentAreaPoint = 0;
	for (int area: areaCount)
	{
	    if (area > maxAreaDist && infiniteNumbers.find(currentAreaPoint) == infiniteNumbers.end())
	    {
            maxAreaDist = area;
            maxAreaPoint = currentAreaPoint;
	    }
	    currentAreaPoint++;
	    cout<<area<<endl;
	}
	
    cout<<"size of coords "<<coordinates.size()<<endl;
    cout<<"maxAreaDist "<<maxAreaDist<<" for point "<<maxAreaPoint<<endl;
	cout<<"done"<<endl;

	return 0;
}
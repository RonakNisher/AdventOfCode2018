// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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

void print(vector<vector<int>>& sky)
{
    int colStart = 100;
    int colCutOff = 200;
    int noOfPoints = 0;
    for (const vector<int>& skyRow : sky)
    {
        if (find(skyRow.begin(), skyRow.end(), 1) != skyRow.end())
        {
            for (int j = colStart; j < colCutOff; j++)
            {
            	if (skyRow[j] == 1)
                	cout<<skyRow[j];
                else
                	cout<<" ";
                if (skyRow[j] == 1)
                    noOfPoints++;
            }
            cout<<endl;
            // cout<<"((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((("<<endl;
        }
    }
    cout<<"Total no of points "<<noOfPoints<<endl;
}

int main()
{ 
	string line;
	string delimiters = " ,=><";
	ifstream myfile ("input.txt");
	
	vector<pair<long, long>> positions;
	vector<pair<int, int>> velocities;
	
	vector<string> words;
	
	long minX = INT_MAX, minY = INT_MAX;
	long maxX = INT_MIN, maxY = INT_MIN;
	
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
            words = split(line, delimiters);
            
            int x = stoi(words[1]);
            int y = stoi(words[2]);
            
            // cout<<x<<", "<<y<<endl;
            
            if (x < minX)
                minX = x;
            else if (x > maxX)
                maxX = x;
                
            if (y < minY)
                minY = y;
            else if (y > maxY)
                maxY = y;
                
            positions.emplace_back(make_pair(x, y));
            velocities.emplace_back(make_pair(stoi(words[4]), stoi(words[5])));
		}
		myfile.close();
	}
	
	cout<<"bounds are "<<minX<<", "<<maxX<<" for Y "<<minY<<", "<<maxY<<endl;
	
	int boundSize = 450;
	const int rows = boundSize;
	const int cols = boundSize;
	
// 	std::vector<std::vector<int> > sky(
//     rows,
//     std::vector<int>(cols)); // Defaults to zero initial value
// 	for (int i = 0; i < rows; i++)
// 	{
// 	    cout<<i<<endl;
// 	    for (int j = 0; j < cols; j++)
// 	        sky[i][j] = 0;
// 	}
	
// 	std::vector<std::vector<long> > sky;
	
	std::vector<std::vector<int> > sky(
    rows,
    std::vector<int>(cols)); // Defaults to zero initial value
	
	cout<<"start "<<endl;
	for (int i = 0; i < 50000; i++)
	{
	    minX = INT_MAX, minY = INT_MAX;
	    maxX = INT_MIN, maxY = INT_MIN;
	
	   // cout<<"positions size "<<positions.size()<<endl;
	    for (int j = 0; j < positions.size(); j++)
	    {
	       // cout<<"pos "<<j<<endl;
	        long newX = int((positions[j].first + velocities[j].first));
	        long newY = int((positions[j].second + velocities[j].second));
	        pair<long, long> newPos = make_pair(newX, newY);
	        
	       // cout<<positions[j].first<<", "<<positions[j].second<<" -> "<<newX<<", "<<newY<<" with vel "<<velocities[j].first<<", "<<velocities[j].second<<endl;
	        positions[j] = newPos;
	       // sky[25 + newPos.first][25 + newPos.second] = 1;
	        
	        if (newX < minX)
                minX = newX;
            else if (newX > maxX)
                maxX = newX;
                
            if (newY < minY)
                minY = newY;
            else if (newY > maxY)
                maxY = newY;
                
	    }
	   // cout<<"bounds are "<<minX<<", "<<maxX<<" for Y "<<minY<<", "<<maxY<<endl;
	   // cout<<"size rough "<<maxX - minX<<", "<<maxY - minY<<endl;
	    
	    long xSize = (abs(minX) + abs(maxX) + 1);
	    long ySize = (abs(minY) + abs(maxY) + 1);
	    
	   // std::vector<std::vector<long> > sky;
	    
	    if (xSize < boundSize)
	    {
	        cout<<"found at iteration "<<i<<endl;
    	   // for (int i = 0; i <xSize; i++)
    	   // {
    	   //     for (int j = 0; j < ySize; j++)
    	   //         sky.emplace_back(0);
    	   // }
            
	        cout<<xSize<<", "<<ySize<<endl;
            cout<<"working..."<<endl;
            
            for (const pair<long, long>& p : positions)
            {
                int x = ((p.first+abs(minX)));
                int y = ((p.second+abs(minY)));
                // cout<<x<<", "<<y<<endl;
                // cout<<p.first<<", "<<p.second<<endl;
                // cout<<"pos is "<<p.first<<" "<<p.first + minX<<endl;
                // sky[p.first + abs(minX)][p.second + abs(minY)] = 1;
                sky[y][x] = 1;
                // sky.at(p.first + abs(minX));
                // .at(p.second + abs(minY)) = 1;
            }
            
        cout<<"Printing"<<endl;
	    print(sky);
            
	   break;
        cout<<"found stuff"<<endl;
	    }
        // sort(positions.begin(), positions.end());
        
        // for (const pair<long, long>& p : positions)
        // {
        //     int x = ((p.first+minX)/10) + minX;
        //     int y = ((p.second+minY)/10) + minY;
        //     cout<<x<<", "<<y<<endl;
        //     // cout<<p.first<<", "<<p.second<<endl;
        //     // cout<<"pos is "<<p.first<<" "<<p.first + minX<<endl;
        //     // sky[p.first + abs(minX)][p.second + abs(minY)] = 1;
        //     sky[y][x] = 1;
        //     // sky.at(p.first + abs(minX));
        //     // .at(p.second + abs(minY)) = 1;
        // }
	    
	   // cout<<"Printing"<<endl;
	   // print(sky);
	   // cout<<endl;
	   // cout<<endl;
	   // cout<<endl;
	   // for (vector<long> skyRow : sky)
	   // {
	   //     skyRow.clear();
	   // }
	    
	   // sky.clear();
	}
	
	cout<<"Done"<<endl;

	return 0;
}
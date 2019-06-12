// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
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

int calculateManhattanDistance(const tuple<int, int, int, int>& lhs, const tuple<int, int, int, int>& rhs)
{
	int lhs0 = get<0>(lhs);
	int lhs1 = get<1>(lhs);
	int lhs2 = get<2>(lhs);
	int lhs3 = get<3>(lhs);
	
	int rhs0 = get<0>(rhs);
	int rhs1 = get<1>(rhs);
	int rhs2 = get<2>(rhs);
	int rhs3 = get<3>(rhs);
	
	return abs(lhs0 - rhs0) + abs(lhs1 - rhs1)+ abs(lhs2 - rhs2) + abs(lhs3 - rhs3);
}

int main()
{ 
	string line;
	string delimiters = " ,";
	ifstream myfile ("input.txt");
	
	vector<string> words;
	
	vector<tuple<int, int, int, int>> points;
	
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
			words = split(line, delimiters);
			
			points.emplace_back(stoi(words[0]), stoi(words[1]), stoi(words[2]), stoi(words[3]));
		}
		myfile.close();
	}
	
	// sort(points.begin(), points.end());
	
	// for (const tuple<int, int, int, int>& point : points)
	// {
	// 	cout<<get<0>(point)<<", "<<get<1>(point)<<", "<<get<2>(point)<<", "<<get<3>(point)<<endl;
	// }
	
	vector<vector<int>> clusters;
	
	int noOfConstellations = 0;
	int pointsAccountedFor = 0;
	for (int i = 0; i < points.size(); i++)
	{
		// cout<<i<<endl;
		vector<int> matchingClusters;
		bool found = false;
		
		for (int j = 0; j < clusters.size(); j++)
		{
			for (int n : clusters[j])
			{
				int manhattanDist = calculateManhattanDistance(points[n], points[i]);
				// cout<<" with "<<j<<" dist is "<<manhattanDist<<endl;
				if (manhattanDist <= 3)
				{
					matchingClusters.push_back(j);
					// found = true;
					break;
				}
			}
		}
		
		int matchingClustersSize = matchingClusters.size();
		// cout<<"matchingClusters size "<<matchingClustersSize<<endl;
		
		if (matchingClustersSize == 0)
		{
			vector<int> c = { i };
			clusters.emplace_back(c);
		}
		else if (matchingClustersSize == 1)
		{
			clusters[matchingClusters[0]].push_back(i);
		}
		else
		{
			// cout<<"Found a bridge"<<endl;
			int survivingCluster = matchingClusters[0];
			for (int i = 1; i < matchingClusters.size(); i++)
			{
				// vector<vector<int>>::iterator it = find(clusters.begin(), clusters.end(), matchingClusters[i]);
				vector<int> elementsToTransfer = clusters[matchingClusters[i]];
				for (const int n : elementsToTransfer)
					clusters[survivingCluster].push_back(n);
				
				// cout<<matchingClusters[i]<<" matchingClusters[i] "<<endl;
			}
			clusters[survivingCluster].push_back(i);
			
			// delete the other transferred vectors
			for (int i = 1; i < matchingClusters.size(); i++)
			{
				clusters.erase(clusters.begin() + matchingClusters[i]);
			}
			
		}
		
		// if (!found)
		// 	noOfConstellations++;
		// pointsAccountedFor++;
		
		// cout<<i<<", noOfConstellations "<<noOfConstellations<<endl;
	}
	
	cout<<"noOfConstellations: "<<clusters.size()<<endl;
	// cout<<"noOfConstellations: "<<noOfConstellations<<endl;
	
	// sort(points.begin(), points.end(), [](const tuple<int, int, int, int>& lhs, const tuple<int, int, int, int>& rhs)
	// {
	// 	int lhs0 = get<0>(lhs);
	// 	int rhs0 = get<0>(rhs);
		
	// 	if (lhs0 != rhs0)
	// 		return lhs0 < rhs0;
			
	// 	int lhs1 = get<1>(lhs);
	// 	int rhs1 = get<1>(rhs);
		
	// 	if (lhs1 != rhs1)
	// 		return lhs1 < rhs1;
			
	// 	int lhs2 = get<2>(lhs);
	// 	int rhs2 = get<2>(rhs);
		
	// 	if (lhs2 != rhs2)
	// 		return lhs2 < rhs2;
			
	// 	int lhs3 = get<3>(lhs);
	// 	int rhs3 = get<3>(rhs);
		
	// 	if (lhs3 != rhs3)
	// 		return lhs3 < rhs3;
	// });
	
	cout<<"Done"<<endl;

	return 0;
}
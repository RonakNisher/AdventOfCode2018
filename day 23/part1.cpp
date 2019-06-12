// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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

int main()
{ 
	string line;
	string delimiters = " ,=><posr";
	ifstream myfile ("input.txt");
	
	vector<string> words;
	
	vector<tuple<long, long, long, long>> nanobots;
	
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			words = split(line, delimiters);
			
			nanobots.emplace_back(stoi(words[0]), stoi(words[1]), stoi(words[2]), stoi(words[3]));
		}
		myfile.close();
	}
	
	long maxRadius = 0;
	tuple<long, long, long, long> nanobotStrongest;
	for (const tuple<long, long, long, long>& nanobot : nanobots)
	{
		// cout<<"Position "<<get<0>(nanobot)<<", "<<get<1>(nanobot)<<", "<<get<2>(nanobot)<<" r = "<<get<3>(nanobot)<<endl;
		
		if (get<3>(nanobot) > maxRadius)
		{
			maxRadius = get<3>(nanobot);
			nanobotStrongest = nanobot;
		}
	}
	
	cout<<"Stringest nanobot "<<get<0>(nanobotStrongest)<<", "<<get<1>(nanobotStrongest)<<", "<<get<2>(nanobotStrongest)<<" r = "<<get<3>(nanobotStrongest)<<endl;
	
	long maxNodes = 0;
	// for (long i = 0; i < nanobots.size(); i++)
	{
		// const auto& nanobot = nanobots[i];
		long radius = get<3>(nanobotStrongest);
		long x = get<0>(nanobotStrongest);
		long y = get<1>(nanobotStrongest);
		long z = get<2>(nanobotStrongest);
		long numNodes = 0;
		
		if (radius > maxRadius)
			maxRadius = radius;
			
		for (long j = 0; j < nanobots.size(); j++)
		{
			const auto& other = nanobots[j];
			
			long dist = abs(get<0>(other) - x) + abs(get<1>(other) - y) + abs(get<2>(other) - z);
			if (radius >= dist)
				numNodes++;
				
			// if (i == 545)
			// {
			// 	cout<<"Position "<<get<0>(other)<<", "<<get<1>(other)<<", "<<get<2>(other)<<endl;
			// 	cout<<j<<" : d "<<dist<<", r "<<radius<<", numNodes "<<numNodes<<endl;
			// }
		}
		
		if (numNodes > maxNodes)
			maxNodes = numNodes;
	}
	
	cout<<"Max Nodes is "<<maxNodes<<endl;
	cout<<"Max radius is "<<maxRadius<<endl;
	cout<<"Done"<<endl;

	return 0;
}
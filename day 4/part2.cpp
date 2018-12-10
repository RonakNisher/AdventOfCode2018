// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

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
	
	ifstream myfile ("input.txt");
	
	vector<string> schedules;
	vector<vector<string>> splitSchedules;

	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			schedules.emplace_back(line);
		}
		myfile.close();
	}
	
	sort(schedules.begin(), schedules.end());
	
	string delimiters = "[]: #";
	int sleepStartTime = 0;
	int sleepStopTime = 0;
	string currentGuardId;
	int currentSleepTime = 0;
	int maxSleepTime = 0;
	string maxSleepGuardId;
	map<string, int> guardSleepTimes;
	map<string, map<int, int>> guardCommonSleepTimeMap;
	
	for (string& schedule : schedules)
	{
		vector<string> splitSchedule = split(schedule, delimiters);
		
		string key = splitSchedule[3];
		if (key == "Guard")
		{
			currentGuardId = splitSchedule[4];
			currentSleepTime = 0;
			sleepStartTime = 0;
			sleepStopTime = 0;
		}
		else if (key == "falls")
		{
			sleepStartTime = stoi(splitSchedule[2]);
		}
		else if(key == "wakes")
		{
			sleepStopTime = stoi(splitSchedule[2]);
			currentSleepTime = (sleepStopTime - sleepStartTime) + guardSleepTimes[currentGuardId];
			guardSleepTimes[currentGuardId] = currentSleepTime;
			
			map<int, int>& guardEgeTimesAndCommonTimePair = guardCommonSleepTimeMap[currentGuardId];
			
			for (int i = sleepStartTime; i < sleepStopTime; i++)
			{
			    guardEgeTimesAndCommonTimePair[i] = guardEgeTimesAndCommonTimePair[i] + 1;
			    
			}
// 			guardEgeTimesAndCommonTimePair[sleepStopTime - 1] = guardEgeTimesAndCommonTimePair[sleepStopTime - 1] + 1;
			
			if (currentSleepTime > maxSleepTime)
			{
				maxSleepTime = currentSleepTime;
				maxSleepGuardId = currentGuardId;
			}
			
		}
	   // cout<<schedule<<endl;
	}
	cout<<endl;
	cout<<"maxSleepGuardId:"<<maxSleepGuardId<<" - maxSleepTime "<<maxSleepTime<<" "<<guardSleepTimes[maxSleepGuardId]<<endl;
	
	
	int maxCount = 0;
	int maxCountTime = 0;
	string maxCountId;
	
	for (auto guard = guardCommonSleepTimeMap.begin(); guard != guardCommonSleepTimeMap.end(); guard++)
	{
	    map<int, int>& guardEgeTimesAndCommonTimePair = guard->second;
	   // cout<<"guard is "<<guard->first<<endl;
    	for (auto it = guardEgeTimesAndCommonTimePair.begin(); it != guardEgeTimesAndCommonTimePair.end(); it++)
    	{
    	    if (it->second > 4)
    	        cout<<guard->first<<" id "<<it->first<<" for "<<it->second<<endl;
    		if (it->second > maxCount)
    		{
    		    
    		  //  cout<<guard->first<<" id "<<it->first<<" for "<<it->second<<endl;
    			maxCountTime = it->first;
    			maxCount = it->second;
    			maxCountId = guard->first;
    		}
    	}
	}
	
	cout<<maxCountTime<<" is the most common time"<<endl;
	cout<<maxCountId<<" is the most common id"<<endl;
	cout<<"final answer is "<<maxCountTime*stoi(maxCountId)<<endl;
	cout<<"done"<<endl;

	return 0;
}
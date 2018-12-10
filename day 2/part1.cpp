// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
	string line;
	
	int TwoCount = 0;
	int ThreeCount = 0;
	ifstream myfile ("input.txt");
	
	unordered_map<char, int> letterCountMap;
	
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			for (const char& letter : line) 
			{
				const auto& ret = letterCountMap.emplace(letter, 1);
				
				const auto& iter = ret.first;
				
				if (!ret.second)
				{
					// int currentVal = letterCountMap[ret.first];
					// letterCountMap[ret.first] = currentVal++;
					
					int currentVal = iter->second;
					iter->second = ++currentVal;
				}
			}
			
			bool TwoFound = false;
			bool ThreeFound = false;
			
			for ( auto it = letterCountMap.cbegin(); it != letterCountMap.cend(); ++it )
			{
				if (it->second == 2)
					TwoFound = true;
					
				if (it->second == 3)
					ThreeFound = true;
			}
			
			if (TwoFound)
				TwoCount++;
			if (ThreeFound)
				ThreeCount++;
				
			letterCountMap.clear();
		}
		myfile.close();
	}
	
	int r = TwoCount*ThreeCount;
	cout<<"done "<<TwoCount<<", "<<ThreeCount<<" -> "<<r<<endl;

	return 0;
}
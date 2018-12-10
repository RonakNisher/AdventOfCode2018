// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

vector<string> split(string input)
{
	vector<string> res;
	
	string val = "";
	for (auto i : input) {
		if(!isspace(i))
		{
			val.push_back(i);
		}
		else
		{
			res.push_back(val);
			val = "";
		}
	}
	
	if(val != "")
		res.push_back(val);
	return res;
}

int main()
{
	string line;
	set<int> resultSet;
	int result = 0;
	int final = 0;
	std::vector<string> words;
	
	ifstream myfile ("input.txt");
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			words.emplace_back(line);
			
		}
		myfile.close();
	}
	
	cout<<words.size()<<endl;
	
	
	int multiplier = 1;
	
	while (final == 0)
	{
		for (auto word : words) 
		{
			cout<<word<<endl;
			if (word[0] == '+')
				multiplier = 1;
			else
				multiplier = -1;
				
			result += multiplier * stoi(word.substr(1));
			// cout<<result<<endl;
			if (!resultSet.insert(result).second)
			{
				final = result;
				break;
			}
		}
		// cout<<final<<endl;
	}
			
	cout<<"done "<<final<<endl;

	return 0;
}
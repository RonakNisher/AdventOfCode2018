// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

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
	int validPhrases = 0;
	string line;
	int result = 0;
	ifstream myfile ("input.txt");
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			std::vector<string> words = split(line);

			// set<string> passPhraseWords;
			// bool isValid = true;
			int multiplier = 1;
			
			for (auto word : words) 
			{
				if (word[0] == '+')
					multiplier = 1;
				else
					multiplier = -1;
					
				result += multiplier * stoi(word.substr(1));
			}
		}
		myfile.close();
	}
	cout<<"done "<<result<<endl;

	return 0;
}
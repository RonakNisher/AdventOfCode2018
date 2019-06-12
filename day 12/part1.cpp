// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include <memory>
#include <set>
#include <map>

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
	string delimiters = " =>";
	ifstream myfile ("input.txt");
	
	string initialState;
	map<string, string> rules;
	
	if (myfile.is_open())
	{
	    getline(myfile, initialState);
	    cout<<"init stat "<<initialState<<endl;
		while ( getline(myfile,line) )
		{
            vector<string> words = split(line, delimiters);
            rules[words[0]] = words[1];
		}
		myfile.close();
	}
	
	for (auto rule : rules)
	{
	    cout<<rule.first<<"->"<<rule.second<<endl;
	}
	
	int initialPotNumber = 0;

	cout<<"Done"<<endl;
	
	string generation;
	long p2 = 50000000000;
	
	for (long i = 0; i < 100; i++)
	{
	   int firstPlant = initialState.find('#');
	   //int start = firstPlant >= 3 ? firstPlant - 3 : 0;
	   int start = 0;
	   
	   //string  generation(0, '.');
	    
	    if (i % 100000 == 0)
	        cout<<"start "<<start<<endl;
	        
	    // n-1
	    string potn1 = "..." + initialState.substr(start, 2);
    	string newCharn1 = rules.find(potn1) != rules.end() ? rules[potn1] : ".";
    	
    	// n-2
	    string potn2 = "...." + initialState.substr(start, 1);
    	string newCharn2 = rules.find(potn2) != rules.end() ? rules[potn2] : ".";
    	
    	
    	if (newCharn2 == "#")
	    {
	       // cout<<"pot1"<<pot1<<endl;
    	    initialPotNumber-= 2;
    	    generation.append(newCharn2).append(newCharn1);
    	    cout<<"generation "<<i+1<<" initialPotNumber "<<initialPotNumber<<endl;
	    }
	    else if(newCharn1 == "#")
	    {
	        initialPotNumber-= 1;
    	    generation.append(newCharn1);
    	    cout<<"generation "<<i+1<<" initialPotNumber "<<initialPotNumber<<endl;
	    }
    	

    	string pot1 = ".." + initialState.substr(start, 3);
    	string newChar = rules.find(pot1) != rules.end() ? rules[pot1] : ".";
    	generation.append(newChar);
	    
	    
	    string pot2 =  "." + initialState.substr(start, 4);
	    string newChar2 = rules.find(pot2) != rules.end() ? rules[pot2] : ".";
	    generation.append(newChar2);
	    
	    for (long j = start + 2; j<initialState.size() - 2; j++)
	    {
	        string pot = initialState.substr(j-2,5);
	        string charToAppend = rules.find(pot) != rules.end() ? rules[pot] : ".";
	        generation.append(charToAppend);
	    }
	    
	    string potLast = initialState.substr(initialState.size() - 1 - 2, string::npos).append("..");
	    string potSecondToLast = initialState.substr(initialState.size() - 2 - 2, string::npos).append(".");
	    
	   // cout<<"potSecondToLast "<<potSecondToLast<<endl;
	   // cout<<"potLast "<<potLast<<endl;
	    
    	string newCharLast = rules.find(potLast) != rules.end() ? rules[potLast] : ".";
    	string newCharSecondToLast = rules.find(potSecondToLast) != rules.end() ? rules[potSecondToLast] : ".";
    	
    	generation.append(newCharSecondToLast).append(newCharLast);
    	
    	// n+1
	    string potnp1 = initialState.substr(initialState.size() - 2, string::npos) + "...";
    	string newCharnp1 = rules.find(potnp1) != rules.end() ? rules[potnp1] : ".";
    	
    	// n+2
	    string potnp2 = initialState.substr(initialState.size() - 1, string::npos) + "....";
    	string newCharnp2 = rules.find(potnp2) != rules.end() ? rules[potnp2] : ".";
    	
    	if (newCharnp2 == "#")
	    {
    	    generation.append(newCharnp1).append(newCharnp2);
	    }
	    else if(newCharnp1 == "#")
	    {
    	    generation.append(newCharnp1);
	    }
    	
    	
    // 	if (newCharLast == "#")
    // 	{
    // 	    generation.append(newCharSecondToLast).append(newCharLast);
    // 	}
    // 	else if (newCharSecondToLast == "#")
    // 	{
    // 	    generation.append(newCharSecondToLast);
    // 	}
    	
    // 	if (i % 10000 == 0)
    // 	    cout<<i+1<<endl;
    
    	cout<<i+1<<" : "<<generation<<endl;
    
    	initialState = "";
    	initialState = generation;
    	generation = "";
	}
	
	cout<<"initialPotNumber "<<initialPotNumber<<endl;
	
	long currentPos = initialPotNumber;
	long score = 0;
	for (char c : initialState)
	{
	    if (c == '#')
	    {
	        score+= currentPos;
	    }
	    currentPos++;
	}
	
	cout<<"score is "<<score<<endl;
	return 0;
}
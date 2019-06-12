// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
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

int findNumberOfMatches(const vector<int>& before,const vector<int>& after,vector<int>& instruction,const vector<string>& operations)
{
	int count = 0;
	
	for (const string& operation : operations)
	{
		vector<int> temp = before;
		if (operation == "addr")
		{
			// regC = regA + regB
			temp[instruction[3]] = temp[instruction[1]] + temp[instruction[2]];
		}
		else if (operation == "addi")
		{
			// regC = regA + B
			temp[instruction[3]] = temp[instruction[1]] + instruction[2];
		}
		else if (operation == "mulr")
		{
			// regC = regA * regB
			temp[instruction[3]] = temp[instruction[1]] * temp[instruction[2]];
		}
		else if (operation == "muli")
		{
			// regC = regA * B
			temp[instruction[3]] = temp[instruction[1]] * instruction[2];
		}
		else if (operation == "banr")
		{
			// regC = regA & regB
			temp[instruction[3]] = temp[instruction[1]] & temp[instruction[2]];
		}
		else if (operation == "bani")
		{
			// regC = regA & B
			temp[instruction[3]] = temp[instruction[1]] & instruction[2];
		}
		else if (operation == "borr")
		{
			// regC = regA | regB
			temp[instruction[3]] = temp[instruction[1]] | temp[instruction[2]];
		}
		else if (operation == "bori")
		{
			// regC = regA | B
			temp[instruction[3]] = temp[instruction[1]] | instruction[2];
		}
		else if (operation == "setr")
		{
			// regC = regA
			temp[instruction[3]] = temp[instruction[1]];
		}
		else if (operation == "seti")
		{
			// regC = A
			temp[instruction[3]] = instruction[1];
		}
		else if (operation == "gtir")
		{
			// regC = (A > regB) ? 1 : 0
			temp[instruction[3]] = (instruction[1] > temp[instruction[2]]) ? 1 : 0;
		}
		else if (operation == "gtri")
		{
			// regC = (regA > B) ? 1 : 0
			temp[instruction[3]] = (temp[instruction[1]] > instruction[2]) ? 1 : 0;
		}
		else if (operation == "gtrr")
		{
			// regC = (regA > regB) ? 1 : 0
			temp[instruction[3]] = (temp[instruction[1]] > temp[instruction[2]]) ? 1 : 0;
		}
		else if (operation == "eqir")
		{
			// regC = (A == regB) ? 1 : 0
			temp[instruction[3]] = (instruction[1] == temp[instruction[2]]) ? 1 : 0;
		}
		else if (operation == "eqri")
		{
			// regC = (regA == B) ? 1 : 0
			temp[instruction[3]] = (temp[instruction[1]] == instruction[2]) ? 1 : 0;
		}
		else if (operation == "eqrr")
		{
			// regC = (regA == regB) ? 1 : 0
			temp[instruction[3]] = (temp[instruction[1]] == temp[instruction[2]]) ? 1 : 0;
		}
		
		if (temp == after)
			count++;
	}
	
	return count;
}


int main()
{ 
	string line;
	string delimiters = " ,:[]";
	ifstream myfile ("input.txt");
	
	const vector<string> operations = {"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori",
									"setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr" };

	int finalRes = 0;
	
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
			// line = before
			vector<string> beforeLine = split(line, delimiters);
			if (beforeLine.size() == 0)
			{
				cout<<"------------------Part 2-------------------"<<endl;
				break;
			}
			
			cout<<"Processing "<<line<<endl;
				
			const vector<int> before = {stoi(beforeLine[1]), stoi(beforeLine[2]), stoi(beforeLine[3]), stoi(beforeLine[4])};
			
			// Registers
			string registerValues;
			getline(myfile,registerValues);
			
			vector<string> registersLine = split(registerValues, delimiters);
			vector<int> instruction;
			for (const string& s : registersLine)
			{
				instruction.emplace_back(stoi(s));
			}
			
			// After
			string afterString;
			getline(myfile,afterString);
			
			vector<string> afterLine = split(afterString, delimiters);
			const vector<int> after = {stoi(afterLine[1]), stoi(afterLine[2]), stoi(afterLine[3]), stoi(afterLine[4])};
			
			
			// Eat up the blank line
			getline(myfile,line);
			
			// Find out the number of possible matches
			int count = findNumberOfMatches(before, after, instruction, operations);
			
			if (count >= 3)
				finalRes++;
		}
		
		myfile.close();
	}

	cout<<"ops with 3 or more matches "<<finalRes<<endl;
	cout<<"Done"<<endl;

	return 0;
}
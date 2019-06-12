// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <set>
#include <map>
#include <climits>
#include <utility>
#include <algorithm>    // std::find, std::intersection

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

void print(set<string>& values)
{
	for (const string& val : values)
	{
		cout<<val<<" ";
	}
	cout<<endl;
}

void performOperation(const string& operation, const vector<int>& instruction, vector<int>& registers)
{
	if (operation == "addr")
	{
		// regC = regA + regB
		registers[instruction[3]] = registers[instruction[1]] + registers[instruction[2]];
	}
	else if (operation == "addi")
	{
		// regC = regA + B
		registers[instruction[3]] = registers[instruction[1]] + instruction[2];
	}
	else if (operation == "mulr")
	{
		// regC = regA * regB
		registers[instruction[3]] = registers[instruction[1]] * registers[instruction[2]];
	}
	else if (operation == "muli")
	{
		// regC = regA * B
		registers[instruction[3]] = registers[instruction[1]] * instruction[2];
	}
	else if (operation == "banr")
	{
		// regC = regA & regB
		registers[instruction[3]] = registers[instruction[1]] & registers[instruction[2]];
	}
	else if (operation == "bani")
	{
		// regC = regA & B
		registers[instruction[3]] = registers[instruction[1]] & instruction[2];
	}
	else if (operation == "borr")
	{
		// regC = regA | regB
		registers[instruction[3]] = registers[instruction[1]] | registers[instruction[2]];
	}
	else if (operation == "bori")
	{
		// regC = regA | B
		registers[instruction[3]] = registers[instruction[1]] | instruction[2];
	}
	else if (operation == "setr")
	{
		// regC = regA
		registers[instruction[3]] = registers[instruction[1]];
	}
	else if (operation == "seti")
	{
		// regC = A
		registers[instruction[3]] = instruction[1];
	}
	else if (operation == "gtir")
	{
		// regC = (A > regB) ? 1 : 0
		registers[instruction[3]] = (instruction[1] > registers[instruction[2]]) ? 1 : 0;
	}
	else if (operation == "gtri")
	{
		// regC = (regA > B) ? 1 : 0
		registers[instruction[3]] = (registers[instruction[1]] > instruction[2]) ? 1 : 0;
	}
	else if (operation == "gtrr")
	{
		// regC = (regA > regB) ? 1 : 0
		registers[instruction[3]] = (registers[instruction[1]] > registers[instruction[2]]) ? 1 : 0;
	}
	else if (operation == "eqir")
	{
		// regC = (A == regB) ? 1 : 0
		registers[instruction[3]] = (instruction[1] == registers[instruction[2]]) ? 1 : 0;
	}
	else if (operation == "eqri")
	{
		// regC = (regA == B) ? 1 : 0
		registers[instruction[3]] = (registers[instruction[1]] == instruction[2]) ? 1 : 0;
	}
	else if (operation == "eqrr")
	{
		// regC = (regA == regB) ? 1 : 0
		registers[instruction[3]] = (registers[instruction[1]] == registers[instruction[2]]) ? 1 : 0;
	}
	// cout<<"Perform "<<operation<<": "<<instruction[1]<<", "<<instruction[2]<<", "<<instruction[3]<<endl;
	// cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<endl;
}

int findNumberOfMatches(const vector<int>& before,const vector<int>& after,vector<int>& instruction,const vector<string>& operations
						, map<int, set<string>>& opcodes)
{
	int count = 0;
	
	set<string> possibleValues;
	int opCode = instruction[0];
	
	for (const string& operation : operations)
	{
		vector<int> temp = before;
		
		performOperation(operation, instruction, temp);
		
		if (temp == after)
		{
			count++;
			possibleValues.insert(operation);
		}
	}
	
	map<int, set<string>>::iterator it = opcodes.find(opCode);
	
	if (it != opcodes.end())
	{
		set<string>& existingVal = it->second;
		set<string> intersectionRes;
		
		for(const string& val : possibleValues)
		{
			auto res = existingVal.find(val);
			if (res != existingVal.end())
			{
				intersectionRes.insert(val);
			}
		}
		
		it->second = intersectionRes;
	}
	else
	{
		// cout<<"new entry for "<<opCode<<" count "<<possibleValues.size()<<endl;
		opcodes[opCode] = possibleValues;
	}
	
	return count;
}


int main()
{ 
	string line;
	string delimiters = " ,:[]";
	ifstream myfile ("input.txt");
	
	vector<string> part2InputLines;
	
	const vector<string> operations = {"addr", "addi", "mulr", "muli", "banr", "bani", "borr", "bori",
									"setr", "seti", "gtir", "gtri", "gtrr", "eqir", "eqri", "eqrr" };
									
	map<int,set<string>> opcodes;

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
				while (getline(myfile,line))
				{
					if (line != "")
						part2InputLines.push_back(line);
				}
				break;
			}
			
// 			cout<<"Processing "<<line<<endl;
				
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
			int count = findNumberOfMatches(before, after, instruction, operations, opcodes);
				
			if (count >= 3)
				finalRes++;
		}
		
		myfile.close();
	}
	
	// figure out the opcodes by 
	map<int, string> finalOpcodeMap;
	
	while (!opcodes.empty())
	{
		int minCount = 20;
		int minCountOpcode = -1;
		int maxCount = 0;
		
		for (auto it = opcodes.begin(); it != opcodes.end(); ++it)
		{
			int size = it->second.size();
			
			if (size < minCount)
			{
				minCount = size;
				minCountOpcode = it->first;
			}
			
			if (size > maxCount)
				maxCount = size;
		}
		
		// cout<<"minCount "<<minCount<<" minCountOpcode "<<minCountOpcode<<endl;
		string code = *opcodes[minCountOpcode].begin();
		// cout<<code<<" size "<<opcodes[minCountOpcode].size()<<endl;
		
		finalOpcodeMap[minCountOpcode] = code;
		opcodes.erase(minCountOpcode);
		
		for (auto it = opcodes.begin(); it != opcodes.end(); ++it)
		{
			it->second.erase(code);
		}
	}
	
	for (auto it = finalOpcodeMap.begin(); it != finalOpcodeMap.end(); ++it)
	{
		cout<<it->first<<" -> "<<it->second<<endl;
	}
	
	vector<int> registers(4, 0);
	cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<endl;
	
	for (const string& line : part2InputLines)
	{
		vector<string> registersLine = split(line, delimiters);
		vector<int> instruction;
		for (const string& s : registersLine)
		{
			instruction.emplace_back(stoi(s));
		}
		
		// if (finalOpcodeMap[instruction[0]] == "")
			// cout<<instruction[0]<<finalOpcodeMap[instruction[0]]<<endl;
		performOperation(finalOpcodeMap[instruction[0]], instruction, registers);
	}
	cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<endl;
	cout<<"Done"<<endl;

	return 0;
}
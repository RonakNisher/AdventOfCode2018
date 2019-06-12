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

void print(vector<int>& values)
{
	for (const int val : values)
	{
		cout<<val<<" ";
	}
	cout<<endl;
}

void performOperation(const string& operation, const vector<int>& instruction, vector<int>& registers)
{
	int A = instruction[0];
	int B = instruction[1];
	int C = instruction[2];
	
	if (operation == "addr")
	{
		// regC = regA + regB
		registers[C] = registers[A] + registers[B];
	}
	else if (operation == "addi")
	{
		// regC = regA + B
		registers[C] = registers[A] + B;
	}
	else if (operation == "mulr")
	{
		// regC = regA * regB
		registers[C] = registers[A] * registers[B];
	}
	else if (operation == "muli")
	{
		// regC = regA * B
		registers[C] = registers[A] * B;
	}
	else if (operation == "banr")
	{
		// regC = regA & regB
		registers[C] = registers[A] & registers[B];
	}
	else if (operation == "bani")
	{
		// regC = regA & B
		registers[C] = registers[A] & B;
	}
	else if (operation == "borr")
	{
		// regC = regA | regB
		registers[C] = registers[A] | registers[B];
	}
	else if (operation == "bori")
	{
		// regC = regA | B
		registers[C] = registers[A] | B;
	}
	else if (operation == "setr")
	{
		// regC = regA
		registers[C] = registers[A];
	}
	else if (operation == "seti")
	{
		// regC = A
		registers[C] = A;
	}
	else if (operation == "gtir")
	{
		// regC = (A > regB) ? 1 : 0
		registers[C] = (A > registers[B]) ? 1 : 0;
	}
	else if (operation == "gtri")
	{
		// regC = (regA > B) ? 1 : 0
		registers[C] = (registers[A] > B) ? 1 : 0;
	}
	else if (operation == "gtrr")
	{
		// regC = (regA > regB) ? 1 : 0
		registers[C] = (registers[A] > registers[B]) ? 1 : 0;
	}
	else if (operation == "eqir")
	{
		// regC = (A == regB) ? 1 : 0
		registers[C] = (A == registers[B]) ? 1 : 0;
	}
	else if (operation == "eqri")
	{
		// regC = (regA == B) ? 1 : 0
		registers[C] = (registers[A] == B) ? 1 : 0;
	}
	else if (operation == "eqrr")
	{
		// regC = (regA == regB) ? 1 : 0
		registers[C] = (registers[A] == registers[B]) ? 1 : 0;
	}
	// cout<<"Perform "<<operation<<": "<<A<<", "<<B<<", "<<C<<endl;
	// cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<endl;
}

void copyRegisterValues(const vector<int>& fromRegister, vector<int>& toRegister)
{
	for (int i = 0; i < fromRegister.size(); i++)
	{
		toRegister[i] = fromRegister[i];
	}
}


int main()
{ 
	string line;
	string delimiters = " ,:[]";
	ifstream myfile ("input.txt");
	
	vector<string> inputLines;
	vector<string> operations;
	vector<vector<int>> instructions;
									
	int ipRegister = 0;
	int ip = 0;
	
	if (myfile.is_open())
	{
		string ipLine;
		getline(myfile,ipLine);
		
		vector<string> ipVec = split(ipLine, delimiters);
		ipRegister = stoi(ipVec[1]);
		cout<<"ip Register is "<<ipRegister<<endl;
		
		while (getline(myfile,line))
		{
			vector<string> input = split(line, delimiters);
			vector<int> instruction;
			for (int i = 1; i < input.size(); i++)
			{
				instruction.emplace_back(stoi(input[i]));
			}
			
			instructions.push_back(instruction);
			operations.emplace_back(input[0]);
		}
		
		myfile.close();
	}
	
	int programSize = operations.size();
	cout<<"input size "<<operations.size()<<endl;
	int regisStartValue = 0;
	// int regisStartValue = 30842;
	int maxValue = 0;
	int maxIns = 0;
	
	// cout<<"Register Start Value "<<regisStartValue<<endl;
	vector<int> registers(6, 0);
	vector<int> prevRegisters(6, 0);
	// cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<", "<<registers[4]<<", "<<registers[5]<<endl;
	
	registers[0] = regisStartValue;
	
	set<int> seenValues;
	vector<int> cycleValues;
	bool collisionFound = false;
	int collisionIp = 0;
	bool cycleFound = false;
	
	// int i = 0;
	while (ip < programSize)
	{
		registers[ipRegister] = ip;
		performOperation(operations[ip], instructions[ip], registers);
		
		ip = registers[ipRegister] + 1;
		
		if (ip == 28)
		{
			auto it = seenValues.find(registers[2]);
			if (it != seenValues.end())
			{
				cout<<"duplicate "<<registers[2]<<endl;
				break;
			}
			else
			{
				if (seenValues.empty())
				{
					cout<<registers[2]<<endl;
					// break;
				}
				seenValues.insert(registers[2]);
				// cout<<"insert "<<registers[2]<<endl;
			}
		}
		// i++;
	}
	
	// cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<", "<<registers[4]<<", "<<registers[5]<<endl;
	cout<<"Done"<<endl;

	return 0;
}
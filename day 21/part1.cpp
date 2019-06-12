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
	
	while (true)
	{
		cout<<"Register Start Value "<<regisStartValue<<endl;
		vector<int> registers(6, 0);
		vector<int> prevRegisters(6, 0);
		// cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<", "<<registers[4]<<", "<<registers[5]<<endl;
		
		registers[0] = regisStartValue;
		
		vector<int> seenValues;
		vector<int> cycleValues;
		bool collisionFound = false;
		int collisionIp = 0;
		bool cycleFound = false;
		
		int i = 0;
		while (ip < programSize)
		{
			// cout<<"ip "<<ip<<" iter "<<i<<endl;
			/*if (!collisionFound)
			{
				auto it = find(seenValues.begin(), seenValues.end(), ip);
				if (it != seenValues.end())
				{
					seenValues.push_back(ip);
					cout<<"collisionFound "<<ip<<endl;
					collisionFound = true;
					collisionIp = ip;
				}
				else
				{
					seenValues.push_back(ip);
				}
			}
			else if (ip != collisionIp)
			{
				cycleValues.push_back(ip);
			}
			else
			{
				cycleValues.push_back(ip);
				break;
			}*/
			
			// copyRegisterValues(registers /*from*/, prevRegisters /*to*/);
			
			// cout<<operations[ip]<<" "<<instructions[ip][0]<<" "<<instructions[ip][1]<<" "<<instructions[ip][2]<<endl;
			registers[ipRegister] = ip;
			performOperation(operations[ip], instructions[ip], registers);
			
	/*		cout<<areRegisterValuesRepeated<<endl;
			if (areRegisterValuesRepeated)
			{
				cout<<"Matching values found at it "<<i<<endl;
				cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<", "<<registers[4]<<", "<<registers[5]<<endl;
			}*/
			
			ip = registers[ipRegister] + 1;
			// cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<", "<<registers[4]<<", "<<registers[5]<<endl;
			
			if (ip == 28)
				cout<<"r2 "<<registers[2]<<endl;
			i++;
			
			// if (ip == 31)
			// 	break;
			
	/*		if (i == 37)
				break;*/
	
		}
		
		if (collisionFound)
		{
			// cout<<"cycleValues "<<endl;
			// print(cycleValues);
			// cout<<"seen values"<<endl;
			// print(seenValues);
			
			cout<<"cycle size "<<cycleValues.size()<<endl;
			
/*			if (regisStartValue == 0)
				regisStartValue++;
			else
				regisStartValue *= 2;*/
				
			regisStartValue++;
			break;
		}
		else
		{
			cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<", "<<registers[4]<<", "<<registers[5]<<endl;
			cout<<"Broke Free at register 0 value "<<regisStartValue<<endl;
			break;
		}
	}
	
	
	// cout<<"Register values "<<registers[0]<<", "<<registers[1]<<", "<<registers[2]<<", "<<registers[3]<<", "<<registers[4]<<", "<<registers[5]<<endl;
	cout<<"Done"<<endl;

	return 0;
}
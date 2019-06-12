// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <utility>
#include <tuple>
#include <memory>
#include <map>
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

struct unit
{
	int type; // 0 = gnome, 1 = elf
	int row;
	int col;
	int nextRow = 0;
	int nextCol = 0;
	int attackPower = 3;
	int health = 200;
	bool isAlive = true;
	
	// unit();
	
	unit(int type, int row, int col) :
	type(type),
	row(row),
	col(col)
	{
		
	};
	
	char getType() const
	{
		return (type == 0) ? 'G' : 'E';
	}
	
	void print() const
	{
		string t = type == 0 ? "Gnome ":"Elf ";
		cout<<t<<" at pos "<<row<<", "<<col<<" has health "<<health<<" and attacking power "<<attackPower<<endl;
	}
	
};

void printUnits(const vector<unit>& units)
{
	cout<<"Units are"<<endl;
	for (const unit& u : units)
	{
		if (u.isAlive)
			u.print();
	}
}

void print(vector<vector<char>>& area)
{
	for (const vector<char>& row : area)
	{
		for (char c : row)
		{
			cout<<c;
		}
		cout<<endl;
	}
}

int shortestLenToTarget(int row, int col, int type, vector<vector<char>>& grid, map<pair<int, int>, int>& visitedMap, int currentCount, int unitR, int unitC)
{
	// current unit pos
	if (row == unitR && col == unitC)
		return 10000;
		
	pair<int, int> rc = make_pair(row, col);
	char ch = grid[row][col];
	
	// wall
	if (ch == '#')
	{
		// cout<<row<<", "<<col<<" wall "<<endl;
		visitedMap[rc] = 10000;
		return 10000;
	}
		
	// found unit of same kind
	if ((type == 0 && ch == 'G') || (type == 1 && ch == 'E'))
	{
		// cout<<row<<", "<<col<<" same kind "<<endl;
		visitedMap[rc] = 10000;
		return 10000;
	}
		
	if (visitedMap.find(rc) != visitedMap.end())
	{
		int existingMinCount = visitedMap[rc];
		if (existingMinCount <= currentCount)
		{
			// cout<<row<<", "<<col<<" min from map "<<existingMinCount<<endl;
			return 10000;
			// return existingMinCount;
		}
		else
			visitedMap[rc] = currentCount;
	}
	else
	{
		// cout<<row<<", "<<col<<" init map "<<endl;
		visitedMap[rc] = currentCount;
	}
	
	// found a target
	if (ch != '.')
	{
		// cout<<"Found target at "<<row<<", "<<col<<" -> "<<currentCount<<endl;
		// visitedMap[rc] = currentCount;
		return currentCount;
	}

	// cout<<row<<", "<<col<<endl;
	
	
	int top = shortestLenToTarget(row - 1, col, type, grid, visitedMap, currentCount + 1, unitR, unitC);
	int left = shortestLenToTarget(row, col - 1, type, grid, visitedMap, currentCount + 1, unitR, unitC);
	int right = shortestLenToTarget(row, col + 1, type, grid, visitedMap, currentCount + 1, unitR, unitC);
	int bottom = shortestLenToTarget(row + 1, col, type, grid, visitedMap, currentCount + 1, unitR, unitC);
	
	int minCount = min(min(left ,right), min(top, bottom));
	
	// cout<<row<<", "<<col<<" -> "<<left<<", "<<right<<", "<<top<<", "<<bottom<<endl;
	// cout<<"returning "<<minCount<<endl;
	// visitedMap[rc] = minCount;
	
	return minCount;
}

pair<bool, pair<int, int>> findTarget(int row, int col, int type, vector<vector<char>>& grid)
{
	map<pair<int, int>, int> visitedMap;
	
	// visitedMap[make_pair(row, col)] = true;
	
	int top = shortestLenToTarget(row - 1, col, type, grid, visitedMap, 1, row, col);
	// cout<<"---------------------------------------"<<endl;
	int left = shortestLenToTarget(row, col - 1, type, grid, visitedMap, 1, row, col);
	// cout<<"---------------------------------------"<<endl;
	int right = shortestLenToTarget(row, col + 1, type, grid, visitedMap, 1, row, col);
	// cout<<"---------------------------------------"<<endl;
	int bottom = shortestLenToTarget(row + 1, col, type, grid, visitedMap, 1, row, col);
	
	
	int minLen = min(min(left ,right), min(top, bottom));
	
	// cout<<row<<", "<<col<<" -> "<<left<<", "<<right<<", "<<top<<", "<<bottom<<" minLen is "<<minLen<<endl;

	if (minLen >= 10000)
		return make_pair(false, make_pair(0 , 0));
		
	if (minLen == top)
		return make_pair(true, make_pair(row - 1, col));
		
	if (minLen == left)
		return make_pair(true, make_pair(row, col - 1));
		
	if (minLen == right)
		return make_pair(true, make_pair(row, col + 1));
		
	if (minLen == bottom)
		return make_pair(true, make_pair(row + 1, col));
}

bool shouldAttack(int row, int col, char type, vector<vector<char>>& grid)
{
	char c = grid[row][col];
	if (c == '.' || c == type)
		return false;
	else
		return true;
}

int getHealthOfUnit(int row, int col, const vector<unit>& units)
{
	for (const unit& u : units)
	{
		if (u.isAlive && u.row == row && u.col == col)
			return u.health;
	}
}

void attack(const unit& current, vector<unit>& units, vector<vector<char>>& grid, int& noOfGnomes, int& noOfElves)
{
	for (unit& u : units)
	{
		if (u.isAlive && u.row == current.nextRow && u.col == current.nextCol)
		{
			int newHealth = u.health - current.attackPower;
			u.health = newHealth;
			if (newHealth <= 0)
			{
				u.isAlive = false;
				grid[u.row][u.col] = '.';
				
				char type = u.getType();
				if (type == 'G')
					noOfGnomes--;
				else
					noOfElves--;
				
				u.row = -1;
				u.col = -1;
			}
			
			return;
		}
	}
}

void increaseAttackPowerOfElvesAndReset(vector<unit>& units, vector<unit>& initialState, int extraPower)
{
	// units.clear();
	for (int i = 0; i < initialState.size(); i++)
	{
		const unit& initialStateUnit = initialState[i];
		unit& newUnit = units[i];
		
		newUnit.type = initialStateUnit.type;
		newUnit.row = initialStateUnit.row;
		newUnit.col = initialStateUnit.col;
		newUnit.nextRow = 0;
		newUnit.nextCol = 0;
		newUnit.health = 200;
		newUnit.isAlive = true;
		
		if (initialStateUnit.type == 1)
		{
			newUnit.attackPower = initialStateUnit.attackPower + extraPower;
		}
		else
		{
			newUnit.attackPower = 3;
		}
		
		// units.emplace_back(newUnit);
	}
	// cout<<"new States "<<endl;
	// printUnits(units);
}

void resetGrid(vector<vector<char>>& grid, const vector<unit>&units)
{
	// clea existing locations
	for (vector<char>& row : grid)
	{
		for (char& c : row)
		{
			if (c == 'E' || c =='G')
				c = '.';
		}
	}
	
	// print(grid);
	
	// place the units
	for (const unit& u : units)
	{
		grid[u.row][u.col] = u.getType();
	}
}

int main()
{ 
	string line;
	string delimiters = " ,=.";
	ifstream myfile ("input.txt");
	
	vector<vector<char>> grid;
	vector<unit> units;
	vector<unit> initialState;
	
	int noOfElves = 0;
	int noOfGnomes = 0;
	const int cDontAttack = 1000;
	
	if (myfile.is_open())
	{
		int r = 0;
		while (getline(myfile,line))
		{
			int col = 0;
			vector<char> row;
			for (char c : line)
			{
				row.push_back(c);
				
				if (c == 'G')
				{
					units.emplace_back(0 /*type*/, r, col);
					initialState.emplace_back(0 /*type*/, r, col);
					noOfGnomes++;
				}
				else if (c == 'E')
				{
					units.emplace_back(1 /*type*/, r, col);
					initialState.emplace_back(1 /*type*/, r, col);
					noOfElves++;
				}
				col++;
			}
			grid.emplace_back(row);
			r++;
		}
		myfile.close();
	}
	
	// print(grid);
	
	
	int noOfRounds = 0;
	bool shouldEndCombat = false;
	bool elfKilled = false;
	
	const int initialNoOfElves = noOfElves;
	const int initialNoOfGnomes = noOfGnomes;
	int extraPower = 0;
	
	while (true)
	{
		elfKilled = false;
		shouldEndCombat = false;
		noOfRounds = 0;
		noOfElves = initialNoOfElves;
		noOfGnomes = initialNoOfGnomes;
		
		cout<<"\n\nNew combat --------------------------------------------"<<extraPower<<endl;
		// printUnits(units);
		
		while (!shouldEndCombat)
		{
			// Sort to get the units in the correct order
			sort(units.begin(), units.end(), [](unit lhs, unit rhs)
			{
				if (lhs.row != rhs.row)
					return lhs.row < rhs.row;
				else
					return lhs.col < rhs.col;
			});
			
			// cout<<"Sorted"<<endl;
			// cout<<"New combat --------------------------------------------"
			// printUnits(units);
			
			for (int i = 0; i < units.size(); i++)
			{
				unit& current = units[i];
				
				if (!current.isAlive)
					continue;
	
				// current.print();
				int type = current.type;
				char charType = current.getType();
				
				// find if targets available
				if ((type == 0 && noOfElves == 0) || (type == 1 && noOfGnomes == 0))
				{
					cout<<"No target found "<<noOfRounds<<endl;
					shouldEndCombat = true;
					break;
				}
				
				// find target
				pair<bool, pair<int, int>> target = findTarget(current.row, current.col, type, grid);
				
				// cout<<target.first<<" -- "<<target.second.first<<", "<<target.second.second<<endl;
				if (target.first == false)
					continue;
					
				int nextRow = target.second.first;
				int nextCol = target.second.second;
				
				char nextChar = grid[nextRow][nextCol];
				
				if (nextChar == '.')
				{
					// Move
					// cout<<"Move "<<endl;
					grid[nextRow][nextCol] = grid[current.row][current.col];
					grid[current.row][current.col] = '.';
					
					current.row = nextRow;
					current.col = nextCol;
				}
				// else
				
				{
					// cout<<"Attack "<<nextRow<<","<<nextCol<<endl;
					// Attack
					int row = current.row;
					int col = current.col;
					
					int top = shouldAttack(row - 1, col, charType, grid) ? getHealthOfUnit(row - 1, col, units) : cDontAttack;
					int left = shouldAttack(row, col - 1, charType, grid) ? getHealthOfUnit(row, col - 1, units) : cDontAttack;
					int right = shouldAttack(row, col + 1, charType, grid) ? getHealthOfUnit(row, col + 1, units) : cDontAttack;
					int bottom = shouldAttack(row + 1, col, charType, grid) ? getHealthOfUnit(row + 1, col, units) : cDontAttack;
		
					int minHealth = min(min(left ,right), min(top, bottom));
					
					if (minHealth == cDontAttack)
						continue;
					// cout<<"Attack "<<endl;
					if (minHealth == top)
					{
						current.nextRow = row - 1;
						current.nextCol = col;
					}
					else if(minHealth == left)
					{
						current.nextRow = row;
						current.nextCol = col - 1;
					}
					else if(minHealth == right)
					{
						current.nextRow = row;
						current.nextCol = col + 1;
					}
					else if (minHealth == bottom)
					{
						current.nextRow = row + 1;
						current.nextCol = col;
					}
						
					attack(current, units, grid, noOfGnomes, noOfElves);
					
					if (noOfElves != initialNoOfElves)
					{
						elfKilled = true;
						break;
					}
				}
				// break;
			}
			
			if (elfKilled)
			{
				cout<<"Elf killed at extraPower "<<extraPower<<" in round "<<noOfRounds<<endl;
				extraPower++;
				increaseAttackPowerOfElvesAndReset(units, initialState, extraPower);
				resetGrid(grid, units);
				// print(grid);
				break;
			}
	
			if (!shouldEndCombat)
				noOfRounds++;
			
			// cout<<"Round "<<noOfRounds<<endl;
			// print(grid);
		}
		
		if (!elfKilled/* || extraPower == 2*/)
			break;
	}
	
	cout<<"\n\n####################################################################"<<endl;
	print(grid);
	printUnits(units);
	
	
	int totalHealth = 0;
	for (const unit& u : units)
	{
		if (u.isAlive)
			totalHealth += u.health;
	}
	
	int outcome = noOfRounds * totalHealth;
	cout<<"\n NoOfRounds "<<noOfRounds<<endl;
	cout<<"Outcome is "<<outcome<<endl;
	cout<<"Done"<<endl;

	return 0;
}
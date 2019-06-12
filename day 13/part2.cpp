// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

  string moveLeft(string& dir)
  {
      if (dir == "top")
      {
          return "left";
      }
      else if (dir == "left")
      {
          return "down";
      }
      else if (dir == "down")
      {
          return "right";
      }
      else if (dir == "right")
      {
          return "top";
      }
  }
  
string moveRight(string& dir)
  {
      if (dir == "top")
      {
          return "right";
      }
      else if (dir == "left")
      {
          return "top";
      }
      else if (dir == "down")
      {
          return "left";
      }
      else if (dir == "right")
      {
          return "down";
      }
  }

struct car
{
  int col;
  int row;
  string direction;
  string nextTurn = "left"; // str, right
  int id;
  bool isAlive = true;
  
  car(int row, int col, string dir, int id) :
  row(row),
  col(col),
  direction(dir),
  id(id)
  { };
  
  void print()
  {
      cout<<"Car "<<id<<" at "<<row<<" row and "<<col<<" col "<<"dir: "<<direction<<" next turn "<<nextTurn<<endl;
  }
  
  void move(const vector<vector<char>>& grid)
  {
      int nextRow = row;
      int nextCol = col;
      
      if (direction == "left")
      {
          nextCol--;
      }
      else if (direction == "right")
      {
          nextCol++;
      }
      else if (direction == "top")
      {
          nextRow--;
      }
      else if (direction == "down")
      {
          nextRow++;
      }
      
      char nextChar = grid[nextRow][nextCol];
      
      // cout<<"car "<<id<<" Next Char "<<nextChar<<endl;
      // print();
      // cout<<row<<", "<<col<<" to "<<nextRow<<", "<<nextCol<<endl;
      // print();
      
      row = nextRow;
      col = nextCol;
      
      
      if (nextChar == '+')
      {
          if (nextTurn == "left")
          {
              direction = moveLeft(direction);
              nextTurn = "str";
          }
          else if (nextTurn == "right")
          {
              direction = moveRight(direction);
              nextTurn = "left";
          }
          else if (nextTurn == "str")
          {
              nextTurn = "right";
          }
          
          // print();
      }
      else if (nextChar == '\\')
      {
          if (direction == "right")
            direction = "down";
          else if (direction == "left")
            direction = "top";
          else if (direction == "top")
            direction = "left";
          else if (direction == "down")
            direction = "right";
      }
      else if (nextChar == '/')
      {
          if (direction == "right")
            direction = "top";
          else if (direction == "left")
            direction = "down";
          else if (direction == "top")
            direction = "right";
          else if (direction == "down")
            direction = "left";
      }
      else if (nextChar == '-' || nextChar == '|')
      {
          // noop
      }
      else
      {
          // cout<<"Unknown char "<<nextChar<<endl;
        //   cout<<"Crashed at "<<row<<", "<<col<<endl;
      }
  }
};

bool compareByLength(const car &a, const car &b)
{
    return a.row < b.row && a.col< b.col;
}

void printAllCars(vector<car>& cars)
{
    for (car& c : cars)
    {
        c.print();
    }
}

void didCrash(vector<car>& cars)
{
    set<pair<int, int>> locations;
    set<pair<int, int>> crashedLocations;
            
    for (const car& c : cars)
    {
      // cout<<"old size "<<cars.size()<<endl;
        pair<int, int> location = make_pair(c.row, c.col);
        
        if (!locations.insert(location).second)
        {
            // cout<<"old size "<<cars.size()<<endl;
            // printAllCars(cars);
            cout<<"Car "<<c.id<<" Crashed at "<<c.row<<", "<<c.col<<endl;
            crashedLocations.insert(location);
            // break;
        }
    }
    
    if (!crashedLocations.empty())
    {
        cout<<"old size "<<cars.size()<<endl;
        // printAllCars(cars);
    }
    
        
    for (car& c : cars)
    {
       pair<int, int> p = make_pair(c.row, c.col);
       if (crashedLocations.find(p) != crashedLocations.end())
       {
         c.isAlive = false;
       }
       
    }
        
    if (!crashedLocations.empty())
    {
        cout<<"New size "<<cars.size()<<endl;
        cout<<"crashed loc "<<crashedLocations.size()<<endl;
        // printAllCars(cars);
        
    }
    
    return ;
}


int main()
{
	string line;
	string delimiters = "";
	ifstream myfile ("input.txt");
	
	string initialState;
	vector<vector<char>> grid;
	vector<car> cars;
	
	if (myfile.is_open())
	{
		int row = 0;
    int id = 0;
		while ( getline(myfile,line) )
		{
		        int col = 0;
            vector<char> words;
            for (char c : line)
            {
                words.emplace_back(c);

                if (c == '<')
                {
                    cars.emplace_back(row, col, "left", id);
                    id++;
                }
                else if (c == '>')
                {
                    cars.emplace_back(row, col, "right", id);
                    id++;
                }
                else if (c == '^')
                {
                    cars.emplace_back(row, col, "top", id);
                    id++;
                }
                else if (c == 'v')
                {
                    cars.emplace_back(row, col, "down", id);
                    id++;
                }
                col++;
            }
            
            row++;
            
            grid.emplace_back(words);
		}
		myfile.close();
	}
	
	cout<<grid.size()<<" rows and "<<grid[0].size()<<" cols "<<endl;
	
	// move
	int it = 0;
	while(cars.size()>1)
	{
	    sort(cars.begin(), cars.end(), compareByLength);
	    bool shouldExit = false;
	   // cout<<"it "<<it<<endl;
	   //printAllCars(cars);
	    for (car& c : cars)
	    {
	       if (c.isAlive)
	       {
	         c.move(grid);
	         didCrash(cars);
	       }
	    }
	    
	  cars.erase(
        remove_if(cars.begin(), 
                cars.end(), 
                [](car& c)
                {
                    return !c.isAlive;
                }),
        cars.end());
        
    cout<<"cars size after all collisions "<<cars.size();
	   
	   // cout<<"after move"<<endl;
	   // printAllCars(cars);
	    it++;
	    
      if (cars.size() == 1)
      {
          printAllCars(cars);
          break;
      }
	}
  printAllCars(cars);
	cout<<"Done"<<endl;
	
	return 0;
}
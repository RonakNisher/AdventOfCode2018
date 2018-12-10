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

int sumMetadata = 0;

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

struct Node
{
public:
  string name;
  int children = 0;
  int metadata = 0;

  Node() = default;
  
  void print()
  {
      cout<<" children "<<children<<" metadata "<<metadata<<endl;
  }
  
};

int recurse(const vector<string>& input, int currentPos)
{
    if (currentPos > input.size() - 1)
        return input.size();
        
    int noOfChildren = stoi(input[currentPos]);
    int noOfMetadata = stoi(input[currentPos + 1]);
    
    // cout<<"currentPos: "<<currentPos<<" noOfChildren: "<<noOfChildren<<" noOfMetadata: "<<noOfMetadata<<endl;
    
    int nextPos = currentPos + 1;
    
    // recurse on children
    while (noOfChildren != 0)
    {
        // cout<<"nextPos "<<nextPos<<endl;
        nextPos = recurse(input, ++nextPos);
        noOfChildren--;
    }
    
    // do metadata
    while (noOfMetadata != 0)
    {
        // cout<<"metadata pos "<<nextPos+1<<endl;
        sumMetadata+= stoi(input[++nextPos]);
        
        noOfMetadata--;
    }
    
    return nextPos;
    
}

int main()
{
	string line;
	string delimiters = " ";
	ifstream myfile ("input.txt");
	
	vector<string> words;
	
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
            words = split(line, delimiters);
		}
		myfile.close();
	}
	
	recurse(words, 0);
	
	cout<<"sumMetadata "<<sumMetadata<<endl;
	
	cout<<"Done"<<endl;

	return 0;
}
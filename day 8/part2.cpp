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

int recurse(const vector<string>& input, int currentPos, int& weight)
{
    if (currentPos > input.size() - 1)
        return input.size();
        
    int sumWeight = 0;
        
    const int noOfChildren = stoi(input[currentPos]);
    int noOfMetadata = stoi(input[currentPos + 1]);
    
    vector<int> childWeights;
    
    // cout<<"currentPos: "<<currentPos<<" noOfChildren: "<<noOfChildren<<" noOfMetadata: "<<noOfMetadata<<endl;
    
    int nextPos = currentPos + 1;
    
    // recurse on children
    int i = noOfChildren;
    while (i != 0)
    {
        int weight = 0;
        nextPos = recurse(input, ++nextPos, weight);
        cout<<"weight "<<weight<<endl;
        childWeights.push_back(weight);
        i--;
    }
    
    // do metadata
    while (noOfMetadata != 0)
    {
        // cout<<"metadata pos "<<nextPos+1<<endl;
        int metadataIndex = stoi(input[++nextPos]);
        
        sumMetadata+= metadataIndex;
        
        if (metadataIndex <= noOfChildren)
        {
            sumWeight+= childWeights[metadataIndex - 1];
        }
        else if (noOfChildren == 0)
        {
            sumWeight+=metadataIndex;
        }
        
        noOfMetadata--;
    }
    
    cout<<"currentPos "<<currentPos<<" weight "<<sumWeight<<endl;
    weight = sumWeight;
    
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
	
	int weight;
	recurse(words, 0, weight);
	
	cout<<"weight "<<weight<<endl;
	cout<<"sumMetadata "<<sumMetadata<<endl;
	
	cout<<"Done"<<endl;

	return 0;
}
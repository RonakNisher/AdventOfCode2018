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

struct Node
{
public:
  string name;
  int pendingDependencies = 0;
  vector<Node*> forwardConnections; 
  
  Node() = default;
  
  Node(string n) :
  name(n)
  {};
  
  void print()
  {
      cout<<"Node "<<name<<" pendingDependencies "<<pendingDependencies<<endl;
      cout<<"Forward Connections ";
      for (const Node* forwardConnection : forwardConnections)
      {
          cout<<forwardConnection->name<<" ";
      }
      cout<<endl;
  }
  
};

int main()
{
	string line;
	string delimiters = " ";
	ifstream myfile ("input.txt");
	
	map<string, Node*> nodesMap;
	
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
            vector<string> words = split(line, delimiters);
            
            string originName = words[1];
            string destName = words[7];
            const auto itOriginNode = nodesMap.find(originName);
            const auto itDestNode = nodesMap.find(destName);
            
            if (itDestNode == nodesMap.end())
            {
                Node* destNode = new Node(destName);
                destNode->pendingDependencies = 1;
                nodesMap[destName] = destNode;
            }
            else
            {
                itDestNode->second->pendingDependencies++;
            }
            
            if (itOriginNode == nodesMap.end())
            {
                Node* originNode = new Node(originName);
                originNode->pendingDependencies = 0;
                originNode->forwardConnections.emplace_back(nodesMap[destName]);
                nodesMap[originName] = originNode;
            }
            else
            {
                itOriginNode->second->forwardConnections.emplace_back(nodesMap[destName]);
            }
		}
		myfile.close();
	}
	
	set<string> unprocessedItems;
	
	for (auto it = nodesMap.begin(); it != nodesMap.end(); it++)
	{
	   // it->second->print();
	    if (it->second->pendingDependencies == 0)
	        unprocessedItems.insert(it->second->name);
	}

	string order;
	
	while (!unprocessedItems.empty())
	{
	    auto first = unprocessedItems.begin();
	   // cout<<"Processing "<<*first<<endl;
	    order.append(*first);
	    
	    unprocessedItems.erase(first);
	    
	    for (Node* item : nodesMap[*first]->forwardConnections)
	    {
	        item->pendingDependencies--;
	        if (item->pendingDependencies == 0)
	        {
    	       // cout<<"Inserting "<<item->name<<endl;
    	        unprocessedItems.insert(item->name);
	        }
	    }
	}
	
	cout<<"Order is "<<order<<endl;

	return 0;
}
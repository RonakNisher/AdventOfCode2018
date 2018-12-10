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
  char name;
  int pendingDependencies = 0;
  vector<Node*> forwardConnections;
  int timeLeftToProcess;
  
  Node() = default;
  
  Node(char n) :
  name(n)
  {
      timeLeftToProcess = name - 64;
  };
  
  void print()
  {
      cout<<"Node "<<name<<" pendingDependencies "<<pendingDependencies<<"Time left to process "<<timeLeftToProcess<<endl;
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
	
	map<char, Node*> nodesMap;
	
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
            vector<string> words = split(line, delimiters);
            
            char originName = words[1][0];
            char destName = words[7][0];
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
	
	set<char> unprocessedItems;
	
	for (auto it = nodesMap.begin(); it != nodesMap.end(); it++)
	{
	   // it->second->print();
	    if (it->second->pendingDependencies == 0)
	        unprocessedItems.insert(it->second->name);
	}

	string order;
	int totalWorkers = 5;
	int workersFree = totalWorkers;
	int totalTime = 0;
	
	while (!unprocessedItems.empty())
	{
	    set<char> nodesToAdd;
	    set<char> nodesToDelete;
	    
	   // cout<<"unprocessedItems queue size "<<unprocessedItems.size()<<endl;
	    for (auto it = unprocessedItems.begin(); it != unprocessedItems.end(); it++)
	    {
	        auto nodeToProcess = nodesMap[*it];
	       // cout<<"Looking at "<<nodeToProcess->name<<endl;
	        if (workersFree > 0)
	        {
	            workersFree--;
	            nodeToProcess->timeLeftToProcess--;
	           // cout<<"processing "<<nodeToProcess->name<<" time left "<<nodeToProcess->timeLeftToProcess<<endl;

	            if (nodeToProcess->timeLeftToProcess == 0)
	            {
	                nodesToDelete.insert(nodeToProcess->name);
	               // unprocessedItems.erase(it);
            	    
            	    for (Node* item : nodeToProcess->forwardConnections)
            	    {
            	        item->pendingDependencies--;
            	        if (item->pendingDependencies == 0)
            	        {
                	       // cout<<"Inserting "<<item->name<<endl;
                	        nodesToAdd.insert(item->name);
            	        }
            	       // cout<<"done children with "<<item->name<<endl;
            	    }
	            }
	        }
	       // cout<<"done looking at "<<nodeToProcess->name<<endl;
	    }
	    
	    workersFree = totalWorkers;
	   // cout<<"delete"<<endl;
	    
	    for (auto it = nodesToDelete.begin(); it != nodesToDelete.end(); it++)
	    {
	       // cout<<"deleting "<<*it<<endl;
	       // if (unprocessedItems.find(*it) != unprocessedItems.end())
	            unprocessedItems.erase(*it);
	    }
	    
	   // if (!nodesToDelete.empty())
	   //     unprocessedItems.erase(nodesToDelete.begin(), nodesToDelete.end());
	        
	    nodesToDelete.clear();
	    
	   // cout<<"add"<<endl;
	    
    // 	cout<<"newly added "<<nodesToAdd.size()<<endl;
    	unprocessedItems.insert(nodesToAdd.begin(), nodesToAdd.end());
    	
    // 	cout<<"unprocessedItems queue end size "<<unprocessedItems.size()<<endl;
    	nodesToAdd.clear();
    	
    	totalTime++;
	}
	
	cout<<"time is "<<totalTime<<endl;
// 	cout<<"Order is "<<order<<endl;

	return 0;
}
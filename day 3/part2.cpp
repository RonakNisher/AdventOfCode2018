#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

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

struct claim
{
	int id;
    int left;
    int top;
    int width;
    int height;
    
    claim(int i, int l, int t, int w, int h):
    id(i),
    left(l),
    top(t),
    width(w),
    height(h){};
    
    void print()
    {
    	cout<<"id: "<<id<<" -> left: "<<left<<", top: "<<top<<" : width: "<<width<<", height: "<<height<<endl;
    }
    
};

void print(std::vector<string>& words)
{
	for (const string& word : words)
	{
		cout<<word<<" ";
	}
	cout<<endl;
}

int main()
{
	string line;
	int result = 0;
	ifstream myfile ("input.txt");
	const string delimiters = "#@,:x ";
	
	vector<claim> claims;
	
	vector<vector<int>> fabric;
	fabric.reserve(2000);
	
	for(int i = 0; i < 2000; i++)
	{
		vector<int> rows(2000,0);
		fabric.emplace_back(rows);
	}
	
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			std::vector<string> words = split(line, delimiters);
			
			print(words);

			claims.emplace_back(stoi(words[0]), stoi(words[1]), stoi(words[2]), stoi(words[3]), stoi(words[4]));
		}
		myfile.close();
	}
	
	int overlapCount = 0;
	list<int> nonOverlappedIds;
	
	for (const claim& c : claims)
	{
	    bool overlapFound = false;
	    
		int topLeftX = c.left;
		int topLeftY = c.top;
		
// 		cout<<topLeftX<<","<<topLeftY<<endl;
		
		for (int row = 0; row < c.width; row++)
		{
			for (int col = 0; col < c.height; col++)
			{
				int existingValue = fabric[row + topLeftX][col + topLeftY];
				if (existingValue == -1)
					continue;
					
				if (existingValue == 0)
					fabric[row + topLeftX][col + topLeftY] = c.id;
				else
				{
				    nonOverlappedIds.remove(existingValue);
					cout<<"Overlap for id "<<c.id<<" at "<<row + topLeftX<<", "<<col + topLeftY;
					fabric[row + topLeftX][col + topLeftY] = -1;
					overlapCount++;
					overlapFound = true;
				}
			}
		}
		if (!overlapFound)
	        nonOverlappedIds.push_back(c.id);
		
	}
	
// 	claims[0].print();
	
	cout<<"done "<<overlapCount<<endl;
	std::cout << nonOverlappedIds.front() << std::endl;

	return 0;
}
// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	string line;
	
	ifstream myfile ("input.txt");
	
	vector<string> boxes;
	string finalBox;
	
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			boxes.emplace_back(line);
		}
		myfile.close();
	}
	
	sort(boxes.begin(), boxes.end());
	
	for (int i = 0; i < boxes.size() - 1; i++)
	{
	    string& word1 = boxes[i];
	    string& word2 = boxes[i+1];
	    
	    int mismatchCount = 0;
	    int mismatchIndex = 0;
	    
        for (int j = 0; j<word1.size(); j++)
        {
            if (word1[j] != word2[j])
            {
                mismatchCount++;
                mismatchIndex = j;
            }
        }
        
        if (mismatchCount == 1)
        {
            cout<<word1<<" and "<<word2<<endl;
            finalBox = word1.erase(mismatchIndex,1);
            break;
        }
	    
	}
	
	cout<<"done "<<finalBox<<endl;

	return 0;
}
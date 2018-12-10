// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <cmath>

using namespace std;

int main()
{
	string line;
	
	ifstream myfile ("input.txt");
	
	list<char> polymers;
	

	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
	        const int charCount = line.size();
		    polymers.push_back(line[0]);
		    
		    int nextIndex = 1;
		    
		    while (true)
		    {
		        if (!polymers.empty())
		        {
		            char& lastElement = polymers.back();
                    if (nextIndex < charCount)
                    {
                        const char& nextChar = line[nextIndex];
                        if (abs((nextChar - lastElement)) == 32)
                        {
                            polymers.pop_back();
                            nextIndex++;
                            continue;
                        }
                        else
                        {
                            polymers.push_back(line[nextIndex++]);
                        }
                    }
                    else
                    {
                        break; // done
                    }
		        }
		        else
		        {
		            polymers.push_back(line[nextIndex++]);
		        }
		    }
		}
		myfile.close();
	}
	
	cout<<"length is "<<polymers.size()<<endl;
	
	cout<<"done"<<endl;

	return 0;
}
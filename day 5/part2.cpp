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
    int shortestCount = 10000;
	

	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
		    string input;
		    int currCharIndex = 0;
		    for (char c = 'A'; c <= 'Z'; c++ )
		    {
		        polymers.clear();
		        input = "";
		        for (const char& letter : line)
		        {
		            if (!(letter == c || (letter == (c + 32))))
		            {
		                input.push_back(letter);
		            }
		        }
		        
		      //  cout<<"removing letter "<<c<<" the initial count is "<<input.size()<<endl;
		      //  cout<<input<<endl;
		        
    	        const int charCount = input.size();
    		    polymers.push_back(input[0]);
    		    
    		    int nextIndex = 1;
    		    
    		    while (true)
    		    {
    		        if (!polymers.empty())
    		        {
    		            char& lastElement = polymers.back();
                        if (nextIndex < charCount)
                        {
                            const char& nextChar = input[nextIndex];
                            if (abs((nextChar - lastElement)) == 32)
                            {
                                polymers.pop_back();
                                nextIndex++;
                                continue;
                            }
                            else
                            {
                                polymers.push_back(input[nextIndex++]);
                            }
                        }
                        else
                        {
                            break; // done
                        }
    		        }
    		        else
    		        {
    		            polymers.push_back(input[nextIndex++]);
    		        }
    		    }
    		  //  cout<<"redacted count is "<<polymers.size()<<endl;
    		    if (polymers.size() < shortestCount)
    		        shortestCount = polymers.size();
		    }

		}
		myfile.close();
	}
	
	cout<<"length is "<<shortestCount<<endl;
	
	cout<<"done"<<endl;

	return 0;
}
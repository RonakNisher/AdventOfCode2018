// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

void print (list<int>& l)
{
    for (int n : l)
        cout<<n<<" ";
    cout<<endl;
}

int main()
{
    int noOfPlayers = 491;
    int maxMarblePoint = 71058;
    
    vector<int> playerScore(noOfPlayers + 1, 0);
    list<int> circle;
    
    int currentMarble = 0;
    circle.emplace_back(currentMarble++);
    auto currentPosition = circle.begin();
    
    circle.emplace_back(currentMarble++);
    currentPosition++;
    
    int currentPlayer = 1;
    
    while (currentMarble <= maxMarblePoint)
    {
        // cout<<"currentMarble "<<currentMarble<<endl;
        currentPlayer = ((currentPlayer + 1) % noOfPlayers);
        if (currentMarble == 10)
            cout<<"currentPlayer "<<currentPlayer<<endl;
        
        if (currentMarble%23 != 0)
        {
            auto plus1Position = ++currentPosition;
            if (plus1Position == circle.end())
            {
                plus1Position = circle.begin();
            }
            
            auto plus2Position = ++plus1Position;
            // cout<<"Inserting before "<<*plus2Position<<endl;
            circle.insert(plus2Position, currentMarble);
            currentPosition = --plus2Position;
            // cout<<"New current position "<<*currentPosition<<endl;
        }
        else
        {
            int currentPosScore = *currentPosition;
            
            int i = 0;
            while(i != 7)
            {
                if (currentPosition == circle.begin())
                    currentPosition = --circle.end();
                else
                    --currentPosition;
                    
                i++;
            }
            
            // cout<<"item to remove is "<<*currentPosition<<endl;
            
            int score = *currentPosition + currentMarble;
            
            currentPosition = circle.erase(currentPosition);
            
            // cout<<"New current Position is "<<*currentPosition<<endl;
            playerScore[currentPlayer] += score;
            // cout<<"playerScore "<<currentPlayer<<" with score "<<playerScore[currentPlayer]<<" delta of "<<score<<endl;
        }
        
        currentMarble++;
        
        // print(circle);
    }
    
    int max = 0;
    for (int i = 0; i <= noOfPlayers; i++)
    {
        // cout<<"Player "<<i<<" has a score "<<playerScore[i]<<endl;
        if (playerScore[i] > max)
            max = playerScore[i];
    }
	
	cout<<"Max score "<<max<<endl;
	cout<<"Done"<<endl;

	return 0;
}
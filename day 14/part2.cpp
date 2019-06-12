// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

void print(map<long, long>& recipes, long size)
{
    for (int i = 0; i < size; i++)
    {
        cout<<recipes[i];
    }
    cout<<endl;
}

int main()
{
    long input = 681901;
    long stoppingPoint = input + 10;
    vector<long> recipes;
    
    vector<int> digits;
    
    long ip = input;
    while(ip != 0)
    {
        int rem = ip % 10;
        ip = ip / 10;
        digits.push_back(rem);
    }
    
    reverse(digits.begin(), digits.end());
    
    cout<<"input vec "<<endl;
    for (int d : digits)
    {
        cout<<d;
    }
    cout<<endl;
    
    long recipe1Index = 0;
    long recipe2Index = 1;
    
    recipes.push_back(3);
    recipes.push_back(7);
    
    int recipesToLeft = 0;
    int currentMatchIndex = 0;
    
    while (currentMatchIndex < digits.size())
    {
        long newRecipe = recipes[recipe1Index] + recipes[recipe2Index];
        
        int newRecipeIndex1 = newRecipe/10;
        int newRecipeIndex0 = newRecipe % 10;
        
        // tens place
        if (newRecipeIndex1 != 0)
        {
            if (digits[currentMatchIndex] == newRecipeIndex1)
            {
                if (currentMatchIndex == 0)
                    recipesToLeft = recipes.size();
                    
                currentMatchIndex++;
                
                if (currentMatchIndex == digits.size())
                    break;
            }
            else
            {
                currentMatchIndex = 0;
                recipesToLeft = 0;
            }
            
            recipes.push_back(newRecipeIndex1);
        }
        
        // units place
        if (digits[currentMatchIndex] == newRecipeIndex0)
        {
            if (currentMatchIndex == 0)
                recipesToLeft = recipes.size();
                
            currentMatchIndex++;
        }
        else
        {
            currentMatchIndex = 0;
            recipesToLeft = 0;
        }
            
        recipes.push_back(newRecipeIndex0);
        
        // get the new index for recipes
        recipe1Index = (recipe1Index + recipes[recipe1Index] + 1) % recipes.size();
        recipe2Index = (recipe2Index + recipes[recipe2Index] + 1) % recipes.size();
    }
    
    cout<<"recipesToLeft "<<recipesToLeft<<endl;
	cout<<"done"<<endl;
	return 0;
}
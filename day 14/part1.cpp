// #include "../helper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
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
    map<long, long> recipes;
    
    long recipe1Index = 0;
    long recipe2Index = 1;
    
    recipes[recipe1Index] = 3;
    recipes[recipe2Index] = 7;
    
    long size = 2;
    
    
    while (size <= stoppingPoint)
    {
        long newRecipe = recipes[recipe1Index] + recipes[recipe2Index];
        
        // cout<<"starting with "<<recipe1Index<<", "<<recipe2Index<<" results in "<<newRecipe<<endl;
        
        int newRecipeIndex1 = newRecipe/10;
        int newRecipeIndex0 = newRecipe % 10;
        
        
        // tens place
        if (newRecipeIndex1 != 0)
        {
            recipes[size] = newRecipeIndex1;
            ++size;
        }
        
        // units place
        recipes[size] = newRecipeIndex0;
        ++size;
        
        // cout<<"newSize "<<size<<endl;
        
        // get the new index for recipes
        
        // cout<<"rec 1 "<<recipe1Index<<"->"<<recipes[recipe1Index]<<" -> "<<(recipe1Index + recipes[recipe1Index] + 1) % size<<endl;
        // cout<<"rec 2 "<<recipe2Index<<"->"<<recipes[recipe2Index]<<" -> "<<(recipe2Index + recipes[recipe2Index] + 1) % size<<endl;
        recipe1Index = (recipe1Index + recipes[recipe1Index] + 1) % size;
        recipe2Index = (recipe2Index + recipes[recipe2Index] + 1) % size;
        
        // print(recipes, size);
        // cout<<"new index "<<recipe1Index<<", "<<recipe2Index<<endl;
        
        // break;
    }
    
    for (int i = 0; i < 10; i++)
    {
        cout<<recipes[input+i];
    }
    cout<<endl;
    
	cout<<"done"<<endl;
	return 0;
}
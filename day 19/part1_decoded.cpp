// #include "../helper.h"
#include <iostream>

using namespace std;


int main()
{ 
    // the instructions basically decode to finding the sum of all the numbers from 1 to 1024
    // which are divisibles of 1024 (value of r2)
    // part 2 r2 = 10551424
    int result = 0;
    long r2 = 10551424;
    
    for (long i = 1; i <= r2; i++)
    {
        if (r2 % i == 0)
            result += i;
    }
    
    cout<<"result is "<<result<<endl;
	return 0;
}
#include "helper.h"

using namespace std;

namespace helpers
{

	vector<std::string> split(std::string input, const std::string& delimiters)
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

}
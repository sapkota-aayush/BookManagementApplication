#include"Validation.h"
using namespace std;

bool isValidString(const string& input)
{
	if (input.empty())
	{
		return false;
	}

	for (char ch : input)
	{
		if (!isalpha(ch) && ch!= ' ')
		{
			return false;
		}
	}
	return true;
}

//To lower the string
string convertToLower(const string& str)
{
	string lowerStr = str; //creating the copy so that it wont change the original copy
	transform(str.begin(), str.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}

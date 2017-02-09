#include <string>
#include <algorithm>
#include <iostream>

#include <metacall/metacall.h>

using namespace std;

string complex_algorithm(const string & str)
{
	string str_rev(str);

	reverse(str_rev.begin(), str_rev.end());

	return str_rev;
}

int main(int argc, char * argv[])
{
	if (metacall_initialize() != 0)
	{
		cout << "Error initializing metacall" << endl;

		return 1;
	}

	return metacall_destroy();
}

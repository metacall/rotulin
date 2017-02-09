#include <iostream>

#include <metacall/metacall.h>

using namespace std;

void * complex_algorithm(void * args[])
{
	size_t length = metacall_value_size(args[0]) - 1;

	char * str = metacall_value_to_string(args[0]);

	size_t left = 0, right = length - 1;

	while (left < right)
	{
		char old_left = str[left];

		str[left] = str[right];

		str[right] = old_left;

		++left;

		--right;
	}

	return metacall_value_create_string(str, length);
}

int main(int argc, char * argv[])
{
	if (metacall_initialize() != 0)
	{
		cout << "Error initializing metacall" << endl;

		return 1;
	}

	if (metacall_register("complex_algorithm", &complex_algorithm, METACALL_STRING, 1, METACALL_STRING) != 0)
	{
		cout << "Invalid function register" << endl;

		return 1;
	}


	return metacall_destroy();
}

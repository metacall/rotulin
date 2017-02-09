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
	const char * rb_scripts[] =
	{
		"cache.rb"
	};

	/* Initialize MetaCall */
	if (metacall_initialize() != 0)
	{
		cout << "Error initializing metacall" << endl;

		return 1;
	}

	/* Register complex algorithm into MetaCall */
	if (metacall_register("complex_algorithm", &complex_algorithm, METACALL_STRING, 1, METACALL_STRING) != 0)
	{
		cout << "Invalid function register" << endl;

		return 1;
	}

	if (metacall_load_from_file("rb", rb_scripts, sizeof(rb_scripts) / sizeof(rb_scripts[0])) != 0)
	{
		cout << "Invalid ruby script load" << endl;

		return 1;
	}

	/* Initialize ruby cache */
	metacall("cache_initialize");

	/* Test */
	{
		const char key[] = "hello";

		const char value[] = "world";

		metacall("cache_set", key, value);

		void * result = metacall("cache_has_key", key);

		if (result != NULL)
		{
			boolean b = metacall_value_to_bool(result);

			if (b == 1)
			{
				cout << "Value exists" << endl;
			}

			metacall_value_destroy(result);
		}
		else
		{
			cout << "Invalid has key" << endl;
		}

		result = metacall("cache_get", key);

		if (result != NULL)
		{
			const char * str = metacall_value_to_string(result);

			cout << "Value " << str << " == " << value << endl;

			metacall_value_destroy(result);
		}
		else
		{
			cout << "Invalid get" << endl;
		}
	}


	return metacall_destroy();
}

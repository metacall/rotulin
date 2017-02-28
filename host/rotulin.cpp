#include "rotulin.h"

#include <metacall/metacall.h>
#include <iostream>

using namespace std;

/**
 * @brief Load all scripts for rotulin
 */
static int rotulin_load_scripts(void);

int rotulin_initialize()
{
	/* Initialize MetaCall */
	if (metacall_initialize() != 0)
	{
		cerr << "Error initializing MetaCall" << endl;

		return 1;
	}

	return rotulin_load_scripts();
}

int rotulin_load_scripts()
{
	const size_t files_max_size = 3;

	enum script_id
	{
		files,
		package
	};

	struct
	{
		const char * tag;
		const char * files[files_max_size];
		size_t size;
		script_id id;
	}
	scripts[] =
	{
		{ "rb", { "cache.rb" }, 1, files },
		{ "py", { "manage.py" }, 1, files },
		{ "cs", { "image.dll" }, 1, package }
	};

	for (auto script : scripts)
	{
		int result;

		if (script.id == files)
		{
			result = metacall_load_from_file(script.tag, script.files, script.size);
		}
		else
		{
			result = metacall_load_from_package(script.tag, script.files[0]);
		}

		if (result != 0)
		{
			cerr << "Invalid MetaCall file loading: " << script.tag << ", " << script.files[0] << " ..." << endl;

			return 1;
		}
	}

	return 0;
}

int rotulin_run()
{
	/* Run frontend */
	void * ret = metacall("frontend_run", 8080);

	int result = metacall_value_to_int(ret);

	/* Check frontend return value */
	if (result != 0)
	{
		cerr << "Invalid python (frontend) server destruction" << endl;
	}

	/* Destroy return value */
	metacall_value_destroy(ret);

	return result;
}

int rotulin_destroy()
{
	/* Destroy MetaCall */
	if (metacall_destroy() != 0)
	{
		cerr << "Error destroying MetaCall" << endl;

		return 1;
	}

	return 0;
}

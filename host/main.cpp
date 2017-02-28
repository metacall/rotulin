#include "rotulin.h"

#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	/* Initialize Rotulin */
	if (rotulin_initialize() != 0)
	{
		cerr << "Error initializing rotulin" << endl;

		return rotulin_destroy();
	}

	/* Run Rotulin */
	if (rotulin_run() != 0)
	{
		cerr << "Invalid rotulin execution" << endl;
	}

	/* Destroy Rotulin */
	return rotulin_destroy();
}

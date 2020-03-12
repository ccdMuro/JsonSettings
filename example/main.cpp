#include <iostream>
#include "settings.h"

int main (int argc, char** argv)
{
	{
		// set file to read and write 
		// settings in JSON format
		Ccd::Settings settings;
		settings.useThisFile("settings.json");
	} // end of scope 'settings' object gets destroyed

	{
		// new settings object in other scope
		Ccd::Settings settings;

		// read data from file
		auto jOb = settings.read();
		std::cout << jOb << std::endl;

		// read the openCount as int
		// increment it by one
		auto openCount = jOb["openCount"].toInt();
		jOb["openCount"]= openCount +1;

		// write changes back to file
		settings.write(jOb);
	}

	return 0;
}


#include <iostream>
#include <vector>
#include <thread>
#include "settings.h"

constexpr const auto SETTINGS_FILE = "settings.json";
constexpr const auto THREAD_COUNT = 100;

int main (int argc, char** argv)
{
	// Ccd::Settings has a shared state through out
	// all object instances. Once the file to work
	// on is set, all Ccd::Settings object will access
	// this one file for read and write operations.
	std::cout << "Starting Ccd::Settings Example\n";

	// Set the file to work with
	{
		std::cout << "#### Scope 1 ####\n";
		// set file to read and write 
		// settings in JSON format
		Ccd::Settings settings;
		settings.useThisFile("settings.json");
		std::cout << "Using " << SETTINGS_FILE << "\n";
	} // end of scope 'settings' object gets destroyed

	// Simple access
	{
		std::cout << "#### Scope 2 ####\n";

		// new settings object in other scope
		Ccd::Settings settings;

		// read data from file
		auto jOb = settings.read();
		std::cout << "read current settings\n";

		// add new key-value pair to settings
		jOb["state"]= "processed";
		std::cout << "add new entry 'state'\n";

		// write changes back to file
		settings.write(jOb);
		std::cout << "save the changes\n";
	}


	// multi thread access
	{
		std::cout << "#### Multi threaded ####\n";
		Ccd::Settings settings;
		auto jOb = settings.read();
		std::cout << "Settings at the beginning of thread example:\n"
			  << jOb << "\n";

		// here we store all therad handles
		std::vector<std::thread> threads{};

		// create 100 threads that will try to
		// access and edit the settings file
		for ( int i = 0; i < THREAD_COUNT; i++ ) 
		{
			// create a thread with emplace_back
			threads.emplace_back([thread_id=i]() {
				// new settings object in each thread's scope
				Ccd::Settings settings;

				// read data from file
				auto jOb = settings.read();

				// read the openCount as int
				// increment it by one
				// and write it back
				auto openCount = jOb["openCount"].toInt();
				jOb["openCount"]= openCount +1;

				// save the id of the last thread 
				// that accessed the settings
				jOb["thread_ID"]=thread_id;

				// write changes to file
				settings.write(jOb);
					});
		}
		std::cout << "Created " << THREAD_COUNT << " threads that will "
			  << "try to increment the 'openCount' value\n"; 

		for ( auto& threadx : threads ) 
		{
			threadx.join();
		}

		jOb = settings.read();
		std::cout << "Settings at the end of thread example:\n"
			  << jOb << "\n";
	}

	return 0;
}


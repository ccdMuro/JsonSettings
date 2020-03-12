#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <mutex>

#include <JsonPP.h>

namespace Ccd {

class Settings
{
public:
	auto pathToFile (const std::string& filePath) -> void;
	auto read() -> Ccd::Json::Object;
	auto write(Ccd::Json::Object jsonObject) -> void;
	
private:
	static std::string sm_settingsFilePath;
	static std::mutex sm_fileAccessGuard;
};

}


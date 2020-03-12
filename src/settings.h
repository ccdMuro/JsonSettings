#pragma once

#include <string>
#include <JsonPP.h>

namespace Ccd {

class Settings
{
public:
	auto useThisFile (const std::string& filePath) -> void;
	auto read() -> Ccd::Json::Object;
	auto write(Ccd::Json::Object jsonObject) -> void;
	
private:
	static std::string sm_settingsFilePath;
};

}


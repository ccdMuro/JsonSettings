#include "settings.h"

namespace Ccd
{
std::string Settings::sm_settingsFilePath {};

auto Settings::read() -> Ccd::Json::Object
{
	std::ifstream settingsFile {sm_settingsFilePath};
	std::stringstream settingsJSON {};
	std::string line{};
	
	while ( getline( settingsFile, line ) ) {
		settingsJSON << line;
	}

	auto jsonObj = Ccd::Json::JsonPP::objectFromString(settingsJSON.str());

	return jsonObj;
}

auto Settings::write(Ccd::Json::Object jsonObject) -> void 
{
	std::ofstream settingsFile {sm_settingsFilePath};
	settingsFile << jsonObject;	
}

auto Settings::pathToFile(const std::string& filePath) -> void
{
	// sm_ static member
	sm_settingsFilePath = filePath;	
}

}

#include "settings.h"

#include <fstream>
#include <sstream>
#include <thread>

namespace Ccd
{
std::string Settings::sm_settingsFilePath {};
std::mutex Settings::sm_fileAccessGuard {};

auto Settings::read() -> Ccd::Json::Object
{
	std::lock_guard<std::mutex> lock(sm_fileAccessGuard);
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
	std::lock_guard<std::mutex> lock(sm_fileAccessGuard);
	std::ofstream settingsFile {sm_settingsFilePath};
	settingsFile << jsonObject;	
}

auto Settings::useThisFile(const std::string& filePath) -> void
{
	// sm_ static member
	sm_settingsFilePath = filePath;	
}

}

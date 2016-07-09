#pragma once
#include <boost\filesystem.hpp>
#include <vector>
#include <string>

class Filesystem
{
public:
	static std::vector<std::string> scan(std::string directory, std::vector<std::string> filters = { "*" });
private:
};


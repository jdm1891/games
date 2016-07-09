#include "Filesystem.h"
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <iostream>

std::vector<std::string> Filesystem::scan(std::string directory, std::vector<std::string> filters)
{

	//Stores index of directory
	std::vector<std::string> index;

	//This is the end iterator
	boost::filesystem::recursive_directory_iterator end_iterator;

	//Cycle through the directory(and subdirectories)
	
	try
	{
		for (boost::filesystem::recursive_directory_iterator iterator(directory); iterator != end_iterator; ++iterator)
		{
			bool fileAccepted = false;
			//push back name of current file to vector
			std::string current_directory = iterator->path().string();
			std::cout << "Found file: " << current_directory << std::endl;
			//add it to the index(but not if filtered out)
			for (const auto& filter : filters)
			{
				//If there is no filter
				if (filter == "*")
				{
					//Add to index
					index.push_back(current_directory);
					break;
				}
				//if this file has an acceptible extension(filtered)
				else if (iterator->path().extension() == filter)
				{
					std::cout << "File met filter requirements with extension " << iterator->path().extension() << std::endl;
					index.push_back(current_directory);
					fileAccepted = true;
				}
			}
			//If the file did not meet filter requirements
			if (!fileAccepted)
			{
				std::cout << "File didn't meet filter requirements with extension " << iterator->path().extension() << std::endl;
			}
		}
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
	}
	return index;
}



#pragma once
#include "stdafx.h"


class ImageToTileID
{
public:
	//////////////////////////////////////////////////////////////////////////
	/// image is created and destroyed locally - only need to provide filepath
	static std::vector<TileID> ConvertToArray(std::string filepath);
private:
	static std::vector<TileID> notFound();
};


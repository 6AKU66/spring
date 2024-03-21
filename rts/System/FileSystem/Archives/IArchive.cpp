/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#include "IArchive.h"

#include "System/StringUtil.h"

#include <tracy/Tracy.hpp>

unsigned int IArchive::FindFile(const std::string& filePath) const
{
	//ZoneScoped;
	const std::string& normalizedFilePath = StringToLower(filePath);
	const auto it = lcNameIndex.find(normalizedFilePath);

	if (it != lcNameIndex.end())
		return it->second;

	return NumFiles();
}

bool IArchive::CalcHash(uint32_t fid, uint8_t hash[sha512::SHA_LEN], std::vector<std::uint8_t>& fb)
{
	//ZoneScoped;
	// NOTE: should be possible to avoid a re-read for buffered archives
	if (!GetFile(fid, fb))
		return false;

	if (fb.empty())
		return false;

	sha512::calc_digest(fb.data(), fb.size(), hash);
	return true;
}

bool IArchive::GetFile(const std::string& name, std::vector<std::uint8_t>& buffer)
{
	//ZoneScoped;
	const unsigned int fid = FindFile(name);

	if (!IsFileId(fid))
		return false;

	GetFile(fid, buffer);
	return true;
}


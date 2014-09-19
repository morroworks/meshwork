//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Copyright (C) 2014  Ivan Donev
//
//	This library is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3.0 as published by the Free Software Foundation
//	This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//	See the GNU LGPL v3.0 for more details. You should have received a copy of the GNU LGPL v3.0 along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//	For help and documentation on the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "MwFileSystem.h"

#include "..\Tools\\MwMath.h"
#include "..\Tools\MwStrings.h"

const wchar_t MwFileSystem::dirSplitter = L'\\';
const wchar_t MwFileSystem::extensionSplitter = L'.';
const wchar_t MwFileSystem::rootSignature = L':';
const wchar_t *MwFileSystem::previousDir = L"..";
const wchar_t *MwFileSystem::currentDir = L".";

MwFileSystem::MwFileSystem(void)
{
}


MwFileSystem::~MwFileSystem(void)
{
}

bool MwFileSystem::FileExists(MwString path)
{
	MwFileInfo fileInfo;

	bool exists = this->GetFileInfo(path, fileInfo);

	return exists && (!fileInfo.isDirectory);
}

bool MwFileSystem::DirectoryExists(MwString path)
{
	MwFileInfo fileInfo;

	bool exists = this->GetFileInfo(path, fileInfo);

	return exists && (fileInfo.isDirectory);
}

bool MwFileSystem::FileOrDirectoryExists(MwString path)
{
	MwFileInfo fileInfo;
	return this->GetFileInfo(path, fileInfo);
}

bool MwFileSystem::IsAbsolutePath(MwString path)
{
	int firstDelimiter = path.IndexOf(MwFileSystem::dirSplitter);
	if (firstDelimiter == -1)
		firstDelimiter = path.length;
	return path.IndexOf(MwFileSystem::rootSignature) != -1;
}

MwString MwFileSystem::GetSymbolicSize(unsigned long long size, int magnitudeBase, int magnitudeThreshold)
{
	const int numMagnitudes = 6;
	const char *magnitudeNames[numMagnitudes] = { "B", "KB", "MB", "GB", "TB", "PB" };

	unsigned long long threshold = magnitudeBase * magnitudeThreshold;
	int magnitudeIndex = 0;
	while ((size > threshold) && (magnitudeIndex < numMagnitudes))
	{
		size /= magnitudeBase;
		magnitudeIndex++;
	}

	return MwString(MwString((int)size) + " " + magnitudeNames[magnitudeIndex]);
}

MwString MwFileSystem::GetRelativeFilePath(MwString &basePath, MwString &path)
{
	if (basePath.length == 0)
        return MwString(path);

	MwString fullBasePath = basePath;
	if (!fullBasePath.EndsWith(MwFileSystem::dirSplitter))
		fullBasePath += MwFileSystem::dirSplitter;

    // Find the delimiter, until which path and fullBasePath are the same
	int delimiter = -1;
    int index = 0;
    int length = MwMath::Min(fullBasePath.length, path.length);
    while (index < length)
    {
        if (path[index] == fullBasePath[index])
        {
			if (path[index] == MwFileSystem::dirSplitter)
            {
                delimiter = index;
            }
        }
        else
            break;

        index++;
    }

    MwString result;

    // If the file is not inside of the the fullPath directory (or in an inner directory), then add a back path
	if (delimiter != (fullBasePath.length - 1))
    {
        int pos = delimiter;
        do
        {
			pos = fullBasePath.IndexOf(MwFileSystem::dirSplitter, pos + 1);
            if (pos != -1)
				result += MwString(MwFileSystem::previousDir) + MwString(MwFileSystem::dirSplitter);
            else
                break;
        }
        while (true);
    }

    result += path.Remove(0, delimiter + 1);

    return MwString(result);
}

MwString MwFileSystem::NormalizePath(MwString &path)
{
	MwStrings pathSegments;
	pathSegments.SplitString(path, MwFileSystem::dirSplitter);

	int *normalizedSegments = pathSegments.count > 0 ? new int[pathSegments.count] : 0;
	int numNormalizedSegments = 0;

	for (int segmentIndex = 0; segmentIndex < pathSegments.count; segmentIndex++)
	{
		if (pathSegments[segmentIndex].Equals(MwFileSystem::currentDir))
		{
		}

		else if (pathSegments[segmentIndex].Equals(MwFileSystem::previousDir))
		{
			if (numNormalizedSegments > 0)
				numNormalizedSegments--;
		}

		else
		{
			normalizedSegments[numNormalizedSegments] = segmentIndex;
			numNormalizedSegments++;
		}
	}


	MwString result;

	// Optimize, so that the string's length is not changed for every segment
	int resultLength = MwMath::Max(numNormalizedSegments - 1, 0);
	for (int segmentIndex = 0; segmentIndex < numNormalizedSegments; segmentIndex++)
		resultLength += pathSegments[normalizedSegments[segmentIndex]].length;

	result.EnsureCapacity(resultLength);

	for (int segmentIndex = 0; segmentIndex < numNormalizedSegments; segmentIndex++)
	{
		result += pathSegments[normalizedSegments[segmentIndex]];
		if (segmentIndex != numNormalizedSegments - 1)
			result += MwFileSystem::dirSplitter;
	}

	if (normalizedSegments != 0)
		delete[] normalizedSegments;

	return MwString(result);
}

MwString MwFileSystem::GetFileName(MwString &path)
{
	int index = path.LastIndexOf(MwFileSystem::dirSplitter) + 1;

	return MwString(path.SubString(index, path.length - index));
}

MwString MwFileSystem::GetFileExtension(MwString &path)
{
	int index = path.LastIndexOf(MwFileSystem::extensionSplitter);
	if ((index == -1) || (index < path.LastIndexOf(MwFileSystem::dirSplitter)))
		return MwString();
	
	index++;

	return MwString(path.SubString(index, path.length - index));
}

MwString MwFileSystem::GetFileNameWithoutExtension(MwString &path)
{
	int start = path.LastIndexOf(MwFileSystem::dirSplitter) + 1;

	int end = path.LastIndexOf(MwFileSystem::extensionSplitter);
	if ((end == -1) || (end < start))
		end = path.length;
	
	return MwString(path.SubString(start, end - start));
}

MwString MwFileSystem::CreateFileNameWithExtension(MwString &fileName, MwString &extension)
{
	int splitterPos = fileName.LastIndexOf(MwFileSystem::extensionSplitter);
	if (splitterPos != 0)
	{
		if (splitterPos > fileName.LastIndexOf(MwFileSystem::dirSplitter))
		{
			return MwString(fileName.SubString(0, splitterPos) + "." + extension);
		}
	}

	return MwString(fileName + "." + extension);
}

MwString MwFileSystem::GetFileDir(MwString &path)
{
	return MwString(path.SubString(0, path.LastIndexOf(MwFileSystem::dirSplitter)));
}

MwString MwFileSystem::MergePaths(MwString &path1, MwString &path2)
{
	return MwString(MwFileSystem::NormalizePath(path1 + MwFileSystem::dirSplitter + path2));
}
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

#include "MwPhysicalFileSystem.h"

#include "..\..\Tools\Streams\MwFileStream.h"

#ifndef UNICODE
#	define UNICODE
#endif

#include <windows.h>

MwPhysicalFileSystem::MwPhysicalFileSystem(void)
	: MwFileSystem()
{
}


MwPhysicalFileSystem::~MwPhysicalFileSystem(void)
{
}

MwBaseStream *MwPhysicalFileSystem::OpenFile(MwString path)
{
	if (!this->FileExists(path.contents))
		return 0;

	return new MwFileStream(path.contents, FileStreamAccessMode_Read);
}

MwBaseStream *MwPhysicalFileSystem::CreateNewFile(MwString path)
{
	return new MwFileStream(path.contents, FileStreamAccessMode_Write);
}

bool MwPhysicalFileSystem::GetFileInfo(MwString path, MwFileInfo &result)
{
	WIN32_FIND_DATA findData;
	HANDLE findHandle = FindFirstFile(path.contents, &findData);
	if (findHandle == INVALID_HANDLE_VALUE)
		return false;

	FindClose(findHandle);

	result.fileName = path;
	result.isDirectory = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	result.size = findData.nFileSizeHigh;
	result.size = (result.size  << 32) | findData.nFileSizeLow;

	return true;
}

bool MwPhysicalFileSystem::GetDirectoryContents(MwString path, MwList<MwFileInfo> &result)
{
	if (path[path.length - 1] != L'\\')
		path += "\\";
   
	path += "*";

	WIN32_FIND_DATA findData;

	HANDLE findHandle = FindFirstFile(path.contents, &findData);

	MwString thisDir("."), previousDir("..");
	if (findHandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(thisDir.Equals(findData.cFileName) || previousDir.Equals(findData.cFileName)))
			{
				MwFileInfo fileInfo;
				fileInfo.fileName = findData.cFileName;
				fileInfo.isDirectory = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
				fileInfo.size = findData.nFileSizeHigh;
				fileInfo.size = (fileInfo.size << 32) | findData.nFileSizeLow;

				result.Add(fileInfo);
			}
		}
		while (FindNextFile(findHandle, &findData) != 0);
	}
	else
		return false;

	if (GetLastError() != ERROR_NO_MORE_FILES) 
	{
		FindClose(findHandle);
		return false;
	}

	FindClose(findHandle);

	return true;
}

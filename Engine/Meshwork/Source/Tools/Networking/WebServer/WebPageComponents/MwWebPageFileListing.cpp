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

#include "MwWebPageFileListing.h"

#include "..\..\..\OS\MwOSUtils.h"
#include "..\..\..\MwStrings.h"
#include "..\MwWebServer.h"

MwWebPageFileListing::MwWebPageFileListing(void)
	: MwWebPageComponent()
{
}


MwWebPageFileListing::~MwWebPageFileListing(void)
{
}

MwString MwWebPageFileListing::Output(MwWebRequest *request)
{
	MwString result = "<table class=\"fileListing\">";

	const char*lineStyleNames[2] =  { "fileListing_line_even", "fileListing_line_odd" };

	MwList<MwFileInfo> filesInfo;
	request->server->fileSystem->GetDirectoryContents(request->server->rootPath + "\\" + request->originalPath, filesInfo);

	int lineCounter = 0;
	for (int i = 0; i < filesInfo.count; i++)
		if (filesInfo[i].isDirectory)
			result += MwString("<tr class=\"") + lineStyleNames[lineCounter++ % 2] + "\"><td class=\"fileListing_name\"><a href=\"" + filesInfo[i].fileName + "/\">" + filesInfo[i].fileName + "</a></td><td class=\"fileListing_size\">DIR</td></tr>";

		for (int i = 0; i < filesInfo.count; i++)
		if (!filesInfo[i].isDirectory)
			result += MwString("<tr class=\"") + lineStyleNames[lineCounter++ % 2 % 2] + "\"><td class=\"fileListing_name\"><a href=\"" + filesInfo[i].fileName + "\">" + filesInfo[i].fileName + "</a></td><td class=\"fileListing_size\">" + request->server->fileSystem->GetSymbolicSize(filesInfo[i].size) + "</td></tr>";
	
	result += "</table>";

	return MwString(result);
}

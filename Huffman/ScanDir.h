#pragma once

#include <Windows.h>

/*
windows.h is a Windows-specific header file for the C and C++ programming 
languages which contains declarations for all of the functions in the Windows API, 
all the common macros used by Windows programmers, and all the data types used by the various
functions and subsystems. It defines a very large number of Windows specific functions that can 
be used in C. The Win32 API can be added to a C programming project by including the <windows.h>
header file and linking to the appropriate libraries. To use functions in xxxx.dll,
the program must be linked to xxxx.lib (or libxxxx.dll.a in MinGW).
Some headers are not associated with a .dll
but with a static library (e.g. scrnsave.h needs scrnsave.lib).
*/
#include "Implementations.h"

struct FileType
{
	// Path to reach the file
	// Example C:\Program files\games\file.txt
	std::wstring path;

	bool isDirectory;
	size_t nestedFilesCnt;
};

/**
* I use the Windows API to get a vector of the specified files for archiving
* with help from docs.microsoft.com/en-us/windows/win32/api/
*/
// The idea is to provide a given directory and a vector of strings which is actually a list of file names 
// that need to be archived.
// This function traverses the given directory 
// and if it encounters the name of a file that is in the provided list,
// it converts it to a FileType object, assigns it a path, and then adds it to an auxiliary vector of type FileType.
// In this way, I gather all the files from the list into another list which is then used in the zip function
// to encode and archive them using the algorithm.
std::string WStringToString(const std::wstring& s)
{
	std::string temp(s.length(), ' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}
bool listFiles(std::wstring path, std::wstring mask, Vector<FileType>& items, Vector<std::string>& item)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	/*
	Contains information about the
	file that is found by the FindFirstFile, FindFirstFileEx, or FindNextFile function
	*/
	std::wstring spec;

	Stack<std::wstring> directories;
	/*
	Stack is implemented in Implementations.h
	*/
	directories.push(path);

	while (!directories.isEmpty())
	{
		size_t nestedCnt = 0;
		do
		{
			path = directories.top();
			spec = path + L"\\" + mask;

			directories.pop();

			hFind = FindFirstFile(spec.c_str(), &ffd);

			/*
			FindFirstFile:
			Searches a directory for a file or
			subdirectory with a name that matches a 
			specific name (or partial name if wildcards are used).	
			If the function fails or fails to locate files from the search string in 
			the lpFileName parameter, the return value is 
			INVALID_HANDLE_VALUE(дефинирано по-горе във функцията) and the 
			contents of lpFindFileData are 
			indeterminate. To get extended error information, call the GetLastError function
			*/
		} while (hFind == INVALID_HANDLE_VALUE && !directories.isEmpty()); //skipping the files without permission


		Vector<FileType> helpVector;

		do
		{
			if (wcscmp(ffd.cFileName, L".") != 0 && wcscmp(ffd.cFileName, L".."))
			{
				if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					directories.push(path + L"\\" + ffd.cFileName);
				}
				else
				{
					std::wstring ws(ffd.cFileName);
					// Convert the file name 

					// When encountering a name from the provided list
					// Convert it to FileType and add it to the auxiliary vector
					for (int i = 0; i < item.getSize(); i++)
					{
						std::string s1 = item[i];

						std::string s2 = WStringToString(ws);
						if (s1.compare(s2) == 0)
						{
							FileType file;
							file.isDirectory = false;
							file.path = path + L"\\" + ffd.cFileName;
							helpVector.push_back(file);
						}
					}
					nestedCnt++;
				}
			}
			} while (FindNextFile(hFind, &ffd) != 0);
		
			FileType dir;
			dir.isDirectory = true;
			dir.path = path;
			dir.nestedFilesCnt = nestedCnt;
			items.push_back(dir);

			for (size_t i = 0; i < helpVector.getSize(); i++)
			{
				items.push_back(helpVector[i]);
			}

			if (GetLastError() != ERROR_NO_MORE_FILES)
			{
				std::cout << GetLastError() << hFind;
				FindClose(hFind);
				return false;
			}

			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
		/*
		If the function succeeds, the return value is a 
		search handle used in a subsequent call to FindNextFile
		or FindClose, 
		*/

	}
	return true;
}

// The first parameter is the directory
// The second parameter is the list of files that should not be included
Vector<FileType> getFiles(String toPack,Vector<std::string> item)
{
	Vector<FileType> files;
	wchar_t arr[1024];
	size_t retValue = 0;

	mbstowcs_s(&retValue, arr, 1024, toPack.c_str(), toPack.getLen());
	/*
	Converts a sequence of multibyte characters to a corresponding sequence of wide characters.
	The mbstowcs_s function converts a string of multibyte characters pointed to by mbstr into wide characters stored in the buffer
	pointed to by wcstr. The conversion will continue for each character until one of these conditions is met:
	-A multibyte null character is encountered
	-An invalid multibyte character is encountered
	-The number of wide characters stored in the wcstr buffer equals count.
	*/
	listFiles(arr, L"*", files,item);

	return files;
}


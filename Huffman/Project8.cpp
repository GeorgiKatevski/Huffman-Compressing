/*                                      *
* /Georgi Katevski                      *
* * * * * * * * * * * * * * * * * * * * *
* Topic: Huffman Compression          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Requirements:                                                              *
* Write a program that compresses multiple files in a directory            *
* into a single file using the Huffman algorithm. The following            *
* functionalities must be supported:                                        *
* - Creating an archive from a given list of files (zip)                   *
* - Extracting one or all files from the archive (unzip)                   *
* - Displaying a list of compressed files with information about           *
*   the level of compression (info)                                         *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/


//#include <string>
//#include <vector>
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <vector>
#include "Archiver.h"
#include <fstream>
using namespace std;




int main(int argc, char* argv[])
{
	vector <string> items;
	for (int i = 2; i < argc; i++)
	{
		items.push_back(argv[i]);
	}

	Archiver arch;
	arch.startProgram(argc, argv);

	return 0;
}


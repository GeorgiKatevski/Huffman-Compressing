#include "Command.h"
//#include "Implementations.h"

Command::Command() : huffman(nullptr)
{
}

Command* Command::create(HuffmanCoding* receiver, char**& argv, int& i, int size)
{
	// First argument - command - can be info, zip, unzip
	String command = *argv;
	if (command == "info")
	{
		argv++;
		i++;
		return new Info(receiver, *argv);
	}
	else if (command == "zip")
	{
		argv++;
		i++;
		// arg1 - given directory
		char* arg1 = *argv;
		argv++;
		i++;
		if (i >= size)
			return nullptr;
		// arg2 - archive name
		char* arg2 = *argv;
		// List of files to be archived
		Vector<std::string> item;
		while (i < size - 1)
		{
			argv++;
			item.push_back(*argv);
			i++;
		}
		return new Zip(receiver, arg1, arg2, item);
	}
	// Command for unzipping all files
	else if (command == "unzip")
	{
		argv++;
		i++;
		char* arg1 = *argv;
		argv++;
		i++;
		if (i >= size)
			return nullptr;
		char* arg2 = *argv;
		// Location of the archive and the name of the file to be extracted
		return new Unzip(receiver, arg1, arg2);
	}
	// If it is an invalid command, return nullptr
	else
	{
		return nullptr;
	}
}

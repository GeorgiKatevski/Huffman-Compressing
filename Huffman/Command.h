#pragma once
#include "HuffmanAlg.h"
#include "Implementations.h"

// Here, the provided commands are taken and executed
// zip/unzip/info
// Object-oriented programming principles such as inheritance, polymorphism, abstraction, and encapsulation are used
// The command is inherited from the base command class and from the specific command that is given
class Command
{
public:
	static Command* create(HuffmanCoding* receiver, char**& argv, int& i, int size);

	Command();
	Command(HuffmanCoding* huffman) : huffman(huffman) {}
	virtual void execute() = 0;

protected:
	HuffmanCoding* huffman;
};

// Command for info
// To show the files in a given archived file
// /info/ /location of the file/ /name of the file/
class Info : public Command
{
public:
	Info(HuffmanCoding* huffman, String toList)
		: Command(huffman)
		, toList(toList) { }

	void execute() { huffman->info(toList); }

private:
	String toList;
};

// Decompressing all files
// /unzip/ /location of the archive/ /name of the archive/
/* Commands are provided by the program's command center */
class Unzip : public Command
{
public:
	Unzip(HuffmanCoding* huffman, String toUnpack, String toCreate)
		: Command(huffman)
		, toUnpack(toUnpack)
		, toCreate(toCreate) {}

	void execute() { huffman->unzip(toUnpack, toCreate); }

private:
	String toUnpack;
	String toCreate;
};

// Archiving a list of files
// Command format:
/*
/zip/  /directory where the files are located/ /name of the created archive/ /file1/ /file2/ /file.../  etc.
Commands are executed by the command center with the first argument being /zip/
The second argument is the /directory where the files are located/
The third argument is the /name of the archive/
The following arguments create a list of files to be archived
*/
class Zip : public Command
{
public:
	Zip(HuffmanCoding* huffman, String toPack, String toCreate, Vector<std::string> item)
		: Command(huffman)
		, toPack(toPack)
		, toCreate(toCreate)
		, item(item)
	{}

	void execute() { huffman->zip(toPack, toCreate, item); }

private:
	// Directory where the files are located
	String toPack;
	// Name of the archive
	String toCreate;
	// List of files
	Vector<std::string> item;
};

#pragma once
//#include "Implementations.h"
#include "HuffmanAlg.h"
#include "Command.h"

class Archiver
{
public:
	Archiver();
	Archiver(const Archiver& rhs);
	Archiver& operator=(const Archiver& rhs);
	~Archiver();

	void startProgram(int argc, char* argv[]);

private:
	void order(Command* command) { command->execute(); }

private:
	HuffmanCoding* huffman;
	Vector<Command*> log;
};
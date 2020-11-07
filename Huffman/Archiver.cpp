#include "Archiver.h"

Archiver::Archiver() : log()
{
	huffman = new HuffmanCoding;
}

Archiver::Archiver(const Archiver& rhs) : log(rhs.log)
{
	huffman = new HuffmanCoding(*rhs.huffman);
}

Archiver& Archiver::operator = (const Archiver& rhs)
{
	if (this == &rhs)
		return *this;

	huffman = new HuffmanCoding(*rhs.huffman);
	log = rhs.log;

	return *this;
}

Archiver::~Archiver()
{
	for (size_t i = 0; i < log.getSize(); i++)
	{
		delete log[i];
	}

	delete huffman;
}

void Archiver::startProgram(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		argv++;
		Command* command = Command::create(this->huffman, argv, i, argc);

		if (command == nullptr)
			break;

		order(command);
		log.push_back(command);
	}
}
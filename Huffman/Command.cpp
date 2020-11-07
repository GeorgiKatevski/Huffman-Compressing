#include "Command.h"
//#include "Implementations.h"

Command::Command() : huffman(nullptr)
{
}

Command* Command::create(HuffmanCoding* receiver, char**& argv, int& i, int size)
{
	//първи аргумент-command - може да бъде info,zip,unzip
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
		//arg1 -дадената директория
		char* arg1 = *argv;
		argv++;
		i++;
		if (i >= size)
			return nullptr;
		//arg - име на архива
		char* arg2 = *argv;
		//списъка от файлове които трябва да се архивират
		Vector<std::string> item;
		while (i < size-1)
		{
			argv++;
			
			item.push_back(*argv);
			i++;
		}
return new Zip(receiver, arg1, arg2,item);
	}
	//команда за разархивиране на всички файлове
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
		//място на файла и име на файла които трябва да се разархивира
		return new Unzip(receiver, arg1, arg2);
	}
	//ако е невалидна команда се върни в майна
	else
	{
		return nullptr;
	}
}
#pragma once
#include "HuffmanAlg.h"
#include "Implementations.h"


//тук се взимат и изпълняват подадените команди
//zip/unzip/info
//за командите са използвани някои добри ООП-принцип -наследяване,полиморфизъм,абстракция,енкапсулация
//от базиса на командата се наследява и от тази команда която е подадена
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
//команда за инфо 
//за да покаже файловете в даден архивиран файл
// /info/ /място където се намира файла/ /име на файл/
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


//декомпресиране на всички файлове 
// /unzip/ /място където се намира архива/ /име на архива/
/* командите се подават от командния център на програмата*/
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

//архивиране на списък от файлове
//начин на подаване:
/*
/zip/  /директория в която се намират файловете/ /име на създадения архив/ /файл1/ /файл2/ /файл.../  etc.
командите се изпълняват от командния център като първия аргумент е /zip/ 
вторият аргумент е /директория,където се намират файловете/ 
третият аргумент /име на архива/ 
следващите аргументи създават списък от файлове който трябва да се архивира
*/
class Zip : public Command
{
public:
	Zip(HuffmanCoding* huffman, String toPack,String toCreate,Vector<std::string> item)
		: Command(huffman)
		, toPack(toPack)
		, toCreate(toCreate)
		,item(item)
	{}

	void execute() { huffman->zip(toPack, toCreate,item); }

private:
	//директория в която се намират файловете
	String toPack;
	//име на архива
	String toCreate;
	//списъка от файлове
	Vector<std::string> item;
};

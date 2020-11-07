/*                                      *
* /Георги Катевски/фн:71899/група:3/    *
* * * * * * * * * * * * * * * * * * * * *
*Тема 5:Хъфман-компресиране             *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Условие:                                                                *
*Напишете програма, която компресира множество файлове в една директория  *
*в един файл, използвайки алгоритъма на Хъфман. Трябва да се поддържат    * 
*следните функционалности:                                                *
*-създаване на архив по подаден списък от файлове (zip)                   *
*-разархивиране на един или всички файлове от архива (unzip)              *
*-извеждане на списък на компресираните файлове с информация за           *
*нивото на компресия (info)                                               *
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

	Archiver* arch = new Archiver;

	arch->startProgram(argc, argv);
	
	delete arch;
	
	

}


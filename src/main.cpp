/**=============================================
 * CS3210
 * LAB 1: STL FILE READER
 * @file main.cpp
 * @date March 7 2018
 * @author Dennis Droese
 =============================================*/

#include <iostream>
#include <fstream>
#include <string>
#include"STLfile.h"

using namespace std;

int main(int argc, char**argv){

	if(argc < 2){
		cout << "Usage: cs3210-lab1_droesedj <filename>\n";
		return 0;
	}

	solid* myOBJ = parseSTLFile(argv[1]);

	if(myOBJ != nullptr){
		printSolidData(myOBJ);
	}

	delete myOBJ;

	return 0;
}

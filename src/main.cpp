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

//	int numFacets = 0;
//	int numVerts = 0;

//	bool facetRead = false;
/*
	string line;
	ifstream myfile ("word.stl");
	if(myfile.is_open()){
		while(getline(myfile,line)){
			cout << line << '\n';
		}
		myfile.close();
	} else {
		cout << "Shit's fucked yo.";
	}
*/
	parseSTLFile("word.stl");

/*	string solidstr ("solid");

	string facetstr ("facet");

	string vertexstr ("vertex");

	//ifstream STL (argv[1]);
	ifstream file ("word.stl");

	if(file.is_open()){
		while(!file.eof()){
			string str;

			getline(file, str);

			istringstream ss(str);


		}
	}
*/

/*	if(STL.is_open()){
		while(getline(STL,line)){
			istringstream wordBuf(line);
			string word;
			getline(wordBuf, word, ' ');

			if(word.compare("solid") == 0){
				getline(wordBuf, word, ' ');
				std::cout << "File: " << word;
			} else if(word.compare("facet normal") == 0){
				facetRead = true;
				numFacets += 1;
				std::cout << "Facet:\n";
				while(facetRead){
					getline(STL, line);
					//wordBuf = line;
					getline(wordBuf, word, ' ');

					if(word.compare("vertex")){
						std::cout << line;
						numVerts += 1;
					} else if(word.compare("endfacet")){
						facetRead = false;
					}
				}
			} else if(word.compare("endsolid")){
				break;
			}
		}
	}
	*/
}

/**=============================================
 * CS3210
 * LAB 1: STL FILE READER
 * @file STLfile.h
 * @date March 7 2018
 * @author Dennis Droese
 *
 * Header for an object representing the contents of an STL file.
 *
 =============================================*/

#ifndef SRC_STLFILE_H_
#define SRC_STLFILE_H_

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;


class Vertex;
class Facet;
class Solid;

extern Solid* parseSTLFile(string file);
extern void printSolidData(Solid* obj);

Solid* parseSolid(string data);
Facet* parseFacet(string data);
Vertex* parseVertex(string data);

#endif /* SRC_STLFILE_H_ */

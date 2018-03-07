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
using namespace std;


class Vertex{
	float x,y,z;
	Vertex next;
public:
	Vertex(float x_, float y_, float z_);
	float getX() {return x;}
	float getY() {return y;}
	float getZ() {return z;}
};


class Facet{
	int numVerts;
	Vertex firstVert;
	Facet next;
public:
	Facet(Vertex startVert);
	int getNumVerts() {return numVerts;}
	Vertex getVertex(int vertIndex);
	Vertex getFirstVertex() {return firstVert;}
};


class Solid{
	string name;
	int numFacets;
	Facet firstFacet;
public:
	Solid(string name_, Facet startFacet);
	string getName() {return name;}
	Facet getFacet(int facetIndex);
	Facet getFacetStart() {return firstFacet;}
};


#endif /* SRC_STLFILE_H_ */

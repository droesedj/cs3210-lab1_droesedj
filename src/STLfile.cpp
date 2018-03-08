/**=============================================
 * CS3210
 * LAB 1: STL FILE READER
 * @file STLfile.cpp
 * @date March 7 2018
 * @author Dennis Droese
 *
 * Object representing the contents of an STL file.
 *
 =============================================*/
#include<iostream>
#include<fstream>
#include<string>
#include "STLfile.h"

using namespace std;

/**
 * Vertex Class
 *
 * Represents a Vertex read in from an STL file.
 * Also knows if any vertices follow it.
 */
class Vertex {

	/// Coordinates of vertex
	float x_,y_,z_;

	/// Pointer to the next vertex.  NULL if this is the last vertex.
	void* next;

public:

	Vertex(float x, float y, float z) {
		x_ = x;
		y_ = y;
		z_ = z;
		next = NULL;
	}

	Vertex() {
		x_ = 0.0;
		y_ = 0.0;
		z_ = 0.0;
		next = NULL;
	}

	float getX() {return x_;}
	float getY() {return y_;}
	float getZ() {return z_;}

	Vertex* getNext() {return (Vertex*)(next);}

	void setX(float x) {x_ = x;}
	void setY(float y) {y_ = y;}
	void setZ(float z) {z_ = z;}

	void setNext(void* nextVert) {
		if(next == NULL){
			next = nextVert;
		}
	}
};

/**
 * Facet Class
 *
 * Represents a Facet read in from an STL file.
 * Also knows if any Facets follow it.
 */
class Facet{

	/// Vector of the facet's normal.
	float n1_, n2_, n3_;


	/// Number of vertices in the facet.
	int numVerts;

	/// First vertex in the facet.
	Vertex firstVert;

	/// Pointer to the next facet.  NULL if this is the last facet.
	void* next;

	int countVertsInChain(Vertex start){
		return 0;
	}

public:

	Facet(float n1, float n2, float n3) {
		numVerts = 0;
		n1_ = n1;
		n2_ = n2;
		n3_ = n3;
		next = NULL;
	}

	Facet() {
		n1_ = 0;
		n2_ = 0;
		n3_ = 0;
		numVerts = 0;
		next = NULL;
	}

	int getNumVerts() {return numVerts;}

	Vertex getVertex(int vertIndex);

	Vertex getFirstVertex() {return firstVert;}

	void setFirstVertex(Vertex first) {
		firstVert = first;
		numVerts = countVertsInChain(first);
	}

	Facet* getNext() {return (Facet*)(next);}

	void setNext(void* nextFacet) {
		if(next == NULL){
			next = nextFacet;
		}
	}
};


class Solid{

	/// Name of the solid.
	string name_;

	/// Number of facets in the solid.
	int numFacets;

	/// TOTAL number of vertices in the solid.
	int numTotalVerts;

	/// First facet in the solid.
	Facet firstFacet;

	/// Minima and Maxima dimensions recorded in the solid.
	float x_min, x_max, y_min, y_max, z_min, z_max;

	/// Dimensions of the object, stored as [x,y,z]
	float x_len, y_len, z_len;

public:

	Solid(){
		name_ = "";
		x_min = 0;
		x_max = 0;
		y_min = 0;
		y_max = 0;
		z_min = 0;
		z_max = 0;
		numTotalVerts = 0;
		numFacets = 0;
		x_len = 0;
		y_len = 0;
		z_len = 0;
	}
	Solid(string name){
			name_ = name;
			x_min = 0;
			x_max = 0;
			y_min = 0;
			y_max = 0;
			z_min = 0;
			z_max = 0;
			numTotalVerts = 0;
			numFacets = 0;
			x_len = 0;
			y_len = 0;
			z_len = 0;
		}

	string getName() {return name_;}
	int getTotalVerts() {return numTotalVerts;}
	int getNumFacets() {return numFacets;}
	Facet getFacet(int facetIndex);
	Facet getFacetStart() {return firstFacet;}

	void setName(string name) {name_ = name;}

	void setFacetStart(Facet start){
		firstFacet = start;
	}
};




void parseSTLFile(string file){
	Solid* output = NULL;
	Vertex* vertexHead = NULL;
	Facet* facetHead = NULL;

	void* vertIterator;
	void* faceIterator;

	int numVerts = 0;


	cout << "STARTING PARSER" << '\n';
	string line;
	ifstream STL ("word.stl");
	if(STL.is_open()){
		while(getline(STL,line)){
			int start = 0;
			while(line[start] == ' '){
				start += 1;
			}
			string word;
			stringstream(line) >> word;

			if(word.compare("solid") == 0){
				output = parseSolid(line);
				cout << "PARSING A SOLID!!!" << '\n';
			} else if(word.compare("facet") == 0){
				cout << "PARSING A FACET" << '\t' << line << '\n';
			} else if(word.compare("outer") == 0){
				cout << "PARSING A LOOP" << '\t' << line << '\n';
			} else if(word.compare("vertex") == 0){
				cout << "PARSING A VERTEX:" << '\t' << line << '\n';
				parseVertex(line);
			}else if(word.compare("endfacet") == 0){
				cout << "PARSING END OF FACET" << '\n';
			} else if(word.compare("endsolid") == 0){
				cout << "PARSING END OF SOLID!" << '\n';
			} else if(word.compare("endloop") == 0){
				cout << "PARSING END OF LOOP!" << '\n';
			} else {
				cout << "COULD NOT FIGURE OUT WHAT " << word << " IS SUPPOSED TO BE!" << '\n';
			}

		}
	}
}


Solid* parseSolid(string data){
	string name;
	string garbage;
	stringstream(data) >> garbage >> name;

	Solid* output = new Solid(name);
	return output;
}

Facet* parseFacet(string data){
	string garbage;
	float x,y,z;
	stringstream(data) >> garbage >> garbage >> x >> y >> z;

	return new Facet(x,y,z);
}

Vertex* parseVertex(string data){
	float f1;
	float f2;
	float f3;

	string word;

	stringstream(data) >> word >> f1 >> f2 >> f3;

	return new Vertex(f1, f2, f3);
}


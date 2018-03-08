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
	float* x_;
	float* y_;
	float* z_;

	/// Pointer to the next vertex.  nullptr if this is the last vertex.
	Vertex* next;

public:

	Vertex(float x, float y, float z) {
		x_ = new float(x);
		y_ = new float(y);
		z_ = new float(z);
		next = nullptr;
	}

	Vertex() {
		x_ = new float;
		y_ = new float;
		z_ = new float;
		next = nullptr;
	}

	float getX() {return *x_;}
	float getY() {return *y_;}
	float getZ() {return *z_;}

	Vertex* getNext() {return (Vertex*)(next);}

	void setX(float x) {*x_ = x;}
	void setY(float y) {*y_ = y;}
	void setZ(float z) {*z_ = z;}

	void setNext(Vertex* nextVert) {
		if(next == nullptr){
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
	float* nx_;
	float* ny_;
	float* nz_;


	/// Number of vertices in the facet.
	int* numVerts;

	/// First vertex in the facet.
	Vertex* firstVert;

	/// Pointer to the next facet.  nullptr if this is the last facet.
	Facet* next;

	int countVertsInChain(){
		int count = 0;
		Vertex* iter = firstVert;

		while(iter->getNext() != nullptr){
			count += 1;
			iter = iter->getNext();
		}

		return count + 1;
	}

public:

	Facet(float n1, float n2, float n3) {
		firstVert = nullptr;
		numVerts = new int;
		nx_ = new float(n1);
		ny_ = new float(n2);
		nz_ = new float(n3);
		next = nullptr;
	}

	Facet() {
		firstVert = nullptr;
		nx_ = nullptr;
		ny_ = nullptr;
		nz_ = nullptr;
		numVerts = new int;
		next = nullptr;
	}

	int getNumVerts() {return *numVerts;}

	Vertex* getVertex(int vertIndex);

	Vertex* getFirstVertex() {return firstVert;}

	void setFirstVertex(Vertex* first) {
		firstVert = first;
		*numVerts = countVertsInChain();
	}

	Facet* getNext() {return (Facet*)(next);}

	void setNext(Facet* nextFacet) {
		if(next == nullptr){
			next = nextFacet;
		}
	}
};


class Solid{

	/// Name of the solid.
	string* name_;

	/// Number of facets in the solid.
	int* numFacets;

	/// TOTAL number of vertices in the solid.
	int* numTotalVerts;

	/// First facet in the solid.
	Facet* firstFacet;

	/// Minimum and Maximum dimensions recorded in the solid.
	float* x_min;
	float* x_max;
	float* y_min;
	float* y_max;
	float* z_min;
	float* z_max;

	/// Dimensions of the object, stored as [x,y,z]
	float* x_len;
	float* y_len;
	float* z_len;


	void processCoords() {
		if(firstFacet != nullptr && firstFacet->getFirstVertex() != nullptr){
			Facet* facetIter = firstFacet;
			Vertex* vertexIter = facetIter->getFirstVertex();

			// init the notable dimensions to the first vert's values.
			*x_min = vertexIter->getX();
			*x_max = vertexIter->getX();
			*y_min = vertexIter->getY();
			*y_max = vertexIter->getY();
			*z_min = vertexIter->getZ();
			*z_max = vertexIter->getZ();

			while(facetIter->getNext() != nullptr){
				while(vertexIter->getNext() != nullptr){
					//Check min/max, update values, advance the vertex iterator.
					if(vertexIter->getX() < *x_min){
						*x_min = vertexIter->getX();
					} else if(vertexIter->getX() > *x_max){
						*x_max = vertexIter->getX();
					}
					if(vertexIter->getY() < *y_min){
						*y_min = vertexIter->getY();
					} else if(vertexIter->getY() > *y_max){
						*y_max = vertexIter->getY();
					}
					if(vertexIter->getZ() < *z_min){
						*z_min = vertexIter->getZ();
					} else if(vertexIter->getZ() > *z_max){
						*z_max = vertexIter->getZ();
					}
					vertexIter = vertexIter->getNext();
				}
				//advance the facet iterator
				facetIter = facetIter->getNext();
			}

			//update dimensions
			*x_len = *x_max - *x_min;
			*y_len = *y_max - *y_min;
			*z_len = *z_max - *z_min;
		}
	}

public:

	Solid(){
		firstFacet = nullptr;
		name_ = new string;
		x_min = new float;
		x_max = new float;
		y_min = new float;
		y_max = new float;
		z_min = new float;
		z_max = new float;
		numTotalVerts = new int;
		numFacets = new int;
		x_len = new float;
		y_len = new float;
		z_len = new float;
	}

	Solid(string name){
		firstFacet = nullptr;
		name_ = new string(name);
		x_min = new float;
		x_max = new float;
		y_min = new float;
		y_max = new float;
		z_min = new float;
		z_max = new float;
		numTotalVerts = new int;
		numFacets = new int;
		x_len = new float;
		y_len = new float;
		z_len = new float;
	}

	string getName() {return *name_;}
	int getTotalVerts() {return *numTotalVerts;}
	int getNumFacets() {return *numFacets;}
	Facet* getFacetStart() {return firstFacet;}

	void setName(string name) {*name_ = name;}

	void setFacetStart(Facet* start){
		firstFacet = start;
		int count = 0;
		int countFaces = 0;
		Facet* iter = start;

		while(iter->getNext() != nullptr){
			count += iter->getNumVerts();
			countFaces += 1;
			iter = iter->getNext();
		}

		*numTotalVerts = count;
		*numFacets = countFaces;

		processCoords();
	}
};


// PARSER CODE BELOW THIS LINE

Solid* parseSTLFile(string file){
	Solid* output = nullptr;
	Vertex* vertexHead = nullptr;
	Facet* facetHead = nullptr;

	Vertex* vertIterator = nullptr;
	Facet* faceIterator = nullptr;


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

			//TODO Get rid of dev console printouts once this is working...

			if(word.compare("solid") == 0){
				// Create the solid from the line
				output = parseSolid(line);
			} else if(word.compare("facet") == 0){
				if(facetHead == nullptr){
					// First facet in the solid, init the head and iterator.
					facetHead = parseFacet(line);
					faceIterator = facetHead;
				} else {
					// Facet comes after the head, advance the iterator and append the new one onto the previous.
					faceIterator->setNext(parseFacet(line));
					faceIterator = faceIterator->getNext();
				}
			} else if(word.compare("outer") == 0){
				// Start of a vertex loop.  Don't really need to do anything about it though.
			} else if(word.compare("vertex") == 0){
				if(vertexHead == nullptr){
					// Firse vertex in the loop, init the head and iterator.
					vertexHead = parseVertex(line);
					vertIterator = vertexHead;
				} else {
					// Vertex comes after the head, advance the iterator and append the new one onto the previous.
					vertIterator->setNext(parseVertex(line));
					vertIterator = vertIterator->getNext();
				}
			}else if(word.compare("endfacet") == 0){
				// End of a facet, attach to the solid, clear the head and iterator.
			} else if(word.compare("endsolid") == 0){
				// End of the solid.  Attach the facet head to the solid output.  Clear the iterators.
				faceIterator = nullptr;
				output->setFacetStart(facetHead);
				facetHead = nullptr;

				cout << "END OF SOLID: " << output->getName() << '\n';
				cout << "SOLID HAS " << output->getTotalVerts() << " total vertices." << '\n';
				cout << "SOLID HAS " << output->getNumFacets() << " total facets." << '\n';
			} else if(word.compare("endloop") == 0){
				// End of a vertex loop, attach the verts to the current facet, clear the head and iterator.
				vertIterator = nullptr;
				faceIterator->setFirstVertex(vertexHead);
				vertexHead = nullptr;
				cout << "PARSING END OF LOOP!" << '\n';
			} else {
				// Garbage or invalid keyword.  Yell into the console.
				cout << "COULD NOT FIGURE OUT WHAT " << word << " IS SUPPOSED TO BE!" << '\n';
			}
		}
	}
	return output;
}


Solid* parseSolid(string data){
	string name;
	string garbage;
	stringstream(data) >> garbage >> name;

	return new Solid(name);
}

Facet* parseFacet(string data){
	string garbage;
	float x,y,z;
	stringstream(data) >> garbage >> garbage >> x >> y >> z;

	return new Facet(x,y,z);
}

Vertex* parseVertex(string data){
	float f1, f2, f3;
	string word;

	stringstream(data) >> word >> f1 >> f2 >> f3;

	return new Vertex(f1, f2, f3);
}

void printSolidData(Solid* obj){
	cout << "RESULTS FOR SOLID: " << obj->getName() << '\n';
	cout << "==========================" << '\n';
	cout << "TOTAL NUMBER OF FACETS:\t" << obj->getNumFacets() << '\n';
	cout << "TOTAL NUMBER OF VERTICES:\t" << obj->getTotalVerts() << '\n';
	cout << "==========================" << '\n';
	cout << "MAXIMUM X-COORDINATE: ";
}

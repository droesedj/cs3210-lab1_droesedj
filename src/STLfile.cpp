/**=============================================
 * CS3210
 * LAB 1: STL FILE READER
 * @file STLfile.cpp
 * @date March 7 2018
 * @author Dennis Droese
 *
 * Contains utilities for parsing and viewing STL model data.
 *
 =============================================*/
#include<iostream>
#include<fstream>
#include<string>
#include "STLfile.h"

using namespace std;


/**
 * Parses a given STL file into a Solid.
 * @param file .STL file to be loaded.
 * @return Solid parsed from the file.
 *
 * Assumes that the file has proper formatting.
 * This WILL hang if the file does not have proper formatting.
 */
Solid* parseSTLFile(string file){
	Solid* output = nullptr;
	Vertex* vertexHead = nullptr;
	Facet* facetHead = nullptr;

	Vertex* vertIterator = nullptr;
	Facet* faceIterator = nullptr;

	string line;
	ifstream STL (file);
	if(STL.is_open()){
		while(getline(STL,line)){
			int start = 0;
			while(line[start] == ' '){
				start += 1;
			}
			string word;
			stringstream(line) >> word;

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
				output->setStartFacet(facetHead);
				facetHead = nullptr;
			} else if(word.compare("endloop") == 0){
				// End of a vertex loop, attach the verts to the current facet, clear the head and iterator.
				vertIterator = nullptr;
				faceIterator->setFirstVertex(vertexHead);
				vertexHead = nullptr;
			} else {
				// Garbage or invalid keyword.  Yell into the console.
				cout << "COULD NOT FIGURE OUT WHAT " << word << " IS SUPPOSED TO BE!" << '\n';
			}
		}
		STL.close();
	} else {
		cout << "Error loading file: " << file << '\n';
		return nullptr;
	}
	return output;
}

/**
 * Parses a solid from a given line of input data
 * Expects data to be in the following format:
 * "solid <string name>"
 * @param data Line of text to be read in.
 * @return Pointer to a newly-created Solid.
 */
Solid* parseSolid(string data){
	string name;
	string garbage;
	stringstream(data) >> garbage >> name;

	return new Solid(name);
}

/**
 * Parses a facet from a given line of input data.
 * Expects data to be in the following format:
 * "facet normal <float x> <float y> <float z>"
 * @param data Line of text to be read in.
 * @return Pointer to a newly-created Facet.
 */
Facet* parseFacet(string data){
	string garbage;
	double x,y,z;
	stringstream(data) >> garbage >> garbage >> x >> y >> z;

	return new Facet(x,y,z);
}

/**
 * Parses a vertex from a given line of input data.
 * Expects data to be in the following format:
 * "vertex <float x> <float y> <float z>"
 * @param data
 * @return Pointer to the newly-created Vertex.
 */
Vertex* parseVertex(string data){
	double f1, f2, f3;
	string garbage;

	stringstream(data) >> garbage >> f1 >> f2 >> f3;

	return new Vertex(f1, f2, f3);
}

/**
 * A really lazy way of retrieving a whole bunch of data from a Solid.
 * @param obj Pointer to a solid object to get data from.
 */
void printSolidData(Solid* obj){
	// Facet/vertex output:

	Facet* facetIter;
	Vertex* vertexIter;
	int facetNum = 1;

	if(obj->getFacetStart() != nullptr && obj->getFacetStart()->getFirstVertex() != nullptr){

		facetIter = obj->getFacetStart();
		vertexIter = facetIter->getFirstVertex();

		while(facetIter->getNext() != nullptr){
			cout << "Facet #" << facetNum << '\n';
			while(vertexIter->getNext() != nullptr){
				cout << "\tVertex: " << vertexIter->getX() << " " << vertexIter->getY() << " " << vertexIter->getZ() << '\n';
				vertexIter = vertexIter->getNext();
			}
			cout << "\tVertex: " << vertexIter->getX() << " " << vertexIter->getY() << " " << vertexIter->getZ() << '\n';
			facetNum++;
			facetIter = facetIter->getNext();
			vertexIter = facetIter->getFirstVertex();
		}
		cout << "Facet #" << facetNum << '\n';
		while(vertexIter->getNext() != nullptr){
			cout << "\tVertex: " << vertexIter->getX() << " " << vertexIter->getY() << " " << vertexIter->getZ() << '\n';
			vertexIter = vertexIter->getNext();
		}
		cout << "\tVertex: " << vertexIter->getX() << " " << vertexIter->getY() << " " << vertexIter->getZ() << '\n';
	}


	// Result output
	cout << "RESULTS FOR SOLID: " << obj->getName() << '\n';
	cout << "==============================" << '\n';
	cout << "TOTAL NUMBER OF FACETS:   " << obj->getNumFacets() << '\n';
	cout << "TOTAL NUMBER OF VERTICES: " << obj->getTotalVerts() << '\n';
	cout << "==============================" << '\n';
	cout << "MAXIMUM X-COORDINATE: " << obj->getXMax() << '\n';
	cout << "MINIMUM X-COORDINATE: " << obj->getXMin() << '\n';
	cout << "MAXIMUM Y-COORDINATE: " << obj->getYMax() << '\n';
	cout << "MINIMUM Y-COORDINATE: " << obj->getYMin() << '\n';
	cout << "MAXIMUM Z-COORDINATE: " << obj->getZMax() << '\n';
	cout << "MINIMUM Z-COORDINATE: " << obj->getZMin() << '\n';
	cout << "==============================" << '\n';
	cout << "SOLID DIMENSIONS (XYZ): " << obj->getXLength() << " x " << obj->getYLength() << " x " << obj->getZLength() << '\n';
	cout << "==============================" << '\n';
}

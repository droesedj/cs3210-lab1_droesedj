/**=============================================
 * CS3210
 * LAB 1: STL FILE READER
 * @file STLfile.h
 * @date March 7 2018
 * @author Dennis Droese
 *
 * Header for several classes representing the contents of an STL file.
 *
 =============================================*/

#ifndef SRC_STLFILE_H_
#define SRC_STLFILE_H_

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;


/**
 * Vertex Class
 *
 * Represents a Vertex read in from an STL file.
 * Also knows if any vertices follow it.
 */
class vertex {

	/// X-coordinate of vertex
	double* x_;

	/// Y-coordinate of vertex
	double* y_;

	/// Z-coordinate of vertex
	double* z_;

	/// Pointer to the next vertex.  nullptr if this is the last vertex in the chain.
	vertex* next;

public:
	vertex(double x, double y, double z);
	vertex();
	double getX();
	double getY();
	double getZ();
	vertex* getNext();
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void setNext(vertex* nextVert);

	/// Destructor.
	~vertex();
};

/**
 * Facet Class
 *
 * Represents a Facet read in from an STL file.
 * Also knows if any Facets follow it.
 */
class facet{

	/// x-direction of the facet's normal.
	double* nx_;

	/// y-direction of the facet's normal.
	double* ny_;

	/// z-direction of the facet's normal.
	double* nz_;

	/// Number of vertices in the facet.
	int* numVerts;

	/// First vertex in the facet.
	vertex* firstVert;

	/// Pointer to the next facet.  nullptr if this is the last facet in the chain.
	facet* next;

	/**
	 * Counts the number of vertices within this facet.
	 * @return Number of vertices.
	 */
	int countVertsInChain();

public:
	facet(double nx, double ny, double nz);
	facet();
	int getNumVerts();
	vertex* getFirstVertex();

	/**
	 * Replaces the current vertex chain with a specified one.
	 * @param first New vertex chain.
	 */
	void setFirstVertex(vertex* first);

	/**
	 * Gets a pointer to the next facet in the chain.
	 * @return A pointer to the next facet in the chain.
	 */
	facet* getNext();

	/**
	 * Sets the pointer of the next facet in the chain.
	 * @param nextFacet Facet to be added to the chain.
	 * DESTRUCTIVE! DO NOT REPLACE EXISTING VALUES!
	 */
	void setNext(facet* nextFacet);

	/// Destructor.
	~facet();
};


/**
 * Solid Class
 *
 * Represents a solid object described by an STL file.
 */
class solid{

	/// Name of the solid.
	string* name_;

	/// Number of facets in the solid.
	int* numFacets;

	/// TOTAL number of vertices in the solid.
	int* numTotalVerts;

	/// First facet in the solid.
	facet* firstFacet;

	/// Minimum recorded x-coordinate
	double* x_min;

	/// Maximum recorded x-coordinate
	double* x_max;

	/// Minimum recorded y-coordinate
	double* y_min;

	/// Maximum recorded y-coordinate
	double* y_max;

	/// Minimum recorded z-coordinate
	double* z_min;
	/// Maximum recorded z-coordinate
	double* z_max;

	/// Length of the solid's x-axis
	double* x_len;

	/// Length of the solid's y-axis
	double* y_len;

	/// Length of the solid's z-axis
	double* z_len;

	/**
	 * This method refreshes the min/max coordinate values and lengths of the solid.
	 */
	void processCoords();

public:
	solid();
	solid(string name);
	string getName();
	int getTotalVerts();
	int getNumFacets();
	facet* getFacetStart();
	double getXMin();
	double getXMax();
	double getYMin();
	double getYMax();
	double getZMin();
	double getZMax();
	double getXLength();
	double getYLength();
	double getZLength();
	void setName(string name);

	/**
	 * Sets the start of the facet chain.
	 * @param start First facet in the chain.
	 * DESTRUCTIVE!!! DO NOT REPLACE EXISTING VALUES!!!
	 */
	void setStartFacet(facet* start);

	/// Destructor
	~solid();
};

/**
 * Parses a given STL file into a Solid.
 * @param file .STL file to be loaded.
 * @return Solid parsed from the file.
 *
 * Assumes that the file has proper formatting.
 * This WILL hang if the file does not have proper formatting.
 */
extern solid* parseSTLFile(string file);

/**
 * A really lazy way of retrieving a whole bunch of data from a Solid.
 * @param obj Pointer to a solid object to get data from.
 */
extern void printSolidData(solid* obj);

/**
 * Parses a solid from a given line of input data
 * Expects data to be in the following format:
 * "solid <string name>"
 * @param data Line of text to be read in.
 * @return Pointer to a newly-created Solid.
 */
solid* parseSolid(string data);

/**
 * Parses a facet from a given line of input data.
 * Expects data to be in the following format:
 * "facet normal <float x> <float y> <float z>"
 * @param data Line of text to be read in.
 * @return Pointer to a newly-created Facet.
 */
facet* parseFacet(string data);

/**
 * Parses a vertex from a given line of input data.
 * Expects data to be in the following format:
 * "vertex <float x> <float y> <float z>"
 * @param data
 * @return Pointer to the newly-created Vertex.
 */
vertex* parseVertex(string data);

#endif /* SRC_STLFILE_H_ */

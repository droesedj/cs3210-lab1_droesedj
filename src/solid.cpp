/**=============================================
 * CS3210
 * LAB 1: STL FILE READER
 * @file facet.cpp
 * @date March 8 2018
 * @author Dennis Droese
 *
 * Solid Class
 *
 =============================================*/

#include "STLfile.h"

using namespace std;

	/**
	 * This method refreshes the min/max coordinate values and lengths of the solid.
	 */
	void solid::processCoords() {
		if(firstFacet != nullptr && firstFacet->getFirstVertex() != nullptr){
			facet* facetIter;

			facetIter = firstFacet;

			vertex* vertexIter = facetIter->getFirstVertex();

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
				vertexIter = facetIter->getFirstVertex();
			}
			//update dimensions
			*x_len = *x_max - *x_min;
			*y_len = *y_max - *y_min;
			*z_len = *z_max - *z_min;
		}
	}

	solid::solid(){
		firstFacet = nullptr;
		name_ = new string;
		x_min = new double;
		x_max = new double;
		y_min = new double;
		y_max = new double;
		z_min = new double;
		z_max = new double;
		numTotalVerts = new int;
		numFacets = new int;
		x_len = new double;
		y_len = new double;
		z_len = new double;
	}

	solid::solid(string name){
		firstFacet = nullptr;
		name_ = new string(name);
		x_min = new double;
		x_max = new double;
		y_min = new double;
		y_max = new double;
		z_min = new double;
		z_max = new double;
		numTotalVerts = new int;
		numFacets = new int;
		x_len = new double;
		y_len = new double;
		z_len = new double;
	}

	string solid::getName() {return *name_;}
	int solid::getTotalVerts() {return *numTotalVerts;}
	int solid::getNumFacets() {return *numFacets;}
	facet* solid::getFacetStart() {return firstFacet;}
	double solid::getXMin() {return *x_min;}
	double solid::getXMax() {return *x_max;}
	double solid::getYMin() {return *y_min;}
	double solid::getYMax() {return *y_max;}
	double solid::getZMin() {return *z_min;}
	double solid::getZMax() {return *z_max;}
	double solid::getXLength() {return *x_len;}
	double solid::getYLength() {return *y_len;}
	double solid::getZLength() {return *z_len;}

	void solid::setName(string name) {*name_ = name;}

	/**
	 * Sets the start of the facet chain.
	 * @param start First facet in the chain.
	 * DESTRUCTIVE!!! DO NOT REPLACE EXISTING VALUES!!!
	 */
	void solid::setStartFacet(facet* start){
		firstFacet = start;
		int count = 0;
		int countFaces = 0;
		facet* iter = start;

		while(iter->getNext() != nullptr){
			count += iter->getNumVerts();
			countFaces += 1;
			iter = iter->getNext();
		}
		count += iter->getNumVerts();
		countFaces += 1;

		*numTotalVerts = count;
		*numFacets = countFaces;

		processCoords();
	}

	/// Destructor
	solid::~solid(){
		delete firstFacet;
		delete name_;
		delete numTotalVerts;
		delete numFacets;
		delete x_min;
		delete x_max;
		delete y_min;
		delete y_max;
		delete z_min;
		delete z_max;
		delete x_len;
		delete y_len;
		delete z_len;
	}

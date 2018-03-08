/**=============================================
 * CS3210
 * LAB 1: STL FILE READER
 * @file facet.cpp
 * @date March 8 2018
 * @author Dennis Droese
 *
 * Facet Class
 *
 =============================================*/

#include "STLfile.h"

using namespace std;

	/**
	 * Counts the number of vertices within this facet.
	 * @return Number of vertices.
	 */
	int facet::countVertsInChain(){
		int count = 0;
		vertex* iter = firstVert;

		while(iter->getNext() != nullptr){
			count += 1;
			iter = iter->getNext();
		}

		return count + 1;
	}


	facet::facet(double nx, double ny, double nz) {
		firstVert = nullptr;
		numVerts = new int;
		nx_ = new double(nx);
		ny_ = new double(ny);
		nz_ = new double(nz);
		next = nullptr;
	}

	facet::facet() {
		firstVert = nullptr;
		nx_ = nullptr;
		ny_ = nullptr;
		nz_ = nullptr;
		numVerts = new int;
		next = nullptr;
	}

	int facet::getNumVerts() {return *numVerts;}

	vertex* facet::getFirstVertex() {return firstVert;}

	/**
	 * Replaces the current vertex chain with a specified one.
	 * @param first New vertex chain.
	 */
	void facet::setFirstVertex(vertex* first) {
		firstVert = first;
		*numVerts = countVertsInChain();
	}

	/**
	 * Gets a pointer to the next facet in the chain.
	 * @return A pointer to the next facet in the chain.
	 */
	facet* facet::getNext() {return (facet*)(next);}

	/**
	 * Sets the pointer of the next facet in the chain.
	 * @param nextFacet Facet to be added to the chain.
	 * DESTRUCTIVE! DO NOT REPLACE EXISTING VALUES!
	 */
	void facet::setNext(facet* nextFacet) {
		if(next == nullptr){
			next = nextFacet;
		}
	}

	/// Destructor
	facet::~facet(){
		delete next;
		delete firstVert;
		delete numVerts;
		delete nx_;
		delete ny_;
		delete nz_;
	}

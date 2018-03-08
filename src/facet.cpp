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
	int Facet::countVertsInChain(){
		int count = 0;
		Vertex* iter = firstVert;

		while(iter->getNext() != nullptr){
			count += 1;
			iter = iter->getNext();
		}

		return count + 1;
	}


	Facet::Facet(double nx, double ny, double nz) {
		firstVert = nullptr;
		numVerts = new int;
		nx_ = new double(nx);
		ny_ = new double(ny);
		nz_ = new double(nz);
		next = nullptr;
	}

	Facet::Facet() {
		firstVert = nullptr;
		nx_ = nullptr;
		ny_ = nullptr;
		nz_ = nullptr;
		numVerts = new int;
		next = nullptr;
	}

	int Facet::getNumVerts() {return *numVerts;}

	Vertex* Facet::getFirstVertex() {return firstVert;}

	/**
	 * Replaces the current vertex chain with a specified one.
	 * @param first New vertex chain.
	 */
	void Facet::setFirstVertex(Vertex* first) {
		firstVert = first;
		*numVerts = countVertsInChain();
	}

	/**
	 * Gets a pointer to the next facet in the chain.
	 * @return A pointer to the next facet in the chain.
	 */
	Facet* Facet::getNext() {return (Facet*)(next);}

	/**
	 * Sets the pointer of the next facet in the chain.
	 * @param nextFacet Facet to be added to the chain.
	 * DESTRUCTIVE! DO NOT REPLACE EXISTING VALUES!
	 */
	void Facet::setNext(Facet* nextFacet) {
		if(next == nullptr){
			next = nextFacet;
		}
	}

	/// Destructor
	Facet::~Facet(){
		delete next;
		delete firstVert;
		delete numVerts;
		delete nx_;
		delete ny_;
		delete nz_;
	}

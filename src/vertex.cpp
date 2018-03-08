/**=============================================
 * CS3210
 * LAB 1: STL FILE READER
 * @file vertex.cpp
 * @date March 8 2018
 * @author Dennis Droese
 *
 * Vertex Class
 *
 =============================================*/

/**
 * Vertex Class
 *
 * Represents a Vertex read in from an STL file.
 * Also knows if any vertices follow it.
 *
 * Uses a linked-list structure to keep track of connected vertices.
 */


#include "STLfile.h"

using namespace std;

	vertex::vertex(double x, double y, double z) {
		x_ = new double(x);
		y_ = new double(y);
		z_ = new double(z);
		next = nullptr;
	}

	vertex::vertex() {
		x_ = new double;
		y_ = new double;
		z_ = new double;
		next = nullptr;
	}

	double vertex::getX() {return *x_;}
	double vertex::getY() {return *y_;}
	double vertex::getZ() {return *z_;}

	vertex* vertex::getNext() {return (vertex*)(next);}

	void vertex::setX(double x) {*x_ = x;}
	void vertex::setY(double y) {*y_ = y;}
	void vertex::setZ(double z) {*z_ = z;}

	void vertex::setNext(vertex* nextVert) {
		if(next == nullptr){
			next = nextVert;
		}
	}


	/// Destructor
	vertex::~vertex(){
		delete next;
		delete x_;
		delete y_;
		delete z_;
	}


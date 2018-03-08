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

#include "STLfile.h"

using namespace std;

	Vertex::Vertex(double x, double y, double z) {
		x_ = new double(x);
		y_ = new double(y);
		z_ = new double(z);
		next = nullptr;
	}

	Vertex::Vertex() {
		x_ = new double;
		y_ = new double;
		z_ = new double;
		next = nullptr;
	}

	double Vertex::getX() {return *x_;}
	double Vertex::getY() {return *y_;}
	double Vertex::getZ() {return *z_;}

	Vertex* Vertex::getNext() {return (Vertex*)(next);}

	void Vertex::setX(double x) {*x_ = x;}
	void Vertex::setY(double y) {*y_ = y;}
	void Vertex::setZ(double z) {*z_ = z;}

	void Vertex::setNext(Vertex* nextVert) {
		if(next == nullptr){
			next = nextVert;
		}
	}


	/// Destructor
	Vertex::~Vertex(){


		delete next;
		delete x_;
		delete y_;
		delete z_;


	}


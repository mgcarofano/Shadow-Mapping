///////////////////////////////////////////////////////////////////////////////
//
//	MATRIX4X4.h
//	Class declaration for a 4x4 matrix
//
//	Downloaded from: www.paulsprojects.net
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence.
//	http://www.paulsprojects.net/NewBSDLicense.txt
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

class MATRIX4X4 {

public:

	//constructors
	MATRIX4X4() { LoadIdentity(); };

	MATRIX4X4(
		float e0, float e1, float e2, float e3,
		float e4, float e5, float e6, float e7,
		float e8, float e9, float e10, float e11,
		float e12, float e13, float e14, float e15
	);

	MATRIX4X4(const float * rhs);

	MATRIX4X4(const MATRIX4X4 & rhs);

	//destructor
	~MATRIX4X4() {}

	//getters & setters
	void SetEntry(int position, float value);
	float GetEntry(int position) const;
	VECTOR4D GetRow(int position) const;
	VECTOR4D GetColumn(int position) const;
	
	void LoadIdentity(void);
	void LoadZero(void);
	
	//binary operators
	MATRIX4X4 operator+(const MATRIX4X4 & rhs) const;
	MATRIX4X4 operator-(const MATRIX4X4 & rhs) const;
	MATRIX4X4 operator*(const MATRIX4X4 & rhs) const;
	MATRIX4X4 operator*(const float rhs) const;
	MATRIX4X4 operator/(const float rhs) const;
	friend MATRIX4X4 operator*(float scaleFactor, const MATRIX4X4 & rhs) { return rhs*scaleFactor; };

	//comparison operators
	bool operator==(const MATRIX4X4 & rhs) const;
	bool operator!=(const MATRIX4X4 & rhs) const { return !((*this)==rhs); };

	//self operators
	void operator+=(const MATRIX4X4 & rhs) { (*this)=(*this)+rhs; };
	void operator-=(const MATRIX4X4 & rhs) { (*this)=(*this)-rhs; };
	void operator*=(const MATRIX4X4 & rhs) { (*this)=(*this)*rhs; };
	void operator*=(const float rhs) { (*this)=(*this)*rhs; };
	void operator/=(const float rhs) { (*this)=(*this)/rhs; };

	//unary operators
	MATRIX4X4 operator-(void) const;
	MATRIX4X4 operator+(void) const {return (*this);}
	
	//multiply a vector by this matrix
	VECTOR4D operator*(const VECTOR4D rhs) const;

	//cast to pointer to a (float *) for glGetFloatv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

protected:

	//member variables
	float entries[16];
	
};

#include "MATRIX4X4.cpp"
#endif	//MATRIX4X4_H
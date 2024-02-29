///////////////////////////////////////////////////////////////////////////////
//
//	VECTOR3D.h
//	Class declaration for a 3d vector
//
//	Downloaded from: www.paulsprojects.net
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence.
//	http://www.paulsprojects.net/NewBSDLicense.txt
//
///////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR3D_H
#define VECTOR3D_H

class VECTOR3D {
public:

	//constructors
	VECTOR3D(void) : x(0.0f), y(0.0f), z(0.0f) {}
	VECTOR3D(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {}
	VECTOR3D(const float * rhs) : x(*rhs), y(*(rhs+1)), z(*(rhs+2)) {}
	VECTOR3D(const VECTOR3D & rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

	//destructor
	~VECTOR3D() {}
	
	//setters
	void Set(float newX, float newY, float newZ) { x=newX; y=newY; z=newZ; }
	void SetX(float newX) { x = newX; }
	void SetY(float newY) { y = newY; }
	void SetZ(float newZ) { z = newZ; }

	//getters
	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetZ() const { return z; }

	void LoadZero(void) { x = y = z = 0.0f; }
	void LoadOne(void) { x = y = z = 1.0f; }
	
	//vector algebra
	VECTOR3D CrossProduct(const VECTOR3D & rhs) const {
		return VECTOR3D(
			y*rhs.z - z*rhs.y,
			z*rhs.x - x*rhs.z,
			x*rhs.y - y*rhs.x
		);
	}

	float DotProduct(const VECTOR3D & rhs) const { return x*rhs.x + y*rhs.y + z*rhs.z; }
	
	void Normalize();
	VECTOR3D GetNormalized() const;
	
	float GetLength() const { return (float) sqrt((x*x) + (y*y) + (z*z)); }
	float GetSquaredLength() const { return (x*x) + (y*y) + (z*z); }

	//binary operators
	VECTOR3D operator+(const VECTOR3D & rhs) const { return VECTOR3D(x + rhs.x, y + rhs.y, z + rhs.z); }
	VECTOR3D operator-(const VECTOR3D & rhs) const { return VECTOR3D(x - rhs.x, y - rhs.y, z - rhs.z); }
	VECTOR3D operator*(const float rhs) const { return VECTOR3D(x*rhs, y*rhs, z*rhs); }
	VECTOR3D operator/(const float rhs) const {
		return (rhs == 0.0f)
			? VECTOR3D(0.0f, 0.0f, 0.0f)
			: VECTOR3D(x/rhs, y/rhs, z/rhs);
	}

	//multiply by a float
	friend VECTOR3D operator*(float scaleFactor, const VECTOR3D & rhs) { return rhs*scaleFactor; };

	//comparison operators
	bool operator==(const VECTOR3D & rhs) const { return (x==rhs.x && y==rhs.y && z==rhs.z); };
	bool operator!=(const VECTOR3D & rhs) const { return !((*this)==rhs); }

	//self operators
	void operator+=(const VECTOR3D & rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; }
	void operator-=(const VECTOR3D & rhs) {	x-=rhs.x; y-=rhs.y; z-=rhs.z; }
	void operator*=(const float rhs) { x *= rhs; y *= rhs; z *= rhs; }
	void operator/=(const float rhs) { if(rhs != 0.0f) { x /= rhs; y /= rhs; z /= rhs; } }

	//unary operators
	VECTOR3D operator-(void) const {return VECTOR3D(-x, -y, -z);}
	VECTOR3D operator+(void) const {return *this;}

	//cast to pointer to a (float *) for glVertex3fv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

protected:

	//member variables
	float x;
	float y;
	float z;

};

#include "VECTOR3D.cpp"
#endif	//VECTOR3D_H
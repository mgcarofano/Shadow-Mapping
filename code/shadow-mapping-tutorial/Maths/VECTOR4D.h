//////////////////////////////////////////////////////////////////////////////////////////
//	VECTOR4D.h
//	Class declaration for a 4d vector
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	8th November 2002	-	Changed Constructor layout
//									-	Some speed Improvements
//									-	Corrected Lerp
//				7th January 2003	-	Added QuadraticInterpolate
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef VECTOR4D_H
#define VECTOR4D_H

class VECTOR4D
{
public:
	//constructors
	VECTOR4D(void) : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

	VECTOR4D(
		float newX,
		float newY, 
		float newZ,
		float newW ) : x(newX), y(newY), z(newZ), w(newW) {}

	VECTOR4D(const float * rhs) : x(*rhs), y(*(rhs+1)), z(*(rhs+2)), w(*(rhs+3)) {}

	VECTOR4D(const VECTOR4D & rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

	//convert v3d to v4d
	VECTOR4D(const VECTOR3D & rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f) {}

	~VECTOR4D() {}

	void Set(float newX, float newY, float newZ, float newW) {
		x = newX;
		y = newY;
		z = newZ;
		w = newW;
	}
	
	void SetX(float newX) { x = newX; }
	void SetY(float newY) { y = newY; }
	void SetZ(float newZ) { z = newZ; }
	void SetW(float newW) { w = newW; }
	
	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetZ() const { return z; }
	float GetW() const { return w; }

	void LoadZero(void) { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }

	void LoadOne(void) { x = 1.0f; y = 1.0f; z = 1.0f; w = 1.0f; }

	//vector algebra
	float DotProduct(const VECTOR4D & rhs) { return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w; }

	//binary operators
	VECTOR4D operator+(const VECTOR4D & rhs) const { return VECTOR4D(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w); }

	VECTOR4D operator-(const VECTOR4D & rhs) const { return VECTOR4D(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w); }

	VECTOR4D operator*(const float rhs) const { return VECTOR4D(x*rhs, y*rhs, z*rhs, w*rhs); }

	VECTOR4D operator/(const float rhs) const {
		return (rhs==0.0f)
			? VECTOR4D(0.0f, 0.0f, 0.0f, 0.0f)
			: VECTOR4D(x/rhs, y/rhs, z/rhs, w/rhs);
	}

	//multiply by a float
	friend VECTOR4D operator*(float scaleFactor, const VECTOR4D & rhs);

	bool operator==(const VECTOR4D & rhs) const;
	bool operator!=(const VECTOR4D & rhs) const { return !((*this)==rhs); }

	//self-add etc
	void operator+=(const VECTOR4D & rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; }

	void operator-=(const VECTOR4D & rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; }

	void operator*=(const float rhs) { x *= rhs; y *= rhs; z *= rhs; w *= rhs; }

	void operator/=(const float rhs) {
		if(rhs==0.0f) {
			return;
		} else{
			x/=rhs;
			y/=rhs;
			z/=rhs;
			w/=rhs;
		}
	}

	//unary operators
	VECTOR4D operator-(void) const { return VECTOR4D(-x, -y, -z, -w); }
	VECTOR4D operator+(void) const { return (*this); }

	//cast to pointer to float for glVertex4fv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}

	//convert v4d to v3d
	operator VECTOR3D();

	//member variables
	float x;
	float y;
	float z;
	float w;
};

#include "VECTOR4D.cpp"
#endif	//VECTOR4D_H
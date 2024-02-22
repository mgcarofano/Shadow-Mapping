///////////////////////////////////////////////////////////////////////////////
//
//	MATRIX4X4.cpp
//	Function definitions for 4x4 matrix class
//
//	Downloaded from: www.paulsprojects.net
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence.
//	http://www.paulsprojects.net/NewBSDLicense.txt
//
///////////////////////////////////////////////////////////////////////////////

#include <memory.h>

MATRIX4X4::MATRIX4X4(float e0, float e1, float e2, float e3,
					float e4, float e5, float e6, float e7,
					float e8, float e9, float e10, float e11,
					float e12, float e13, float e14, float e15)
{
	entries[0] = e0;
	entries[1] = e1;
	entries[2] = e2;
	entries[3] = e3;
	entries[4] = e4;
	entries[5] = e5;
	entries[6] = e6;
	entries[7] = e7;
	entries[8] = e8;
	entries[9] = e9;
	entries[10] = e10;
	entries[11] = e11;
	entries[12] = e12;
	entries[13] = e13;
	entries[14] = e14;
	entries[15] = e15;
}

MATRIX4X4::MATRIX4X4(const MATRIX4X4 & rhs)
{
	memcpy(entries, rhs.entries, 16*sizeof(float));
}

MATRIX4X4::MATRIX4X4(const float * rhs)
{
	memcpy(entries, rhs, 16*sizeof(float));
}

void MATRIX4X4::SetEntry(int position, float value)
{
	if(position>=0 && position<=15)
		entries[position]=value;
}
	
float MATRIX4X4::GetEntry(int position) const
{
	if(position>=0 && position<=15)
		return entries[position];

	return 0.0f;
}

VECTOR4D MATRIX4X4::GetRow(int position) const
{
	switch (position) {
		case 0:
			return VECTOR4D(entries[0], entries[4], entries[8], entries[12]);
		case 1:
			return VECTOR4D(entries[1], entries[5], entries[9], entries[13]);
		case 2:
			return VECTOR4D(entries[2], entries[6], entries[10], entries[14]);
		case 3:
			return VECTOR4D(entries[3], entries[7], entries[11], entries[15]);
		default:
			break;
	}

	return VECTOR4D(0.0f, 0.0f, 0.0f, 0.0f);

}

VECTOR4D MATRIX4X4::GetColumn(int position) const
{
	switch (position) {
		case 0:
			return VECTOR4D(entries[0], entries[1], entries[2], entries[3]);
		case 1:
			return VECTOR4D(entries[4], entries[5], entries[6], entries[7]);
		case 2:
			return VECTOR4D(entries[8], entries[9], entries[10], entries[11]);
		case 3:
			return VECTOR4D(entries[12], entries[13], entries[14], entries[15]);
		default:
			break;
	}

	return VECTOR4D(0.0f, 0.0f, 0.0f, 0.0f);
}

void MATRIX4X4::LoadIdentity(void)
{
	memset(entries, 0, 16*sizeof(float));

	entries[0]=1.0f;
	entries[5]=1.0f;
	entries[10]=1.0f;
	entries[15]=1.0f;
}

void MATRIX4X4::LoadZero(void)
{
	memset(entries, 0, 16*sizeof(float));
}

MATRIX4X4 MATRIX4X4::operator+(const MATRIX4X4 & rhs) const		//overloaded operators
{
	return MATRIX4X4(
		entries[0] + rhs.entries[0],
		entries[1] + rhs.entries[1],
		entries[2] + rhs.entries[2],
		entries[3] + rhs.entries[3],
		entries[4] + rhs.entries[4],
		entries[5] + rhs.entries[5],
		entries[6] + rhs.entries[6],
		entries[7] + rhs.entries[7],
		entries[8] + rhs.entries[8],
		entries[9] + rhs.entries[9],
		entries[10] + rhs.entries[10],
		entries[11] + rhs.entries[11],
		entries[12] + rhs.entries[12],
		entries[13] + rhs.entries[13],
		entries[14] + rhs.entries[14],
		entries[15] + rhs.entries[15]
	);
}

MATRIX4X4 MATRIX4X4::operator-(const MATRIX4X4 & rhs) const		//overloaded operators
{
	return MATRIX4X4(
		entries[0] - rhs.entries[0],
		entries[1] - rhs.entries[1],
		entries[2] - rhs.entries[2],
		entries[3] - rhs.entries[3],
		entries[4] - rhs.entries[4],
		entries[5] - rhs.entries[5],
		entries[6] - rhs.entries[6],
		entries[7] - rhs.entries[7],
		entries[8] - rhs.entries[8],
		entries[9] - rhs.entries[9],
		entries[10] - rhs.entries[10],
		entries[11] - rhs.entries[11],
		entries[12] - rhs.entries[12],
		entries[13] - rhs.entries[13],
		entries[14] - rhs.entries[14],
		entries[15] - rhs.entries[15]
	);
}

MATRIX4X4 MATRIX4X4::operator*(const MATRIX4X4 & rhs) const
{

	float ret[16] = {};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				ret[i*4 + j] += entries[k*4 + j] * rhs.entries[i*4 + k];
				// printf("ret[%d] += entries[%d] * rhs.entries[%d]\n", (i*4 + j), (k*4 + j), (i*4 + k));
			}
		}
	}
	
	return MATRIX4X4(
		ret[0], ret[1], ret[2], ret[3],
		ret[4], ret[5], ret[6], ret[7],
		ret[8], ret[9], ret[10], ret[11],
		ret[12], ret[13], ret[14], ret[15]
	);

}

MATRIX4X4 MATRIX4X4::operator*(const float rhs) const
{
	return MATRIX4X4 (
		entries[0] * rhs,
		entries[1] * rhs,
		entries[2] * rhs,
		entries[3] * rhs,
		entries[4] * rhs,
		entries[5] * rhs,
		entries[6] * rhs,
		entries[7] * rhs,
		entries[8] * rhs,
		entries[9] * rhs,
		entries[10] * rhs,
		entries[11] * rhs,
		entries[12] * rhs,
		entries[13] * rhs,
		entries[14] * rhs,
		entries[15] * rhs
	);
}

MATRIX4X4 MATRIX4X4::operator/(const float rhs) const
{
	if (rhs==0.0f || rhs==1.0f)
		return (*this);
		
	float temp=1/rhs;

	return (*this)*temp;
}

bool MATRIX4X4::operator==(const MATRIX4X4 & rhs) const
{
	for(int i=0; i<16; i++) {
		if(entries[i] != rhs.entries[i])
			return false;
	}

	return true;
}

MATRIX4X4 MATRIX4X4::operator-(void) const
{
	MATRIX4X4 result(*this);

	for(int i=0; i<16; i++)
		result.entries[i]=-result.entries[i];

	return result;
}

VECTOR4D MATRIX4X4::operator*(const VECTOR4D rhs) const {
	return VECTOR4D(
		entries[0]*rhs.GetX() + entries[4]*rhs.GetY() + entries[8]*rhs.GetZ() + entries[12]*rhs.GetW(),
		entries[1]*rhs.GetX() + entries[5]*rhs.GetY() + entries[9]*rhs.GetZ() + entries[13]*rhs.GetW(),
		entries[2]*rhs.GetX() + entries[6]*rhs.GetY() + entries[10]*rhs.GetZ() + entries[14]*rhs.GetW(),
		entries[3]*rhs.GetX() + entries[7]*rhs.GetY() + entries[11]*rhs.GetZ() + entries[15]*rhs.GetW()
	);
}

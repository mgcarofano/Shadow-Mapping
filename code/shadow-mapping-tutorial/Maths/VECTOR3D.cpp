///////////////////////////////////////////////////////////////////////////////
//
//	VECTOR3D.cpp
//	Function definitions for VECTOR3D class
//
//	Downloaded from: www.paulsprojects.net
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence.
//	http://www.paulsprojects.net/NewBSDLicense.txt
//
///////////////////////////////////////////////////////////////////////////////

void VECTOR3D::Normalize()
{
	float length = GetLength();

	if(length == 1 || length == 0)
		return;

	float scalefactor = 1.0f/length;

	x *= scalefactor;
	y *= scalefactor;
	z *= scalefactor;
}

VECTOR3D VECTOR3D::GetNormalized() const
{
	VECTOR3D result(*this);
	result.Normalize();
	return result;
}

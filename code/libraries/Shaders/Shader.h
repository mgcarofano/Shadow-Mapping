#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* path);

// Utitlity class to load, compile and attach a vertex- and fragment shader to a program
class Shader {

public:

	GLuint ID;

	// Load a vertex and a fragment shader from file
	Shader() {};
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader() {}

	// Use the program
	void Use();

	// Delete the program
	void Delete();
};

#include "Shader.cpp"
#endif // SHADER_H

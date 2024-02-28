#ifndef VAO_H
#define VAO_H

#include "VBO.h"

class VAO {
    public:
        GLuint ID;

        VAO();
        ~VAO() {}

        void LinkVBO(VBO vbo, GLuint layout);
        
        void Bind();
        void Unbind();
        void Delete();
};

#include "VAO.cpp"
#endif // VAO_H
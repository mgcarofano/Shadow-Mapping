#ifndef VBO_H
#define VBO_H

class VBO {
    public:
        GLuint ID;

        VBO(GLfloat* verts, GLsizeiptr size);
        ~VBO() {}

        void Bind();
        void Unbind();
        void Delete();
};

#include "VBO.cpp"
#endif // VBO_H
#ifndef EBO_H
#define EBO_H

class EBO {
    public:
        GLuint ID;

        EBO(GLuint* indices, GLsizeiptr size);
        ~EBO() {}

        void Bind();
        void Unbind();
        void Delete();
};

#include "EBO.cpp"
#endif // EBO_H
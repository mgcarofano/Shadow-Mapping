VAO::VAO() {
    glGenVertexArraysAPPLE(1, &ID);
}

void VAO::LinkVBO(VBO vbo, GLuint layout) {
    vbo.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
}

void VAO::Bind() {
    glBindVertexArrayAPPLE(ID);
}

void VAO::Unbind() {
    glBindVertexArrayAPPLE(0);
}

void VAO::Delete() {
    glDeleteVertexArraysAPPLE(1, &ID);
}
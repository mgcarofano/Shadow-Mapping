CC=clang++
LIB=./libraries/GLFW/
file=example

main:
	$(CC) -I$(LIB) -L$(LIB) -lglfw3 \
		-framework OpenGL \
		-framework GLUT \
		-framework Cocoa \
		-framework IOKit \
		$(file).cpp -o $(file)
	./$(file)
	rm -f $(file)
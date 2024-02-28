
// Legge il contenuto di un file
std::string get_file_contents(const char* path) {

	FILE* file;
	char c = 0;
	std::string ret = "";

	if ((file = fopen(path, "r")) == NULL) {
		printf("Errore durante l'esecuzione!\n");
		printf("Applicazione terminata.\n");
		exit(1);
	}

	while ((c = fgetc(file)) != EOF) ret += c;

	return ret;

}

// Carica il vertex ed il fragment shader
Shader::Shader(const char* vertexPath, const char* fragmentPath) {

	// Carica il codice e crea il vertex shader
	std::string vertexFile = get_file_contents(vertexPath);
	const char* vertexSourceCode = vertexFile.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
	glCompileShader(vertexShader);

	// Carica il codice e crea il fragment shader
	std::string fragmentFile = get_file_contents(fragmentPath);
	const char* fragmentSourceCode = fragmentFile.c_str();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);
	glCompileShader(fragmentShader);

	// Crea il programma a cui sono allegati gli shader
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	// Elimina gli shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

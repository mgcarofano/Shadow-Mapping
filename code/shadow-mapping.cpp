/* 

	shadow-mapping.cpp
	di Mario Gabriele Carofano
	(from Shadow Mapping Tutorial - Paul Baker)

*/

/*	************************************************************************
	DESCRIZIONE

	In questo file è fornita una possibile implementazione dello Shadow
	Mapping da una singola fonte luminosa.
	
*/

/*	************************************************************************ */
//	LIBRERIE

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include "libraries/GLFW/glfw3.h"

#include "libraries/color.cpp"
#include "libraries/TIMER.h"

#include "libraries/Maths/VECTOR3D.h"
#include "libraries/Maths/VECTOR4D.h"
#include "libraries/Maths/MATRIX4X4.h"

// #include "libraries/Shaders/Shader.h"
// #include "libraries/Shaders/VAO.h"
// #include "libraries/Shaders/EBO.h"
// #include "libraries/Shaders/VBO.h"

#include "SCENE.cpp"

/*	************************************************************************ */
//  ENUMERAZIONI, COSTANTI E VARIABILI GLOBALI

#define WINDOW_WIDTH 750.0
#define WINDOW_HEIGHT 750.0
#define WINDOW_X_POSITION 400.0
#define WINDOW_Y_POSITION 100.0

// Shader
// Shader shaderProgram;

// Timer used for frame rate independent movement
TIMER timer;

//Camera & light positions
#define EYE_LIGHT 1
#define EYE_CAMERA 2

int eyePosition = EYE_CAMERA;

GLfloat cameraPositions[3][3] = {
	// {1.0f, 1.5f, -3.0f},	// ESEMPIO-PRESENTAZIONE
	{-2.5f, 3.5f, -2.5f},	// SCENE1

	// {4.0f, 4.0f, -1.0f}, // ESEMPIO-VINCOLO_FIELD_OF_VIEW
	{-4.5f, 3.5f, -2.5f},	// SCENE2
	
	{-2.5f, 2.0f, -2.5f}	// SCENE3
};

VECTOR3D lightPosition(2.0f, 3.0f,-2.0f);

// Shadow map info
GLuint shadowMapTexture;
const int shadowMapSize = 512;

// GLfloat shadowMapVertices[4][5] = {
// 	{0.55, 0.95, 0.0, 0.0, 1.0},	// D
// 	{0.55, 0.55, 0.0, 0.0, 0.0},	// A
// 	{0.95, 0.55, 0.0, 1.0, 0.0},	// B
// 	{0.95, 0.95, 0.0, 1.0, 1.0}	// C
// };
// GLuint shadowMapIndices[] = {
// 	0, 1, 2,
// 	0, 2, 3
// };

//window size
int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;

//Matrices
MATRIX4X4 lightProjectionMatrix, lightViewMatrix;
MATRIX4X4 cameraProjectionMatrix, cameraViewMatrix;

static MATRIX4X4 biasMatrix(
	0.5f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.01f
);	//bias from [-1, 1] to [0, 1]

// Angolo di rotazione delle sfere.
float angle = 0.0f;

// Velocità dell'animazione.
int animation_speed = 0;

// Scelta della scena da disegnare.
int scene = SCENE2;

// Execution performance
#define CSV_TIME_PATH "../output/time-shadow_mapping.csv"
#define INIT 0
#define SHADOW 1
#define NO_SHADOW 2

const char* getStringType(int type_input) {
	switch(type_input) {
		case INIT:
			return "INIT";
		case SHADOW:
			return "SHADOW";
		case NO_SHADOW:
			return "NO_SHADOW";
		default:
			return "";
	}
}

bool performance = true;

double execution_start[3] = {};
double execution_end[3] = {};
double execution_time[3] = {};

/*	************************************************************************ */
//  FUNZIONI ACCESSORIE

//Called on window resize
void WindowResize(int w, int h) {

	//Save new window size
	windowWidth = w;
	windowHeight = h;

	//Update the camera's projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(45.0f, (float) windowWidth/windowHeight, 1.0f, 100.0f);
		glGetFloatv(GL_PROJECTION_MATRIX, cameraProjectionMatrix);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void UpdateScene() {

	// Update 'cameraProjectionMatrix'
	WindowResize(windowWidth, windowHeight);
	
	// Update 'cameraViewMatrix'
	glPushMatrix();
		glLoadIdentity();
		gluLookAt(
			cameraPositions[scene-1][0], cameraPositions[scene-1][1], cameraPositions[scene-1][2],
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		);
		glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);
	glPopMatrix();
	
	// Update 'lightProjectionMatrix'
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
		glGetFloatv(GL_PROJECTION_MATRIX, lightProjectionMatrix);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	// Update 'lightViewMatrix'
	glPushMatrix();
		glLoadIdentity();
		gluLookAt(
			lightPosition.GetX(), lightPosition.GetY(), lightPosition.GetZ(),
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		);
		glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);
	glPopMatrix();
	
}

void UpdateEyePosition(int eyepos) {

	switch(eyepos) {
		case EYE_LIGHT:
		{
			eyePosition = EYE_LIGHT;

			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(lightProjectionMatrix);

			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(lightViewMatrix);

			glViewport(0, 0, shadowMapSize, shadowMapSize);
			break;
		}
		case EYE_CAMERA:
		{
			eyePosition = EYE_CAMERA;

			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(cameraProjectionMatrix);
			
			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(cameraViewMatrix);

			glViewport(0, 0, windowWidth, windowHeight);
			break;
		}
	}
}

bool toggleEyePosition() {
	if (eyePosition == EYE_LIGHT) eyePosition = EYE_CAMERA;
	else eyePosition = EYE_LIGHT;
	return eyePosition;
}

//Called for initiation
bool Init(void) {

	glPointSize(3.0);
	
	//Load identity modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Shading states
	glShadeModel(GL_SMOOTH);
	glClearColor(BLACK[0], BLACK[1], BLACK[2], 1.0);
	glColor4f(WHITE[0], WHITE[1], WHITE[2], 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//We use glScale when drawing the scene
	glEnable(GL_NORMALIZE);

	//Create the shadow map texture
	glGenTextures(1, &shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_DEPTH_COMPONENT,
		shadowMapSize,
		shadowMapSize,
		0,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		NULL
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// glFramebufferTexture2D(
	// 	GL_FRAMEBUFFER,
	// 	GL_DEPTH_ATTACHMENT,
	// 	GL_TEXTURE_2D,
	// 	shadowMapTexture,
	// 	0
	// );

	// // Verifica che il framebuffer sia stato creato correttamente
	// if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
	// 	printf("Errore nella creazione del framebuffer.");
	// 	return false;
	// }

	//Use the color as the ambient and diffuse material
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

	UpdateScene();

	return true;
}

//1st step - Draw from light's point of view
void FirstStep(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Si impostano le matrici della luce per 'GL_PROJECTION' e 'MODELVIEW'
	// Use viewport the same size as the shadow map
	UpdateEyePosition(EYE_LIGHT);

	//Draw back faces into the shadow map
	glCullFace(GL_FRONT);

	//Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);
	
	//Draw the scene
	DrawScene(angle, scene);

	//Read the depth buffer into the shadow map texture
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, shadowMapSize, shadowMapSize, 0);

	//restore states
	glBindTexture(GL_TEXTURE_2D, 0);
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);
}

//2nd step - Draw from camera's point of view with dim light
void SecondStep(void) {

	glClear(GL_DEPTH_BUFFER_BIT);

	// Si impostano le matrici della camera per 'GL_PROJECTION' e 'MODELVIEW'
	// Use viewport the same size as the window
	UpdateEyePosition(EYE_CAMERA);

	//Use dim light to represent shadowed areas
	glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(lightPosition));
	glLightfv(GL_LIGHT1, GL_AMBIENT, GRAY_20);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, GRAY_20);
	glLightfv(GL_LIGHT1, GL_SPECULAR, BLACK);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	DrawScene(angle, scene);
}

//3rd step - Draw from camera's point of view with bright light
void ThirdStep(void) {

	// Si impostano le matrici della camera per 'GL_PROJECTION' e 'MODELVIEW'
	// Use viewport the same size as the window
	UpdateEyePosition(EYE_CAMERA);

	// Si attivano le luci della scena
	glLightfv(GL_LIGHT1, GL_DIFFUSE, WHITE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, WHITE);

	/*
		Calculate texture matrix for projection.

		The MATRIX4X4 'biasMatrix' takes us from eye space
		to the light's clip space. It is postmultiplied by the inverse
		of the current view matrix when specifying texgen.
	*/

	MATRIX4X4 textureMatrix =
		biasMatrix
		* lightProjectionMatrix
		* lightViewMatrix;


	/*
		Per garantire la caratteristica di essere una tecnica image-based,
		utilizziamo la modalità GL_EYE_LINEAR. In questo modo la texture
		è fissata nello spazio immagine del viewport, cioè la texture
		è indipendente rispetto alle trasformazioni di modellazione
		degli oggetti in scena.
	*/

	//Set up texture coordinate generation.
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
	glEnable(GL_TEXTURE_GEN_R);

	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
	glEnable(GL_TEXTURE_GEN_Q);

	//Bind & enable shadow map texture
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glEnable(GL_TEXTURE_2D);

	//Enable shadow comparison
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

	//Set alpha test to discard false comparisons
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);

	DrawScene(angle, scene);
}

// void DisplayShadowMap() {
// 	glBindTexture(GL_TEXTURE_2D, 0);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
	
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();

// 	glViewport(0, 0, windowWidth, windowHeight);
// 	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 	shaderProgram = Shader("./Shaders/vertex.shader", "./Shaders/fragment.shader");
// 	shaderProgram.Use();
// 	// glBindTexture(GL_TEXTURE_2D, shadowMapTexture);

// 	// GLint w = 0, h = 0;
// 	// glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
// 	// glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
// 	// printf("w: %d, h: %d\n", w, h);

// 	// GLint boundTexture;
// 	// glGetIntegerv(GL_TEXTURE_BINDING_2D, &boundTexture);
// 	// printf("boundTexture: %d, shadowMapTexture: %d\n", boundTexture, shadowMapTexture);

// 	// Caricamento dei dati del quad in buffer
// 	GLuint quadVAO, quadVBO, quadEBO;
// 	glGenVertexArraysAPPLE(1, &quadVAO);
// 	glGenBuffers(1, &quadVBO);
// 	glGenBuffers(1, &quadEBO);

// 	glBindVertexArrayAPPLE(quadVAO);
// 	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(shadowMapVertices), shadowMapVertices, GL_STATIC_DRAW);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shadowMapIndices), shadowMapIndices, GL_STATIC_DRAW);

// 	// Posizione
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
// 	glEnableVertexAttribArray(0);

// 	// Coordinate texture
// 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
// 	glEnableVertexAttribArray(1);

// 	// Disegna il quad
// 	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

// 	// Pulizia delle risorse
// 	glBindVertexArrayAPPLE(0);
// 	glDeleteVertexArraysAPPLE(1, &quadVAO);
// 	glDeleteBuffers(1, &quadVBO);
// 	glDeleteBuffers(1, &quadEBO);
// 	glBindTexture(GL_TEXTURE_2D, 0);
// }

void writeTimeCSV(
	const char* out_path,
	int scene,
	int type_input,
	float animation_speed,
	double* execution_time
) {

	FILE *csv_file;
	int size = 0;

	if ((csv_file = fopen(out_path, "a")) == NULL) {
		printf("Impossibile aprire il file .csv!\n");
		printf("Applicazione terminata.\n");
		exit(1);
	}

	// Se il file e' vuoto, allora non inserire '\n'
	fseek(csv_file, 0, SEEK_END);
    size = ftell(csv_file);
	if (size != 0) {
		fprintf(csv_file, "\n");
	}

	fseek(csv_file, 0, SEEK_SET);
	fprintf(csv_file, "%d,%s,%s,%.1f,%f",
		scene, getStringType(type_input),
		"true",
		animation_speed,
		execution_time[type_input]
	);

	fclose(csv_file);

	printf("%s aggiornato con successo!\n\n", out_path);

}

//Called to draw scene
void DisplayScene(void) {

	if (performance) {
		execution_start[SHADOW] = timer.GetTime();
	}

	// Calculate the angle of spheres in scene from time in order to make an animation.
	angle = timer.GetTime() * animation_speed;

	if (eyePosition == EYE_LIGHT) {
	// if (true) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		UpdateEyePosition(EYE_LIGHT);
		// UpdateEyePosition(EYE_CAMERA); // ESEMPIO-PRESENTAZIONE
		DrawScene(angle, scene);
	} else {
		FirstStep();
		SecondStep();
		ThirdStep();
	}

	// DisplayShadowMap();

	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);

	//reset matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glFinish();
	glutSwapBuffers();

	if (performance) {
		performance = false;
		execution_end[SHADOW] = timer.GetTime();
		execution_time[SHADOW] = (execution_end[SHADOW] - execution_start[SHADOW]);
		writeTimeCSV(CSV_TIME_PATH, scene, SHADOW, animation_speed, execution_time);
	}

	glutPostRedisplay();

}

/*	************************************************************************ */
//  FUNZIONI PER INTERAZIONE DA TASTIERA

GLvoid keyboardOrdFunc(unsigned char key, int x, int y) {

	switch (key) {
        case 27:
        {
			exit(0);
		}
		case 'r':
		case 'R':
        {
			timer.Reset();
			animation_speed = 0;
			performance = true;
			break;
		}
		case 'l':
		case 'L':
        {
			toggleEyePosition();
			break;
		}
		case 'p':
		case 'P':
        {
			timer.Pause();
			break;
		}
		case 'u':
		case 'U':
        {
			timer.Unpause();
			break;
		}
		case ' ':
        {
			if (++scene > NUM_SCENE) scene = SCENE1;
			UpdateScene();
			timer.Reset();
			animation_speed = 0;
			performance = true;
			break;
		}
		default:
			break;
	}

	glutPostRedisplay();

}

GLvoid keyboardSpecFunc(int key, int x, int y) {

	timer.Reset();
	
	switch (key) {
		case GLUT_KEY_UP: {
			animation_speed += 5;
			break;
		}
		case GLUT_KEY_DOWN: {
			animation_speed -= 5;
			break;
		}
		case GLUT_KEY_LEFT: {
			animation_speed -= 10;
			break;
		}
		case GLUT_KEY_RIGHT: {
			animation_speed += 10;
			break;
		}
		default:
			break;
	}

	glutPostRedisplay();

}

/*	************************************************************************ */
//  FUNZIONI PER INTERAZIONE DA MOUSE

GLvoid mouseOrdFunc(int button, int state, int x, int y) {

	switch(button) {
		case GLUT_LEFT_BUTTON: {
			// left_mouse_func(state, x, y);
			break;
		}
		case GLUT_RIGHT_BUTTON: {
			// right_mouse_func(state, x, y);
			break;
		}
		default:
			break;
	}

	glutPostRedisplay();

}

/*	************************************************************************ */
//  MAIN

int main(int argc, char** argv) {

	// Reset timer
	performance = true;
	timer.Reset();

	execution_start[INIT] = timer.GetTime();
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Shadow Mapping");

	if(!Init())
		return 0;

	glutDisplayFunc(DisplayScene);
	glutReshapeFunc(WindowResize);
	glutMouseFunc(mouseOrdFunc);
	glutKeyboardFunc(keyboardOrdFunc);
	glutSpecialFunc(keyboardSpecFunc);

	execution_end[INIT] = timer.GetTime();
	execution_time[INIT] = execution_end[INIT] - execution_start[INIT];
	writeTimeCSV(CSV_TIME_PATH, scene, INIT, 0.0f, execution_time);

	// shaderProgram = Shader("./Shaders/vertex.shader", "./Shaders/fragment.shader");

	// VAO vao;
	// vao.Bind();

	// shaderProgram.Use();
	// vao.Bind();

	glutMainLoop();

	// vao.Delete();
	// shaderProgram.Delete();
	return 0;
}

/*	************************************************************************ */
/*	RIFERIMENTI
	
*/

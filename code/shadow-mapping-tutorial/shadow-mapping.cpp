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
#include "../libraries/GLFW/glfw3.h"
#include "../libraries/controller.cpp"

#include "Maths/VECTOR3D.h"
#include "Maths/VECTOR4D.h"
#include "Maths/MATRIX4X4.h"

#include "Shaders/Shader.h"
#include "Shaders/VAO.h"
#include "Shaders/EBO.h"
#include "Shaders/VBO.h"

#include "SCENE.cpp"
#include "TIMER.h"

/*	************************************************************************ */
//  ENUMERAZIONI, COSTANTI E VARIABILI GLOBALI

#define EPSILON 0.01f

// Timer used for frame rate independent movement
TIMER timer;

//Camera & light positions
VECTOR3D cameraPosition(-2.5f, 3.5f,-2.5f);
VECTOR3D lightPosition(2.0f, 3.0f,-2.0f);

//Size of shadow map
const int shadowMapSize=512;

//Textures
GLuint shadowMapTexture;

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
	0.5f, 0.5f, 0.5f, 1.0f
);	//bias from [-1, 1] to [0, 1]

// Angolo di rotazione delle sfere.
float angle = 0.0f;

// Velocità dell'animazione.
int animation_speed = 0;

// Scelta della scena da disegnare.
int scene = SCENE1;

/*	************************************************************************ */
//  FUNZIONI ACCESSORIE

//Called on window resize
void WindowResize(int w, int h) {

	//Save new window size
	windowWidth = w;
	windowHeight = h;

	//Update the camera's projection matrix
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(45.0f, (float) windowWidth/windowHeight, 1.0f, 100.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);
	glPopMatrix();

}

//Called for initiation
bool Init(void) {
	
	//Load identity modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Shading states
	glShadeModel(GL_SMOOTH);
	glClearColor(BLACK[0], BLACK[1], BLACK[2], 1.0);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
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
		GL_UNSIGNED_BYTE,
		NULL
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//Use the color as the ambient and diffuse material
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

	glPushMatrix();

		// Update 'cameraProjectionMatrix'
		WindowResize(windowWidth, windowHeight);
		
		// Update 'cameraViewMatrix'
		glLoadIdentity();
		gluLookAt(
			cameraPosition.GetX(), cameraPosition.GetY(), cameraPosition.GetZ(),
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		);
		glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);
		
		// Update 'lightProjectionMatrix'
		glLoadIdentity();
		gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);
		
		// Update 'lightViewMatrix'
		glLoadIdentity();
		gluLookAt(
			lightPosition.GetX(), lightPosition.GetY(), lightPosition.GetZ(),
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		);
		glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);
	
	glPopMatrix();

	// Reset timer
	timer.Reset();

	return true;
}

//1st step - Draw from light's point of view
void FirstStep(void) {
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(lightProjectionMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(lightViewMatrix);

	//Use viewport the same size as the shadow map
	glViewport(0, 0, shadowMapSize, shadowMapSize);

	//Draw back faces into the shadow map
	glCullFace(GL_FRONT);

	//Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);
	
	//Draw the scene
	DrawScene(angle, scene);

	//Read the depth buffer into the shadow map texture
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowMapSize, shadowMapSize);

	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);
}

//2nd step - Draw from camera's point of view
void SecondStep(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(cameraProjectionMatrix);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(cameraViewMatrix);

	glViewport(0, 0, windowWidth, windowHeight);

	//Use dim light to represent shadowed areas
	glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(lightPosition));
	glLightfv(GL_LIGHT1, GL_AMBIENT, GRAY_20);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, GRAY_20);
	glLightfv(GL_LIGHT1, GL_SPECULAR, BLACK);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	DrawScene(angle, scene);
}

//3rd step - Draw with bright light
void ThirdStep(void) {

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

	//Set alpha test to discard false comparisons
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);

	DrawScene(angle, scene);
}

//Called to draw scene
void Display(void) {

	glPointSize(3.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate the angle of spheres in scene from time in order to make an animation.
	angle = timer.GetTime() * animation_speed;

	FirstStep();
	SecondStep();
	ThirdStep();

	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);
	
	//Set matrices for ortho
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//reset matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glFinish();
	glutSwapBuffers();
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
		case 'q':
		case 'Q':
        {
			q_func();
			break;
		}
		case 'a':
		case 'A':
        {
			a_func();
			break;
		}
		case 'w':
		case 'W':
        {
			w_func();
			break;
		}
		case 's':
		case 'S':
        {
			s_func();
			break;
		}
		case 'e':
		case 'E':
        {
			e_func();
			break;
		}
		case 'd':
		case 'D':
        {
			d_func();
			break;
		}
		case 'r':
		case 'R':
        {
			timer.Reset();
			animation_speed = 0;
			break;
		}
		case 'i':
		case 'I':
        {
			i_func();
			break;
		}
		case 'j':
		case 'J':
        {
			j_func();
			break;
		}
		case 'k':
		case 'K':
        {
			k_func();
			break;
		}
		case 'l':
		case 'L':
        {
			l_func();
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
			left_mouse_func(state, x, y);
			break;
		}
		case GLUT_RIGHT_BUTTON: {
			right_mouse_func(state, x, y);
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
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Shadow Mapping");

	if(!Init())
		return 0;

	glutDisplayFunc(Display);
	glutReshapeFunc(WindowResize);
	glutMouseFunc(mouseOrdFunc);
	glutKeyboardFunc(keyboardOrdFunc);
	glutSpecialFunc(keyboardSpecFunc);

	Shader shaderProgram("./Shaders/vertex.shader", "./Shaders/fragment.shader");

	// VAO vao;
	// vao.Bind();

	shaderProgram.Use();
	// vao.Bind();

	glutMainLoop();

	// vao.Delete();
	shaderProgram.Delete();
	return 0;
}

/*	************************************************************************ */
/*	RIFERIMENTI
	
*/

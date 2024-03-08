/* 

	no_shadow.cpp
	di Mario Gabriele Carofano

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

#include "SCENE.cpp"

/*	************************************************************************ */
//  ENUMERAZIONI, COSTANTI E VARIABILI GLOBALI

#define WINDOW_WIDTH 750.0
#define WINDOW_HEIGHT 750.0
#define WINDOW_X_POSITION 400.0
#define WINDOW_Y_POSITION 100.0

// Timer used for frame rate independent movement
TIMER timer;

//Camera & light positions
#define EYE_LIGHT 1
#define EYE_CAMERA 2

int eyePosition = EYE_CAMERA;

GLfloat cameraPositions[3][3] = {
	// {1.0f, 1.5f, -3.0f},	// ESEMPIO-PRESENTAZIONE
	{-2.5f, 3.5f, -2.5f},	// SCENE1
	{-4.5f, 3.5f, -2.5f},	// SCENE2
	{-2.5f, 2.0f, -2.5f}	// SCENE3
};

VECTOR3D lightPosition(2.0f, 3.0f,-2.0f);

//window size
int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;

// Angolo di rotazione delle sfere.
float angle = 0.0f;

// Velocità dell'animazione.
int animation_speed = 0;

// Scelta della scena da disegnare.
int scene = SCENE3;

// Execution performance
#define CSV_TIME_PATH "../output/time-no_shadow.csv"
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

	glPushMatrix();
		glLoadIdentity();
		gluPerspective(45.0f, (float) windowWidth/windowHeight, 1.0f, 100.0f);
	glPopMatrix();

}

void UpdateScene() {
	glPushMatrix();

		WindowResize(windowWidth, windowHeight);
	
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
	glColor4f(WHITE[0], WHITE[1], WHITE[2], 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//We use glScale when drawing the scene
	glEnable(GL_NORMALIZE);

	//Use the color as the ambient and diffuse material
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

	UpdateScene();

	return true;
}

void writeTimeCSV(
	const char* out_path,
	int scene,
	int type_input,
	bool shadowMapVisibility,
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
		"false",
		animation_speed,
		execution_time[type_input]
	);

	fclose(csv_file);

	printf("%s aggiornato con successo!\n\n", out_path);

}

//Called to draw scene
void DisplayScene(void) {

	if (performance) {
		execution_start[NO_SHADOW] = timer.GetTime();
	}

	glPointSize(3.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate the angle of spheres in scene from time in order to make an animation.
	angle = timer.GetTime() * animation_speed;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float) windowWidth/windowHeight, 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		cameraPositions[scene-1][0], cameraPositions[scene-1][1], cameraPositions[scene-1][2],
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	);

	// Si attivano le luci della scena
	glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(lightPosition));
	glLightfv(GL_LIGHT1, GL_DIFFUSE, WHITE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, WHITE);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	DrawScene(angle, scene);

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

	if (performance) {
		performance = false;
		execution_end[NO_SHADOW] = timer.GetTime();
		execution_time[NO_SHADOW] = (execution_end[NO_SHADOW] - execution_start[NO_SHADOW]);
		writeTimeCSV(CSV_TIME_PATH, scene, NO_SHADOW, false, animation_speed, execution_time);
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

// GLvoid mouseOrdFunc(int button, int state, int x, int y) {

// 	switch(button) {
// 		case GLUT_LEFT_BUTTON: {
// 			// left_mouse_func(state, x, y);
// 			break;
// 		}
// 		case GLUT_RIGHT_BUTTON: {
// 			// right_mouse_func(state, x, y);
// 			break;
// 		}
// 		default:
// 			break;
// 	}

// 	glutPostRedisplay();

// }

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
	// glutMouseFunc(mouseOrdFunc);
	glutKeyboardFunc(keyboardOrdFunc);
	glutSpecialFunc(keyboardSpecFunc);

	execution_end[INIT] = timer.GetTime();
	execution_time[INIT] = execution_end[INIT] - execution_start[INIT];
	writeTimeCSV(CSV_TIME_PATH, scene, INIT, false, 0.0f, execution_time);
	// printf("INIT - start: %f, end: %f, tot: %f\n", execution_start[INIT], execution_end[INIT], execution_time[INIT]);

	glutMainLoop();

	return 0;
}

/*	************************************************************************ */
/*	RIFERIMENTI
	
*/

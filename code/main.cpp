/*

	main.cpp
	di Mario Gabriele Carofano

*/

/*	************************************************************************* */
//	LIBRERIE

#include "libraries/controller.cpp"

/*	************************************************************************* */
//  ENUMERAZIONI, COSTANTI E VARIABILI GLOBALI

float* eyePoint = NULL;

/*	************************************************************************* */
//  FUNZIONI ACCESSORIE

GLvoid drawScene(GLvoid) {

	glPointSize(3.0);
	glClearColor(BLACK[0], BLACK[1], BLACK[2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_LIGHTING);
	// glEnable(GL_LIGHT0);
	// glEnable(GL_NORMALIZE);
	// glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(fovy, aspect, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    computeEyePoint(eyePoint);
    gluLookAt(
        eyePoint[0], eyePoint[1], eyePoint[2],	// eyePoint
        x_position, y_position, z_position,		// center
        0.0, 1.0, 0.0						    // up-vector
    );

    glPushMatrix();
        glBegin(GL_POINTS);
            // ...
        glEnd();
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
	
    glFlush();
	glutSwapBuffers();

}

/*	************************************************************************* */
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
			r_func();
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
		case ' ':
        {
			space_func();
			break;
		}
		default:
			break;
	}

	glutPostRedisplay();

}

GLvoid keyboardSpecFunc(int key, int x, int y) {
	
	switch (key) {
		case GLUT_KEY_UP: {
			up_func();
			break;
		}
		case GLUT_KEY_DOWN: {
			down_func();
			break;
		}
		case GLUT_KEY_LEFT: {
			left_key_func();
			break;
		}
		case GLUT_KEY_RIGHT: {
			right_key_func();
			break;
		}
		default:
			break;
	}

	glutPostRedisplay();

}

/*	************************************************************************* */
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

/*	************************************************************************* */
//  MAIN

int main (int argc, char** argv) {

	srand(time(NULL));
	eyePoint = (float*) calloc(3, sizeof(float));

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Shadow Mapping");
	
	glutDisplayFunc(drawScene);

	glutMouseFunc(mouseOrdFunc);
	glutKeyboardFunc(keyboardOrdFunc);
	glutSpecialFunc(keyboardSpecFunc);

	r_func();
	
	glutMainLoop();

	free(eyePoint);
}

/*	************************************************************************* */
/*	RIFERIMENTI
	
*/

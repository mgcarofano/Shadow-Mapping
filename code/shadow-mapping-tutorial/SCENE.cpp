/*

	SCENE.cpp
	di Mario Gabriele Carofano

*/

/*	************************************************************************ */
//  ENUMERAZIONI, COSTANTI E VARIABILI GLOBALI

#define NUM_SCENE 3
#define SCENE1 1
#define SCENE2 2
#define SCENE3 3

/*	************************************************************************ */
//  FUNZIONI DI DISEGNO DELLE SCENE

void Scene1(float angle) {
	
	// BASE
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);
		glScalef(1.0f, 0.05f, 1.0f);
		glutSolidCube(4.0f);
	glPopMatrix();

	// TORUS
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.5f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidTorus(0.2, 0.5, 24, 48);
	glPopMatrix();

	// SPHERES
	glPushMatrix();
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);

		glTranslatef(0.45f, 1.0f, 0.45f);
		glutSolidSphere(0.2, 24, 24);

		glTranslatef(-0.9f, 0.0f, 0.0f);
		glutSolidSphere(0.2, 24, 24);

		glTranslatef(0.0f, 0.0f,-0.9f);
		glutSolidSphere(0.2, 24, 24);

		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(0.9f, 0.0f, 0.0f);
		glutSolidSphere(0.2, 24, 24);
	glPopMatrix();

}

void Scene2(float angle) {

}

void Scene3(float angle) {

}

/*	************************************************************************ */
//  FUNZIONI DI SCELTA DELLA SCENA DA DISEGNARE

void DrawScene(float angle, int scene) {

    switch(scene) {
        case SCENE1:
        {
            Scene1(angle);
            break;
        }
        case SCENE2:
        {
            Scene2(angle);
            break;
        }
        case SCENE3:
        {
            Scene3(angle);
            break;
        }
        default:
            break;
    }

}

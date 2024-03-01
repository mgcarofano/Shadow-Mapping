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

// Disegna una semplice scena con una base, un toro e 4 sfere.
void Scene1(float angle) {
	
	// BASE
	glPushMatrix();
		glColor3fv(BLUE);
		glScalef(1.0f, 0.05f, 1.0f);
		glutSolidCube(4.0f);
	glPopMatrix();

	// TORO
	glPushMatrix();
		glColor3fv(RED);
		glTranslatef(0.0f, 0.5f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidTorus(0.2, 0.5, 24, 48);
	glPopMatrix();

	// SFERE
	glPushMatrix();
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glColor3fv(GREEN);

		// glTranslatef(0.45f, 1.0f, 0.0f); // ESEMPIO-PRESENTAZIONE
		glTranslatef(0.45f, 1.0f, 0.45f);
		glutSolidSphere(0.2, 24, 24);

		glTranslatef(-0.9f, 0.0f, 0.0f);
		glutSolidSphere(0.2, 24, 24);

		glTranslatef(0.0f, 0.0f,-0.9f);
		glutSolidSphere(0.2, 24, 24);

		glColor3fv(YELLOW);
		glTranslatef(0.9f, 0.0f, 0.0f);
		glutSolidSphere(0.2, 24, 24);
	glPopMatrix();

}

// Disegna la scena proposta da NVIDIA Corporation.
void Scene2() {

	int l1 = 0, l2 = 0, l3 = 0;

	// BASE
	glPushMatrix();
		glColor3fv(BROWN);
		glScalef(1.0f, 0.05f, 1.0f);
		glutSolidCube(4.5f);
	glPopMatrix();

	// SFERE
	glPushMatrix();
		glTranslatef(-0.7f, 0.5f, -0.7f);

		for (l1 = 0; l1 < 3; l1++) {
			glPushMatrix();
				for (l2 = 0; l2 < 9; l2++) {
					if ((l1+l2)%2 == 0) glColor3fv(CHRISTMAS_GREEN);
					else  glColor3fv(CHRISTMAS_RED);

					glutSolidSphere(0.2, 24, 24);

					if (l2%3 != 2) glTranslatef(0.0f, 0.0f, 0.5f);
					else glTranslatef(0.5f, 0.0f, -1.0f);
				}
			glPopMatrix();
			glTranslatef(0.0f, 0.6f, 0.0f);
		}
	glPopMatrix();

}

void Scene3() {

	// BASE
	glPushMatrix();
		glColor3fv(YELLOW_20);
		glScalef(1.0f, 0.05f, 1.0f);
		glutSolidCube(4.0f);
	glPopMatrix();

	// TEAPOT
	glPushMatrix();
		glTranslatef(0.0f, 0.7f, 0.0f);
		glRotatef(40.0f, 0.0f, 1.0f, 0.0f);
		glColor3fv(GRAY_90);
		glutSolidTeapot(0.6);
	glPopMatrix();

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
            Scene2();
            break;
        }
        case SCENE3:
        {
            Scene3();
            break;
        }
        default:
            break;
    }

}

/*

	mesh.cpp
	di Mario Gabriele Carofano

*/

/*	************************************************************************* */
//	LIBRERIE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*	************************************************************************* */
//	ENUMERAZIONI, COSTANTI E VARIABILI GLOBALI

#define MATRIX_WIDTH 4
#define MATRIX_HEIGHT 4
#define MATRIX_DEPTH 3

#define AXIS_LENGTH 100
#define AXIS_OPACITY 0.2

/*	************************************************************************* */
//	FUNZIONI ACCESSORIE

template <typename Data>
void freeMatrix(Data** mat, int rows) {
    for (int i = 0; i < rows; i++) {
        free(mat[i]);
    }
    free(mat);
}

float* getNormal(double **points, const int n_vert, const int start) {

	float* ret = (float*) calloc(3, sizeof(float));

	float x_ret = 0.0, y_ret = 0.0, z_ret = 0.0;
	float x_diff = 0.0, y_diff = 0.0, z_diff = 0.0;
	float x_sum = 0.0, y_sum = 0.0, z_sum = 0.0;
	int curr = 0, next = 0;

	for (int i = 0; i < n_vert; i++) {

		curr = start + i;
		next = start + ((i+1) % n_vert);

		// printf("curr: %d, next: %d\n", curr, next);

		y_diff = points[curr][1] - points[next][1];
		z_sum = points[curr][2] + points[next][2];
		x_ret += (y_diff * z_sum);

		z_diff = points[curr][2] - points[next][2];
		x_sum = points[curr][0] + points[next][0];
		y_ret += (z_diff * x_sum);

		x_diff = points[curr][0] - points[next][0];
		y_sum = points[curr][1] + points[next][1];
		z_ret += (x_diff * y_sum);

	}

	ret[0] = x_ret;
	ret[1] = y_ret;
	ret[2] = z_ret;

	return ret;

}

float* getCenter(double **points, const int n_vert, const int start) {

	float* ret = (float*) calloc(3, sizeof(float));

	float x_ret = 0.0;
	float y_ret = 0.0;
	float z_ret = 0.0;

	for (int i = 0; i < n_vert; i++) {

		x_ret += points[start+i][0];
		y_ret += points[start+i][1];
		z_ret += points[start+i][2];

	}

	ret[0] = x_ret / n_vert;
	ret[1] = y_ret / n_vert;
	ret[2] = z_ret / n_vert;

	return ret;

}

void toHomogeneous(GLfloat cp[MATRIX_WIDTH][MATRIX_HEIGHT][MATRIX_DEPTH], GLfloat cw[MATRIX_WIDTH][MATRIX_HEIGHT][MATRIX_DEPTH+1], GLfloat w[MATRIX_WIDTH][MATRIX_HEIGHT]) {
	for (int i = 0; i < MATRIX_WIDTH; i++) {
		for (int j = 0; j < MATRIX_HEIGHT; j++) {
			for (int k = 0; k < MATRIX_DEPTH; k++) {
				cw[i][j][k] = cp[i][j][k] * w[i][j];
			}
			cw[i][j][MATRIX_DEPTH] = w[i][j];
		}
	}
}

void drawAxis() {
	glBegin(GL_LINES);

		// X_AXIS
		glColor4f(RED[0], RED[1], RED[2], AXIS_OPACITY);
		glVertex3f(-AXIS_LENGTH, 0.0, 0.0);
		glVertex3f(AXIS_LENGTH, 0.0, 0.0);

		// Y_AXIS
		glColor4f(GREEN[0], GREEN[1], GREEN[2], AXIS_OPACITY);
		glVertex3f(0.0, -AXIS_LENGTH, 0.0);
		glVertex3f(0.0, AXIS_LENGTH, 0.0);

		// Z_AXIS
		glColor4f(CYAN[0], CYAN[1], CYAN[2], AXIS_OPACITY);
		glVertex3f(0.0, 0.0, -AXIS_LENGTH);
		glVertex3f(0.0, 0.0, AXIS_LENGTH);
	
	glEnd();
}

/*	************************************************************************* */
/*	RIFERIMENTI
	
*/
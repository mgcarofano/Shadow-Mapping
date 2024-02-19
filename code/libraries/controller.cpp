/*

	controller.cpp
	di Mario Gabriele Carofano

*/

/*	************************************************************************* */
//	LIBRERIE

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include "./GLFW/glfw3.h"

#include "color.cpp"
#include "mesh.cpp"
#include "csv.cpp"

#include <stdio.h>
#include <math.h>

/*	************************************************************************* */
//	ENUMERAZIONI, COSTANTI E VARIABILI GLOBALI

#define WINDOW_WIDTH 750.0
#define WINDOW_HEIGHT 750.0
#define WINDOW_X_POSITION 400.0
#define WINDOW_Y_POSITION 100.0

float x_position = 0.0;
float y_position = 0.0;
float z_position = 0.0;

float fovy = 45.0;
float aspect = 1.0;
float zNear = 0.1;
float zFar = 100.0;

float e_rad = 20.0;
float e_lat = 0.0;
float e_long = 0.0;

/*	************************************************************************* */
//	FUNZIONI ACCESSORIE

float getRelative(int coord, float dimension) {
	float mid = dimension / 2.0;
	float relative = (coord - mid) / mid; // dipende dalle dimensioni della finestra

	if (coord > 0 && coord < mid) { // coordinata negativa
		if (relative > 0.0) relative = relative * (-1);
	} else if (coord > mid && coord < dimension) { // coordinata positiva
		if (relative < 0.0) relative = relative * (-1);
	} else if (coord == mid) {
		relative = 0.0;
	} else if (coord == 0) {
		relative = -1.0;
	} else if (coord == dimension) {
		relative = 1.0;
	}

	return relative;
}

void computeEyePoint(float* eyePoint) {
	eyePoint[0] = e_rad * cos(e_lat * M_PI/180) * cos(e_long * M_PI/180);
	eyePoint[1] = e_rad * sin(e_lat * M_PI/180);
	eyePoint[2] = e_rad * cos(e_lat * M_PI/180) * sin(e_long * M_PI/180);
	// printf("e_rad: %f, e_lat: %f, e_long: %f\n", e_rad, e_lat, e_long);
}

/*	************************************************************************* */
//	FUNZIONI PER INTERAZIONE DA MOUSE E TASTIERA

void q_func() {
	
}

void a_func() {
	
}

void w_func() {
	
}

void s_func() {
	
}

void e_func() {
	
}

void d_func() {
	
}

void i_func() {
	
}

void j_func() {
	
}

void k_func() {
	
}

void l_func() {
	
}

void r_func() {
	
}

void space_func() {
	
}

void up_func() {
	
}

void down_func() {
	
}

void left_key_func() {
	
}

void right_key_func() {
	
}

void left_mouse_func(int state, int x, int y) {
	
}

void right_mouse_func(int state, int x, int y) {
	
}

/*	************************************************************************* */
/*	RIFERIMENTI
	
*/

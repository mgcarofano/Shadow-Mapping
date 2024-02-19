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

#define WINDOW_WIDTH 750.0
#define WINDOW_HEIGHT 750.0
#define WINDOW_X_POSITION 400.0
#define WINDOW_Y_POSITION 100.0

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

Point computeEyePoint() {
	float x_ret = 0.0, y_ret = 0.0, z_ret = 0.0;

	x_ret = e_rad * cos(e_lat * M_PI/180) * cos(e_long * M_PI/180);
	y_ret = e_rad * sin(e_lat * M_PI/180);
	z_ret = e_rad * cos(e_lat * M_PI/180) * sin(e_long * M_PI/180);

	// printf("e_rad: %f, e_lat: %f, e_long: %f\n", e_rad, e_lat, e_long);

	return Point(x_ret, y_ret, z_ret);
}

/*	************************************************************************* */
//	FUNZIONI PER INTERAZIONE DA MOUSE E TASTIERA

void q_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void a_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void w_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void s_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void e_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void d_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void i_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void j_func(Example e) {
	switch (e)
	{
		default:
			break;
	}
}

void k_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void l_func(Example e) {
	switch (e)
	{
		default:
			break;
	}
}

void r_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void space_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void up_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void down_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void left_key_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void right_key_func(Example e) {
	switch(e)
	{
		default:
			break;
	}
}

void left_mouse_func(Example e, int state, int x, int y) {
	switch(e)
	{
		default:
			break;
	}
}

void right_mouse_func(Example e, int state, int x, int y) {
	switch(e)
	{
		default:
			break;
	}
}

/*	************************************************************************* */
/*	RIFERIMENTI
	
*/

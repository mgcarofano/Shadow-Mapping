/*

	color.cpp
	di Mario Gabriele Carofano

*/

/*	************************************************************************* */
//	LIBRERIE

#include <stdio.h>
#include <math.h>

/*	************************************************************************* */
//	FUNZIONI ACCESSORIE

float* getRandomColor() {
	float* ret = (float*) calloc(3, float);

	ret[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	ret[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	ret[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	
	return ret;
}

float* getRGBfromHEX(int hexValue) {
	float* ret = (float*) calloc(3, float);

	ret[0] = ((hexValue >> 16) & 0xFF) / 255.0;
	ret[1] = ((hexValue >> 8) & 0xFF) / 255.0;
	ret[2] = ((hexValue) & 0xFF) / 255.0;

  	return ret;
}

/*	************************************************************************* */
//	COSTANTI E VARIABILI GLOBALI

#define WHITE {1.0, 1.0, 1.0}
#define GRAY_90 {0.9, 0.9, 0.9}
#define GRAY_80 {0.8, 0.8, 0.8}
#define GRAY_70 {0.7, 0.7, 0.7}
#define GRAY_60 {0.6, 0.6, 0.6}
#define GRAY_50 {0.5, 0.5, 0.5}
#define GRAY_40 {0.4, 0.4, 0.4}
#define GRAY_30 {0.3, 0.3, 0.3}
#define GRAY_20 {0.2, 0.2, 0.2}
#define GRAY_10 {0.1, 0.1, 0.1}
#define BLACK {0.0, 0.0, 0.0}

#define RED {1.0, 0.0, 0.0}
#define GREEN {0.0, 1.0, 0.0}
#define BLUE {0.0, 0.0, 1.0}

#define CYAN {0.0, 1.0, 1.0}
#define PURPLE {1.0, 0.0, 1.0}
#define YELLOW {1.0, 1.0, 0.0}
#define YELLOW_20 {0.2, 0.2, 0.0}

#define BROWN {0.43, 0.15, 0.05}
#define IVORY {1.0, 1.0, 0.941}
#define BEIGE {0.882, 0.776, 0.6}
#define BLUE_VIOLET {0.541, 0.168, 0.886}
#define LAVENDER {0.902, 0.902, 0.98}
#define DARK_BROWN {0.36, 0.25, 0.2}

#define CHRISTMAS_GREEN {0.192, 0.474, 0.345}
#define CHRISTMAS_RED {0.662, 0.211, 0.235}

/*	************************************************************************* */
/*	RIFERIMENTI
	
*/
